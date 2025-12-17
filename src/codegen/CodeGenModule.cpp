// src/codegen/CodeGenModule.cpp
// Linear code generation (task 2) for the stackdyn64 VM.

#include "CodeGenModule.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <set>
#include <sstream>

namespace stackdyn64_codegen {

namespace {

// =============================================================================
// Tagged value helpers (must match stackdyn64.target.pdsl)
//   TV[63:56] = tag
//   TV[55:0]  = payload
// =============================================================================

constexpr std::uint64_t TAG_BOOL   = 0x01ull;
constexpr std::uint64_t TAG_INT    = 0x02ull;
constexpr std::uint64_t TAG_UINT   = 0x03ull;
constexpr std::uint64_t TAG_CHAR   = 0x04ull;
constexpr std::uint64_t TAG_STRING = 0x05ull;

inline std::uint64_t makeTV(std::uint64_t tag, std::uint64_t payload56) {
    return (tag << 56) | (payload56 & 0x00FFFFFFFFFFFFFFull);
}

inline std::uint64_t tvBool(bool v) { return makeTV(TAG_BOOL, v ? 1ull : 0ull); }
inline std::uint64_t tvUInt(std::uint64_t v) { return makeTV(TAG_UINT, v); }
inline std::uint64_t tvInt(std::int64_t v) {
    return makeTV(TAG_INT, static_cast<std::uint64_t>(v) & 0x00FFFFFFFFFFFFFFull);
}
inline std::uint64_t tvChar(std::uint32_t cp) { return makeTV(TAG_CHAR, static_cast<std::uint64_t>(cp)); }
inline std::uint64_t tvStringPtrPayload(std::uint16_t addr16) { return makeTV(TAG_STRING, addr16); }

// =============================================================================
// Utilities
// =============================================================================

static std::string sanitizeLabel(std::string s) {
    for (char& c : s) {
        unsigned char uc = static_cast<unsigned char>(c);
        // Only [A-Za-z0-9_] are allowed in labels for the assembler.
        if (!(std::isalnum(uc) || c == '_')) c = '_';
    }
    if (s.empty()) s = "_";
    // Label must not start with a digit.
    if (std::isdigit(static_cast<unsigned char>(s[0]))) s = "_" + s;
    return s;
}


static std::string makeFunctionLabel(const std::string& name) {
    // Avoid collisions with instruction mnemonics (e.g. function named 'add').
    // Assembler treats mnemonics as reserved tokens, so we prefix all function entry labels.
    return std::string("fn_") + sanitizeLabel(name);
}

static bool parseIntLiteral(const std::string& s, std::int64_t& outVal) {
    try {
        int base = 10;
        std::size_t idx = 0;
        if (s.size() >= 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) base = 16;
        else if (s.size() >= 2 && s[0] == '0' && (s[1] == 'b' || s[1] == 'B')) base = 2;
        outVal = std::stoll(s, &idx, base);
        return idx == s.size();
    } catch (...) {
        return false;
    }
}

// =============================================================================
// ProgramImage builder
// =============================================================================

struct ImageBuilder {
    stackdyn64::ProgramImage image;
    std::size_t codeSectionIndex = 0;
    std::size_t dataSectionIndex = 0;

    ImageBuilder() {
        stackdyn64::Section code;
        code.decl.name = "code";
        code.decl.bank = stackdyn64::BankName::code;
        code.decl.startAddr = static_cast<std::uint16_t>(0x0000);
        image.sections.push_back(std::move(code));
        codeSectionIndex = image.sections.size() - 1;

        stackdyn64::Section data;
        data.decl.name = "data";
        data.decl.bank = stackdyn64::BankName::dataMem;
        data.decl.startAddr = static_cast<std::uint16_t>(0x0000);
        image.sections.push_back(std::move(data));
        dataSectionIndex = image.sections.size() - 1;
    }

    stackdyn64::Section& codeSec() { return image.sections.at(codeSectionIndex); }
    stackdyn64::Section& dataSec() { return image.sections.at(dataSectionIndex); }

    std::size_t emitCodeLabel(const std::string& raw, const std::string& qualified) {
        stackdyn64::LineItem li;
        li.label = stackdyn64::Label{raw, qualified};
        li.payload = stackdyn64::CommentLine{""};
        codeSec().lines.push_back(std::move(li));
        return codeSec().lines.size() - 1;
    }

    std::size_t emitInstr(const stackdyn64::Instruction& ins, std::optional<stackdyn64::Label> lbl = std::nullopt) {
        stackdyn64::LineItem li;
        li.label = std::move(lbl);
        li.payload = ins;
        codeSec().lines.push_back(std::move(li));
        return codeSec().lines.size() - 1;
    }

    std::size_t emitDataLabel(const std::string& raw, const std::string& qualified) {
        stackdyn64::LineItem li;
        li.label = stackdyn64::Label{raw, qualified};
        li.payload = stackdyn64::CommentLine{""};
        dataSec().lines.push_back(std::move(li));
        return dataSec().lines.size() - 1;
    }

    std::size_t emitDataBytes(const std::vector<std::uint8_t>& bytes, const std::string& comment = {}) {
        stackdyn64::DataDef d;
        d.dir = stackdyn64::DataDirective::db;
        d.comment = comment;
        d.values.reserve(bytes.size());
        for (auto b : bytes) d.values.push_back(static_cast<std::uint64_t>(b));

        stackdyn64::LineItem li;
        li.payload = d;
        dataSec().lines.push_back(std::move(li));
        return dataSec().lines.size() - 1;
    }
};

// =============================================================================
// Reverse postorder traversal for CFG
// =============================================================================

static std::vector<BasicBlockPtr> reversePostOrder(const ControlFlowGraph& cfg) {
    std::vector<BasicBlockPtr> post;
    std::set<int> vis;
    std::function<void(const BasicBlockPtr&)> dfs = [&](const BasicBlockPtr& b) {
        if (!b) return;
        if (vis.count(b->id)) return;
        vis.insert(b->id);
        for (const auto& e : b->edges) dfs(e.target);
        post.push_back(b);
    };
    dfs(cfg.entry);
    std::reverse(post.begin(), post.end());
    return post;
}

// =============================================================================
// Frame layout (matches CodeGenModule.h comment)
// =============================================================================

static void collectVarsFromOp(const OperationNodePtr& op,
                              std::set<std::string>& outVars,
                              const std::set<std::string>& params) {
    if (!op) return;

    if (op->kind == OperationKind::VarDecl) {
        for (const auto& o : op->operands) {
            if (o.kind == OperandKind::Variable && !params.count(o.value)) outVars.insert(o.value);
        }
    }

    if (op->kind == OperationKind::Assign && op->children.size() >= 1) {
        const auto& lhs = op->children[0];
        if (lhs && !lhs->operands.empty() && lhs->operands[0].kind == OperandKind::Variable) {
            const std::string& name = lhs->operands[0].value;
            if (!params.count(name)) outVars.insert(name);
        }
    }

    for (const auto& ch : op->children) collectVarsFromOp(ch, outVars, params);
}

static FrameLayout buildFrameLayout(const FunctionInfo& fn) {
    FrameLayout fl;

    // Params: +24, +32, ...
    std::int16_t pd = 24;
    for (const auto& p : fn.signature.paramNames) {
        fl.paramDisp[p] = pd;
        pd = static_cast<std::int16_t>(pd + 8);
    }

    std::set<std::string> params(fn.signature.paramNames.begin(), fn.signature.paramNames.end());
    std::set<std::string> locals;
    for (const auto& b : fn.cfg.blocks) {
        if (!b) continue;
        for (const auto& op : b->operations) collectVarsFromOp(op, locals, params);
    }

    std::int16_t ld = -8;
    for (const auto& name : locals) {
        fl.localDisp[name] = ld;
        ld = static_cast<std::int16_t>(ld - 8);
        fl.localCount++;
    }

    // Hidden temporary local used by codegen to preserve return values
    // while cleaning up call arguments.
    //
    // Why needed: call convention leaves arguments above the return slot.
    // To avoid leaking stack space, we temporarily spill the return value
    // into this local, drop arguments, then reload the return value.
    std::string tmpName = "__cg_tmp_ret";
    if (fl.localDisp.count(tmpName) || fl.paramDisp.count(tmpName)) {
        int k = 0;
        while (fl.localDisp.count(tmpName + std::to_string(k)) ||
               fl.paramDisp.count(tmpName + std::to_string(k))) {
            ++k;
        }
        tmpName = tmpName + std::to_string(k);
    }
    fl.localDisp[tmpName] = ld;
    ld = static_cast<std::int16_t>(ld - 8);
    fl.localCount++;

    return fl;
}

// =============================================================================
// Emission helpers
// =============================================================================

static std::size_t emitPushImm(ImageBuilder& out, std::uint64_t tv, const std::string& cmt = {}) {
    stackdyn64::Instruction i;
    i.mnemonic = stackdyn64::Mnemonic::push;
    i.operands = { stackdyn64::Operand::imm64(tv) };
    i.comment = cmt;
    return out.emitInstr(i);
}

static std::size_t emitJmp(ImageBuilder& out, const std::string& target, const std::string& cmt = {}) {
    stackdyn64::Instruction j;
    j.mnemonic = stackdyn64::Mnemonic::jmp;
    j.operands = { stackdyn64::Operand::codeLabel(target) };
    j.comment = cmt;
    const std::size_t line = out.codeSec().lines.size();
    out.image.fixups.push_back(stackdyn64::Fixup{out.codeSectionIndex, line, 0, target, stackdyn64::LabelSpace::Code});
    out.emitInstr(j);
    return line;
}

static std::size_t emitJcc(ImageBuilder& out, bool jnz, const std::string& target, const std::string& cmt = {}) {
    stackdyn64::Instruction j;
    j.mnemonic = jnz ? stackdyn64::Mnemonic::jnz : stackdyn64::Mnemonic::jz;
    j.operands = { stackdyn64::Operand::codeLabel(target) };
    j.comment = cmt;
    const std::size_t line = out.codeSec().lines.size();
    out.image.fixups.push_back(stackdyn64::Fixup{out.codeSectionIndex, line, 0, target, stackdyn64::LabelSpace::Code});
    out.emitInstr(j);
    return line;
}

// =============================================================================
// Expression lowering (stack-based): leaves result on stack
// =============================================================================

struct FnCtx {
    const FunctionInfo& fn;
    const FrameLayout& frame;
    ImageBuilder& out;
};

static void genExpr(const OperationNodePtr& n, FnCtx& ctx);

static void genLoadVar(const std::string& name, FnCtx& ctx) {
    auto itL = ctx.frame.localDisp.find(name);
    auto itP = ctx.frame.paramDisp.find(name);

    stackdyn64::Instruction i;
    i.mnemonic = stackdyn64::Mnemonic::ldfp;
    if (itL != ctx.frame.localDisp.end()) {
        i.operands = { stackdyn64::Operand::disp16(itL->second) };
        i.comment = "load local " + name;
        ctx.out.emitInstr(i);
        return;
    }
    if (itP != ctx.frame.paramDisp.end()) {
        i.operands = { stackdyn64::Operand::disp16(itP->second) };
        i.comment = "load param " + name;
        ctx.out.emitInstr(i);
        return;
    }

    // Unknown variable -> push 0
    emitPushImm(ctx.out, tvInt(0), "unknown var " + name);
}

static void genStoreVar(const std::string& name, FnCtx& ctx) {
    // Special case: assignment to the function name acts as a return value
    // (VB-like semantics). Store into the VM-mandated return slot [bp+16].
    if (name == ctx.fn.signature.name || sanitizeLabel(name) == sanitizeLabel(ctx.fn.signature.name)) {
        stackdyn64::Instruction st;
        st.mnemonic = stackdyn64::Mnemonic::stfp;
        st.operands = { stackdyn64::Operand::disp16(16) };
        st.comment = "store return value (" + ctx.fn.signature.name + ")";
        ctx.out.emitInstr(st);
        return;
    }

    auto itL = ctx.frame.localDisp.find(name);
    auto itP = ctx.frame.paramDisp.find(name);

    stackdyn64::Instruction i;
    i.mnemonic = stackdyn64::Mnemonic::stfp;
    if (itL != ctx.frame.localDisp.end()) {
        i.operands = { stackdyn64::Operand::disp16(itL->second) };
        i.comment = "store local " + name;
        ctx.out.emitInstr(i);
        return;
    }
    if (itP != ctx.frame.paramDisp.end()) {
        i.operands = { stackdyn64::Operand::disp16(itP->second) };
        i.comment = "store param " + name;
        ctx.out.emitInstr(i);
        return;
    }
    // Unknown -> drop value
    stackdyn64::Instruction drop;
    drop.mnemonic = stackdyn64::Mnemonic::drop;
    drop.comment = "drop (unknown var " + name + ")";
    ctx.out.emitInstr(drop);
}

static std::int16_t tmpRetDisp(const FrameLayout& frame) {
    // Find the hidden spill slot added in buildFrameLayout.
    for (const auto& kv : frame.localDisp) {
        if (kv.first.rfind("__cg_tmp_ret", 0) == 0) return kv.second;
    }
    // Fallback (should not happen): use the first local if any.
    if (!frame.localDisp.empty()) return frame.localDisp.begin()->second;
    return -8;
}

static void genBinaryOp(const OperationNodePtr& n, FnCtx& ctx) {
    if (!n || n->children.size() < 2) return;
    genExpr(n->children[0], ctx);
    genExpr(n->children[1], ctx);

    stackdyn64::Instruction i;
    if (n->op == "AddExpr") i.mnemonic = stackdyn64::Mnemonic::add;
    else if (n->op == "SubExpr") i.mnemonic = stackdyn64::Mnemonic::sub;
    else if (n->op == "MulExpr") i.mnemonic = stackdyn64::Mnemonic::mul;
    else if (n->op == "DivExpr") i.mnemonic = stackdyn64::Mnemonic::div;
    else if (n->op == "ModExpr") i.mnemonic = stackdyn64::Mnemonic::mod;
    else if (n->op == "AndExpr") i.mnemonic = stackdyn64::Mnemonic::land;
    else if (n->op == "OrExpr") i.mnemonic = stackdyn64::Mnemonic::lor;
    else if (n->op == "CompareExpr") {
        std::string cmp;
        if (!n->operands.empty() && n->operands[0].kind == OperandKind::Constant) cmp = n->operands[0].value;
        if (cmp == "==") i.mnemonic = stackdyn64::Mnemonic::eq;
        else if (cmp == "!=" || cmp == "<>") i.mnemonic = stackdyn64::Mnemonic::neq;
        else if (cmp == "<") i.mnemonic = stackdyn64::Mnemonic::lt;
        else if (cmp == ">") i.mnemonic = stackdyn64::Mnemonic::gt;
        else if (cmp == "<=") i.mnemonic = stackdyn64::Mnemonic::le;
        else if (cmp == ">=") i.mnemonic = stackdyn64::Mnemonic::ge;
        else i.mnemonic = stackdyn64::Mnemonic::eq;
    } else {
        i.mnemonic = stackdyn64::Mnemonic::nop;
        i.comment = "unknown binop " + n->op;
    }
    ctx.out.emitInstr(i);
}

static void genUnaryOp(const OperationNodePtr& n, FnCtx& ctx) {
    if (!n || n->children.empty()) return;
    genExpr(n->children[0], ctx);

    std::string uop;
    if (!n->operands.empty() && n->operands[0].kind == OperandKind::Constant) uop = n->operands[0].value;

    stackdyn64::Instruction i;
    if (uop == "not") i.mnemonic = stackdyn64::Mnemonic::lnot;
    else i.mnemonic = stackdyn64::Mnemonic::neg; // default: unary '-'
    ctx.out.emitInstr(i);
}

static void genCall(const OperationNodePtr& n, FnCtx& ctx) {
    if (!n) return;

    // Determine callee raw name first (before makeFunctionLabel)
    std::string calleeRaw;
    if (!n->children.empty() && n->children[0] && n->children[0]->op == "Identifier" && !n->children[0]->operands.empty()) {
        calleeRaw = n->children[0]->operands[0].value;
    } else {
        calleeRaw = n->op;
    }

    // -------------------- BUILTINS --------------------
    // Convention: builtins return 0 (int) so they can be used in expressions too.
    // Arguments are children[1..].

    if (calleeRaw == "printChar") {
        // expects 1 arg
        if (n->children.size() >= 2) genExpr(n->children[1], ctx); // pushes value
        stackdyn64::Instruction o;
        o.mnemonic = stackdyn64::Mnemonic::outb;
        o.comment = "builtin printChar";
        ctx.out.emitInstr(o);

        // return 0
        emitPushImm(ctx.out, tvInt(0), "printChar ret");
        return;
    }

    if (calleeRaw == "println") {
        // print '\n'
        emitPushImm(ctx.out, tvChar('\n'), "newline");
        stackdyn64::Instruction o;
        o.mnemonic = stackdyn64::Mnemonic::outb;
        o.comment = "builtin println";
        ctx.out.emitInstr(o);

        emitPushImm(ctx.out, tvInt(0), "println ret");
        return;
    }

    if (calleeRaw == "printInt") {
        // Full version: prints any non-negative integer by calling helper routine.
        // Expects 1 arg.
        if (n->children.size() >= 2) genExpr(n->children[1], ctx);
        else emitPushImm(ctx.out, tvInt(0), "missing arg");

        // push return slot
        emitPushImm(ctx.out, tvInt(0), "return slot");

        const std::string callee = "__builtin_printInt";

        stackdyn64::Instruction call;
        call.mnemonic = stackdyn64::Mnemonic::call;
        call.operands = { stackdyn64::Operand::codeLabel(callee) };
        call.comment = "call builtin printInt";
        const std::size_t line = ctx.out.codeSec().lines.size();
        ctx.out.image.fixups.push_back(stackdyn64::Fixup{ctx.out.codeSectionIndex, line, 0, callee, stackdyn64::LabelSpace::Code});
        ctx.out.emitInstr(call);

        // cleanup: spill return, drop arg, reload (leave 0 on stack)
        const std::int16_t disp = tmpRetDisp(ctx.frame);
        {
            stackdyn64::Instruction st;
            st.mnemonic = stackdyn64::Mnemonic::stfp;
            st.operands = { stackdyn64::Operand::disp16(disp) };
            st.comment = "spill builtin ret";
            ctx.out.emitInstr(st);
        }
        {
            stackdyn64::Instruction drop;
            drop.mnemonic = stackdyn64::Mnemonic::drop;
            drop.comment = "drop arg";
            ctx.out.emitInstr(drop);
        }
        {
            stackdyn64::Instruction ld;
            ld.mnemonic = stackdyn64::Mnemonic::ldfp;
            ld.operands = { stackdyn64::Operand::disp16(disp) };
            ld.comment = "reload builtin ret";
            ctx.out.emitInstr(ld);
        }
        return;
    }

     if (calleeRaw == "readChar") {
        // set input port
        {
            stackdyn64::Instruction s;
            s.mnemonic = stackdyn64::Mnemonic::setio;
            s.operands = { stackdyn64::Operand::imm8(0) };
            s.comment = "builtin readChar: setio stdin";
            ctx.out.emitInstr(s);
        }

        // read byte -> pushes TAG_INT(payload=byte)
        {
            stackdyn64::Instruction in;
            in.mnemonic = stackdyn64::Mnemonic::inb;
            in.comment = "builtin readChar: inb";
            ctx.out.emitInstr(in);
        }

        // restore output port (so printInt/printChar keep working)
        {
            stackdyn64::Instruction s;
            s.mnemonic = stackdyn64::Mnemonic::setio;
            s.operands = { stackdyn64::Operand::imm8(1) };
            s.comment = "builtin readChar: restore stdout";
            ctx.out.emitInstr(s);
        }

        return; // result already on stack
    }

    if (calleeRaw == "readInt") {
        // call __builtin_readInt()
        emitPushImm(ctx.out, tvInt(0), "return slot");
        stackdyn64::Instruction call;
        call.mnemonic = stackdyn64::Mnemonic::call;
        call.operands = { stackdyn64::Operand::codeLabel("__builtin_readInt") };
        call.comment = "builtin readInt";
        const std::size_t line = ctx.out.codeSec().lines.size();
        ctx.out.image.fixups.push_back(stackdyn64::Fixup{ctx.out.codeSectionIndex, line, 0,
                                                        "__builtin_readInt", stackdyn64::LabelSpace::Code});
        ctx.out.emitInstr(call);

        // spill ret, no args to drop
        const std::int16_t disp = tmpRetDisp(ctx.frame);
        {
            stackdyn64::Instruction st;
            st.mnemonic = stackdyn64::Mnemonic::stfp;
            st.operands = { stackdyn64::Operand::disp16(disp) };
            st.comment = "spill readInt ret";
            ctx.out.emitInstr(st);
        }
        {
            stackdyn64::Instruction ld;
            ld.mnemonic = stackdyn64::Mnemonic::ldfp;
            ld.operands = { stackdyn64::Operand::disp16(disp) };
            ld.comment = "reload readInt ret";
            ctx.out.emitInstr(ld);
        }
        return;
    }

    // -------------------- NORMAL CALL --------------------
    const std::string callee = makeFunctionLabel(calleeRaw);

    // Arguments are children[1..]
    const std::size_t argc = (n->children.size() >= 1) ? (n->children.size() - 1) : 0;
    for (std::size_t i = n->children.size(); i-- > 1;) {
        genExpr(n->children[i], ctx);
    }
    // Return slot placeholder (callee will write [bp+16])
    emitPushImm(ctx.out, tvInt(0), "return slot");

    stackdyn64::Instruction call;
    call.mnemonic = stackdyn64::Mnemonic::call;
    call.operands = { stackdyn64::Operand::codeLabel(callee) };
    call.comment = "call " + callee;
    const std::size_t line = ctx.out.codeSec().lines.size();
    ctx.out.image.fixups.push_back(stackdyn64::Fixup{ctx.out.codeSectionIndex, line, 0, callee, stackdyn64::LabelSpace::Code});
    ctx.out.emitInstr(call);

    // IMPORTANT: our call convention places arguments *above* the return slot.
    // After RET, the stack top is the return value, but the arguments are still
    // sitting above it (sp+8, sp+16, ...). If we leave them there, stack space
    // leaks with every call.
    //
    // We clean them up while keeping the return value by spilling the return
    // value into a hidden local slot, dropping args, then reloading.
    if (argc > 0) {
        const std::int16_t disp = tmpRetDisp(ctx.frame);

        // spill return value into local: stfp disp (pops value)
        {
            stackdyn64::Instruction st;
            st.mnemonic = stackdyn64::Mnemonic::stfp;
            st.operands = { stackdyn64::Operand::disp16(disp) };
            st.comment = "spill call ret";
            ctx.out.emitInstr(st);
        }

        // drop arguments (now on top)
        for (std::size_t k = 0; k < argc; ++k) {
            stackdyn64::Instruction drop;
            drop.mnemonic = stackdyn64::Mnemonic::drop;
            drop.comment = "drop arg";
            ctx.out.emitInstr(drop);
        }

        // reload return value back to stack
        {
            stackdyn64::Instruction ld;
            ld.mnemonic = stackdyn64::Mnemonic::ldfp;
            ld.operands = { stackdyn64::Operand::disp16(disp) };
            ld.comment = "reload call ret";
            ctx.out.emitInstr(ld);
        }
    }
}

static void genExpr(const OperationNodePtr& n, FnCtx& ctx) {
    if (!n) return;

    switch (n->kind) {
        case OperationKind::VarDecl:
            // allocated in prolog; no code here
            return;

        case OperationKind::Assign: {
            if (n->children.size() < 2) return;
            // RHS
            genExpr(n->children[1], ctx);

            // LHS variable name
            const auto& lhs = n->children[0];
            if (lhs && lhs->op == "Identifier" && !lhs->operands.empty()) {
                genStoreVar(lhs->operands[0].value, ctx);
            } else {
                stackdyn64::Instruction drop;
                drop.mnemonic = stackdyn64::Mnemonic::drop;
                drop.comment = "drop (unsupported LHS)";
                ctx.out.emitInstr(drop);
            }
            // assignment is a statement in our language; no resulting value kept
            return;
        }

        case OperationKind::BinaryOp:
            genBinaryOp(n, ctx);
            return;

        case OperationKind::UnaryOp:
            genUnaryOp(n, ctx);
            return;

        case OperationKind::Call:
            genCall(n, ctx);
            return;

        case OperationKind::Nop: {
            if (n->op == "Literal" && !n->operands.empty()) {
                const std::string& lit = n->operands[0].value;
                if (lit == "true" || lit == "false") {
                    emitPushImm(ctx.out, tvBool(lit == "true"), "bool");
                    return;
                }
                if (!lit.empty() && lit.front() == '\'' && lit.back() == '\'' && lit.size() >= 3) {
                    std::uint32_t cp = static_cast<std::uint8_t>(lit[1]);
                    emitPushImm(ctx.out, tvChar(cp), "char");
                    return;
                }
                if (!lit.empty() && lit.front() == '"') {
                    // Strings are not fully supported without a proper linker that patches IMM64.
                    // For now: push tagged null string pointer.
                    emitPushImm(ctx.out, tvStringPtrPayload(0), "string (stub)");
                    return;
                }
                std::int64_t v = 0;
                if (parseIntLiteral(lit, v)) emitPushImm(ctx.out, tvInt(v), "int");
                else emitPushImm(ctx.out, tvInt(0), "bad literal");
                return;
            }

            if (n->op == "Identifier" && !n->operands.empty()) {
                genLoadVar(n->operands[0].value, ctx);
                return;
            }

            // Wrapper: evaluate children sequentially, keep last value on stack
            for (const auto& ch : n->children) genExpr(ch, ctx);
            return;
        }
    }
}

static void genStatement(const OperationNodePtr& op, FnCtx& ctx) {
    if (!op) return;
    if (op->kind == OperationKind::Assign) {
        genExpr(op, ctx);
        return;
    }
    if (op->kind == OperationKind::VarDecl) return;
    genExpr(op, ctx);
    // Expression statement: drop result
    stackdyn64::Instruction drop;
    drop.mnemonic = stackdyn64::Mnemonic::drop;
    drop.comment = "drop expr result";
    ctx.out.emitInstr(drop);
}

// =============================================================================
// Block lowering
// =============================================================================

static std::string makeBlockLabel(const FunctionInfo& fn, const BasicBlockPtr& b) {
    std::ostringstream oss;
    // Assembler allows dots only as *leading* local-label markers. Use '_' in generated global labels.
    oss << makeFunctionLabel(fn.signature.name) << "_B" << b->id;
    if (!b->label.empty()) oss << "_" << sanitizeLabel(b->label);
    return oss.str();
}

static void lowerFunction(const FunctionInfo& fn, ImageBuilder& out, CodeGenResult& res) {
    const std::string fnName = makeFunctionLabel(fn.signature.name);
    FrameLayout frame = buildFrameLayout(fn);
    res.frames[fnName] = frame;

    // Map each block to a code label
    std::unordered_map<int, std::string> b2l;
    for (const auto& b : fn.cfg.blocks) {
        if (!b) continue;
        b2l[b->id] = makeBlockLabel(fn, b);
    }

    FnCtx ctx{fn, res.frames[fnName], out};

    // Function symbol label
    out.emitCodeLabel(fnName, fnName);

    // --- Prolog: allocate locals on stack via pushes (each = 8 bytes)
    for (std::size_t i = 0; i < frame.localCount; ++i) {
        emitPushImm(out, tvInt(0), "local init");
    }

    // Jump to entry block label
    if (fn.cfg.entry) emitJmp(out, b2l[fn.cfg.entry->id], "enter body");

    // Traverse blocks in reverse postorder (works with cycles)
    auto order = reversePostOrder(fn.cfg);

    for (std::size_t idx = 0; idx < order.size(); ++idx) {
        const auto& b = order[idx];
        if (!b) continue;
        out.emitCodeLabel(b2l[b->id], b2l[b->id]);

        const bool hasCond = [&]() {
            bool hasT = false, hasF = false;
            for (const auto& e : b->edges) {
                if (e.kind == EdgeKind::TrueBranch) hasT = true;
                if (e.kind == EdgeKind::FalseBranch) hasF = true;
            }
            return hasT && hasF;
        }();

        // If conditional, the last operation in the block is the condition expression.
        const std::size_t nops = b->operations.size();
        const std::size_t stmtCount = (hasCond && nops > 0) ? (nops - 1) : nops;

        for (std::size_t i = 0; i < stmtCount; ++i) genStatement(b->operations[i], ctx);

        if (hasCond && nops > 0) {
            // Condition must leave its value on stack; jz/jnz will POP it.
            genExpr(b->operations.back(), ctx);
        }

        // Exit block -> epilog
        if (fn.cfg.exit && b->id == fn.cfg.exit->id) {
            // Default return value: 0
            emitPushImm(out, tvInt(0), "default return");
            stackdyn64::Instruction st;
            st.mnemonic = stackdyn64::Mnemonic::stfp;
            st.operands = { stackdyn64::Operand::disp16(16) };
            st.comment = "write return slot";
            out.emitInstr(st);

            stackdyn64::Instruction r;
            r.mnemonic = stackdyn64::Mnemonic::ret;
            out.emitInstr(r);
            continue;
        }

        if (b->edges.empty() || b->isTerminal) {
            if (fn.cfg.exit) emitJmp(out, b2l[fn.cfg.exit->id], "to exit");
            continue;
        }

        // Conditional: emit jnz true; jmp false
        if (hasCond) {
            BasicBlockPtr t = nullptr, f = nullptr;
            for (const auto& e : b->edges) {
                if (e.kind == EdgeKind::TrueBranch) t = e.target;
                if (e.kind == EdgeKind::FalseBranch) f = e.target;
            }
            if (t && f) {
                emitJcc(out, /*jnz=*/true, b2l[t->id], "if true");
                emitJmp(out, b2l[f->id], "if false");
                continue;
            }
        }

        // Single edge: fallthrough/jmp
        if (b->edges.size() == 1 && b->edges[0].target) {
            const auto& e = b->edges[0];
            const std::string target = b2l[e.target->id];
            if (e.kind == EdgeKind::Fallthrough && idx + 1 < order.size() && order[idx + 1] && b2l[order[idx + 1]->id] == target) {
                continue; // natural fallthrough
            }
            emitJmp(out, target, "edge");
            continue;
        }

        // Fallback: jump to first edge
        if (!b->edges.empty() && b->edges[0].target) emitJmp(out, b2l[b->edges[0].target->id], "edge0");
    }
}


// =============================================================================
// Built-in helper routines
// =============================================================================

static void emitBuiltinPrintInt(ImageBuilder& out) {
    // Prints non-negative integer x passed as first argument, returns 0.
    // Recursively prints higher digits then prints last digit.
    const std::string FN = "__builtin_printInt";
    const std::string L_SINGLE = "__builtin_printInt_single";

    out.emitCodeLabel(FN, FN);

    // Prolog locals (2 slots): saved_x and tmp_ret
    emitPushImm(out, tvInt(0), "local saved_x");
    emitPushImm(out, tvInt(0), "local tmp");

    // Load x (param0 at [bp+24])
    {
        stackdyn64::Instruction ld;
        ld.mnemonic = stackdyn64::Mnemonic::ldfp;
        ld.operands = { stackdyn64::Operand::disp16(24) };
        ld.comment = "load x";
        out.emitInstr(ld);
    }

    // if x >= 10 ?  (keep x on stack)
    {
        stackdyn64::Instruction dup;
        dup.mnemonic = stackdyn64::Mnemonic::dup;
        dup.comment = "dup x";
        out.emitInstr(dup);
    }
    emitPushImm(out, tvInt(10), "10");
    {
        stackdyn64::Instruction ge;
        ge.mnemonic = stackdyn64::Mnemonic::ge;
        ge.comment = "x >= 10";
        out.emitInstr(ge);
    }
    // if !(x >= 10) jump to single-digit path; jz pops condition, x remains
    emitJcc(out, /*jnz=*/false, L_SINGLE, "single digit?");

    // Multi-digit path: stack has [x]
    {
        stackdyn64::Instruction st;
        st.mnemonic = stackdyn64::Mnemonic::stfp;
        st.operands = { stackdyn64::Operand::disp16(-8) };
        st.comment = "save x";
        out.emitInstr(st); // pops x
    }

    // q = x / 10
    {
        stackdyn64::Instruction ld;
        ld.mnemonic = stackdyn64::Mnemonic::ldfp;
        ld.operands = { stackdyn64::Operand::disp16(-8) };
        ld.comment = "reload x";
        out.emitInstr(ld);
    }
    emitPushImm(out, tvInt(10), "10");
    {
        stackdyn64::Instruction div;
        div.mnemonic = stackdyn64::Mnemonic::div;
        div.comment = "q = x/10";
        out.emitInstr(div);
    }

    // call self(q)
    emitPushImm(out, tvInt(0), "return slot");
    {
        stackdyn64::Instruction call;
        call.mnemonic = stackdyn64::Mnemonic::call;
        call.operands = { stackdyn64::Operand::codeLabel(FN) };
        call.comment = "recurse";
        const std::size_t line = out.codeSec().lines.size();
        out.image.fixups.push_back(stackdyn64::Fixup{out.codeSectionIndex, line, 0, FN, stackdyn64::LabelSpace::Code});
        out.emitInstr(call);
    }

    // cleanup recursive call (1 arg): spill ret, drop arg
    {
        stackdyn64::Instruction st;
        st.mnemonic = stackdyn64::Mnemonic::stfp;
        st.operands = { stackdyn64::Operand::disp16(-16) };
        st.comment = "spill recurse ret";
        out.emitInstr(st); // pops ret
    }
    {
        stackdyn64::Instruction drop;
        drop.mnemonic = stackdyn64::Mnemonic::drop;
        drop.comment = "drop recurse arg";
        out.emitInstr(drop);
    }

    // digit = x % 10
    {
        stackdyn64::Instruction ld;
        ld.mnemonic = stackdyn64::Mnemonic::ldfp;
        ld.operands = { stackdyn64::Operand::disp16(-8) };
        ld.comment = "reload x";
        out.emitInstr(ld);
    }
    emitPushImm(out, tvInt(10), "10");
    {
        stackdyn64::Instruction mod;
        mod.mnemonic = stackdyn64::Mnemonic::mod;
        mod.comment = "digit = x%10";
        out.emitInstr(mod);
    }

    // print digit
    emitPushImm(out, tvInt(0x30), "'0'");
    {
        stackdyn64::Instruction add;
        add.mnemonic = stackdyn64::Mnemonic::add;
        add.comment = "to ascii";
        out.emitInstr(add);
    }
    {
        stackdyn64::Instruction outb;
        outb.mnemonic = stackdyn64::Mnemonic::outb;
        outb.comment = "outb";
        out.emitInstr(outb);
    }

    // return 0
    emitPushImm(out, tvInt(0), "ret 0");
    {
        stackdyn64::Instruction st;
        st.mnemonic = stackdyn64::Mnemonic::stfp;
        st.operands = { stackdyn64::Operand::disp16(16) };
        st.comment = "write return slot";
        out.emitInstr(st);
    }
    {
        stackdyn64::Instruction r;
        r.mnemonic = stackdyn64::Mnemonic::ret;
        r.comment = "ret";
        out.emitInstr(r);
    }

    // Single-digit path: label
    out.emitCodeLabel(L_SINGLE, L_SINGLE);

    // Stack has [x]
    emitPushImm(out, tvInt(0x30), "'0'");
    {
        stackdyn64::Instruction add;
        add.mnemonic = stackdyn64::Mnemonic::add;
        add.comment = "to ascii";
        out.emitInstr(add);
    }
    {
        stackdyn64::Instruction outb;
        outb.mnemonic = stackdyn64::Mnemonic::outb;
        outb.comment = "outb";
        out.emitInstr(outb);
    }

    // return 0
    emitPushImm(out, tvInt(0), "ret 0");
    {
        stackdyn64::Instruction st;
        st.mnemonic = stackdyn64::Mnemonic::stfp;
        st.operands = { stackdyn64::Operand::disp16(16) };
        st.comment = "write return slot";
        out.emitInstr(st);
    }
    {
        stackdyn64::Instruction r;
        r.mnemonic = stackdyn64::Mnemonic::ret;
        r.comment = "ret";
        out.emitInstr(r);
    }
}

static void emitBuiltinReadInt(ImageBuilder& out) {
    const std::string FN = "__builtin_readInt";
    const std::string L_loop = "__builtin_readInt_loop";
    const std::string L_done = "__builtin_readInt_done";

    out.emitCodeLabel(FN, FN);

    // locals:
    // [bp-8]  acc
    // [bp-16] ch
    // [bp-24] digit
    emitPushImm(out, tvInt(0), "acc");
    emitPushImm(out, tvInt(0), "ch");
    emitPushImm(out, tvInt(0), "digit");

    // acc = 0
    emitPushImm(out, tvInt(0), "0");
    {
        stackdyn64::Instruction st;
        st.mnemonic = stackdyn64::Mnemonic::stfp;
        st.operands = { stackdyn64::Operand::disp16(-8) };
        st.comment = "acc=0";
        out.emitInstr(st);
    }

    out.emitCodeLabel(L_loop, L_loop);

    // setio stdin (0)
    {
        stackdyn64::Instruction s;
        s.mnemonic = stackdyn64::Mnemonic::setio;
        s.operands = { stackdyn64::Operand::imm8(0) };
        s.comment = "stdin";
        out.emitInstr(s);
    }
    // inb -> pushes ch
    {
        stackdyn64::Instruction in;
        in.mnemonic = stackdyn64::Mnemonic::inb;
        in.comment = "read byte";
        out.emitInstr(in);
    }
    // restore stdout (1)
    {
        stackdyn64::Instruction s;
        s.mnemonic = stackdyn64::Mnemonic::setio;
        s.operands = { stackdyn64::Operand::imm8(1) };
        s.comment = "stdout";
        out.emitInstr(s);
    }
    // store ch in local
    {
        stackdyn64::Instruction st;
        st.mnemonic = stackdyn64::Mnemonic::stfp;
        st.operands = { stackdyn64::Operand::disp16(-16) };
        st.comment = "save ch";
        out.emitInstr(st);
    }

    // if ch == '\n' (10) -> done
    {
        stackdyn64::Instruction ld;
        ld.mnemonic = stackdyn64::Mnemonic::ldfp;
        ld.operands = { stackdyn64::Operand::disp16(-16) };
        ld.comment = "load ch";
        out.emitInstr(ld);
    }
    emitPushImm(out, tvInt(10), "LF");
    {
        stackdyn64::Instruction eq;
        eq.mnemonic = stackdyn64::Mnemonic::eq;
        eq.comment = "ch==LF";
        out.emitInstr(eq);
    }
    emitJcc(out, /*jnz=*/true, L_done, "if LF -> done");

    // if ch < '0' -> done
    {
        stackdyn64::Instruction ld;
        ld.mnemonic = stackdyn64::Mnemonic::ldfp;
        ld.operands = { stackdyn64::Operand::disp16(-16) };
        ld.comment = "load ch";
        out.emitInstr(ld);
    }
    emitPushImm(out, tvInt(0x30), "'0'");
    {
        stackdyn64::Instruction lt;
        lt.mnemonic = stackdyn64::Mnemonic::lt;
        lt.comment = "ch<'0'";
        out.emitInstr(lt);
    }
    emitJcc(out, /*jnz=*/true, L_done, "if <'0' -> done");

    // if ch > '9' -> done
    {
        stackdyn64::Instruction ld;
        ld.mnemonic = stackdyn64::Mnemonic::ldfp;
        ld.operands = { stackdyn64::Operand::disp16(-16) };
        ld.comment = "load ch";
        out.emitInstr(ld);
    }
    emitPushImm(out, tvInt(0x39), "'9'");
    {
        stackdyn64::Instruction gt;
        gt.mnemonic = stackdyn64::Mnemonic::gt;
        gt.comment = "ch>'9'";
        out.emitInstr(gt);
    }
    emitJcc(out, /*jnz=*/true, L_done, "if >'9' -> done");

    // digit = ch - '0'
    {
        stackdyn64::Instruction ld;
        ld.mnemonic = stackdyn64::Mnemonic::ldfp;
        ld.operands = { stackdyn64::Operand::disp16(-16) };
        ld.comment = "load ch";
        out.emitInstr(ld);
    }
    emitPushImm(out, tvInt(0x30), "'0'");
    {
        stackdyn64::Instruction sub;
        sub.mnemonic = stackdyn64::Mnemonic::sub;
        sub.comment = "digit = ch-'0'";
        out.emitInstr(sub);
    }
    {
        stackdyn64::Instruction st;
        st.mnemonic = stackdyn64::Mnemonic::stfp;
        st.operands = { stackdyn64::Operand::disp16(-24) };
        st.comment = "save digit";
        out.emitInstr(st);
    }

    // acc = acc*10 + digit
    {
        stackdyn64::Instruction ld;
        ld.mnemonic = stackdyn64::Mnemonic::ldfp;
        ld.operands = { stackdyn64::Operand::disp16(-8) };
        ld.comment = "load acc";
        out.emitInstr(ld);
    }
    emitPushImm(out, tvInt(10), "10");
    {
        stackdyn64::Instruction mul;
        mul.mnemonic = stackdyn64::Mnemonic::mul;
        mul.comment = "acc*10";
        out.emitInstr(mul);
    }
    {
        stackdyn64::Instruction ld;
        ld.mnemonic = stackdyn64::Mnemonic::ldfp;
        ld.operands = { stackdyn64::Operand::disp16(-24) };
        ld.comment = "load digit";
        out.emitInstr(ld);
    }
    {
        stackdyn64::Instruction add;
        add.mnemonic = stackdyn64::Mnemonic::add;
        add.comment = "acc*10+digit";
        out.emitInstr(add);
    }
    {
        stackdyn64::Instruction st;
        st.mnemonic = stackdyn64::Mnemonic::stfp;
        st.operands = { stackdyn64::Operand::disp16(-8) };
        st.comment = "store acc";
        out.emitInstr(st);
    }

    // loop
    emitJmp(out, L_loop, "continue");

    // done:
    out.emitCodeLabel(L_done, L_done);

    // return acc in [bp+16]
    {
        stackdyn64::Instruction ld;
        ld.mnemonic = stackdyn64::Mnemonic::ldfp;
        ld.operands = { stackdyn64::Operand::disp16(-8) };
        ld.comment = "load acc";
        out.emitInstr(ld);
    }
    {
        stackdyn64::Instruction st;
        st.mnemonic = stackdyn64::Mnemonic::stfp;
        st.operands = { stackdyn64::Operand::disp16(16) };
        st.comment = "return acc";
        out.emitInstr(st);
    }
    {
        stackdyn64::Instruction r;
        r.mnemonic = stackdyn64::Mnemonic::ret;
        out.emitInstr(r);
    }
}

} // namespace

// =============================================================================
// Public entry point
// =============================================================================

CodeGenResult buildProgramImage(const CFGAnalysisResult& analysis) {
    CodeGenResult res;
    ImageBuilder out;

    // Entry label and runtime init
    out.emitCodeLabel("start", "start");

    // Initialize stack regs (a safe top-of-stack for 16-bit stackMem).
    {
        stackdyn64::Instruction ldsp;
        ldsp.mnemonic = stackdyn64::Mnemonic::ldsp;
        ldsp.operands = { stackdyn64::Operand::imm16(0xFF00) };
        ldsp.comment = "init sp";
        out.emitInstr(ldsp);

        stackdyn64::Instruction ldbp;
        ldbp.mnemonic = stackdyn64::Mnemonic::ldbp;
        ldbp.operands = { stackdyn64::Operand::imm16(0xFF00) };
        ldbp.comment = "init bp";
        out.emitInstr(ldbp);
    }

    // Enable output
    {
        stackdyn64::Instruction io;
        io.mnemonic = stackdyn64::Mnemonic::setio;
        io.operands = { stackdyn64::Operand::imm16(1) };
        io.comment = "enable io";
        out.emitInstr(io);
    }

    // Call main if present
    bool hasMain = false;
    for (const auto& fn : analysis.functions) {
        if (sanitizeLabel(fn.signature.name) == "main") { hasMain = true; break; }
    }
    if (hasMain) {
        emitPushImm(out, tvInt(0), "return slot");
        stackdyn64::Instruction call;
        call.mnemonic = stackdyn64::Mnemonic::call;
        call.operands = { stackdyn64::Operand::codeLabel(makeFunctionLabel("main")) };
        call.comment = "call main";
        const std::size_t line = out.codeSec().lines.size();
        out.image.fixups.push_back(stackdyn64::Fixup{out.codeSectionIndex, line, 0, "main", stackdyn64::LabelSpace::Code});
        out.emitInstr(call);

        // drop main return
        stackdyn64::Instruction drop;
        drop.mnemonic = stackdyn64::Mnemonic::drop;
        drop.comment = "drop main return";
        out.emitInstr(drop);
    }

    // Halt
    {
        stackdyn64::Instruction hlt;
        hlt.mnemonic = stackdyn64::Mnemonic::hlt;
        out.emitInstr(hlt);
    }
    out.image.entryLabel = "start";

    // Emit built-in helper routines
    emitBuiltinPrintInt(out);
    emitBuiltinReadInt(out);

    // Lower each function
    for (const auto& fn : analysis.functions) {
        lowerFunction(fn, out, res);
    }

    res.image = std::move(out.image);
    return res;
}

} // namespace stackdyn64_codegen