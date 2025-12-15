#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
#include <filesystem>

#include "src/parser/ParserModule.h"   // ParseResult, parseFromString
#include "src/cfg/CFGStructures.h"     // FileUnit, CFGAnalysisResult, FunctionInfo
#include "src/cfg/CFGBuild.h"          // buildControlFlowGraphs

#include "src/codegen/CodeGenModule.h" // buildProgramImage
#include "src/codegen/VMImageStructures.h"     // ProgramImage listing structures

#include "src/codegen/CodeGenModule.h" // stackdyn64_codegen::buildProgramImage

namespace fs = std::filesystem;

// ---------- Утилиты для DOT ----------

static std::string escapeDotString(const std::string& s) {
    std::string r;
    r.reserve(s.size());
    for (char c : s) {
        if (c == '"')  r += "\\\"";
        else if (c == '\n') r += "\\n";
        else if (c == '\r') { /* пропускаем */ }
        else r += c;
    }
    return r;
}

static std::string operationKindToString(OperationKind kind) {
    switch (kind) {
        case OperationKind::Nop:      return "Nop";
        case OperationKind::Assign:   return "Assign";
        case OperationKind::BinaryOp: return "BinaryOp";
        case OperationKind::UnaryOp:  return "UnaryOp";
        case OperationKind::Call:     return "Call";
        case OperationKind::VarDecl:  return "VarDecl";
    }
    return "Unknown";
}

static std::string operationToString(const OperationNodePtr& node, int depth = 0) {
    if (!node) return {};
    std::ostringstream oss;

    oss << operationKindToString(node->kind);
    if (!node->op.empty()) {
        oss << "(" << node->op << ")";
    }

    if (!node->operands.empty()) {
        oss << " [";
        bool first = true;
        for (const auto& op : node->operands) {
            if (!first) oss << ", ";
            first = false;
            oss << (op.kind == OperandKind::Variable ? "var:" :
                    op.kind == OperandKind::Constant ? "const:" : "tmp:")
                << op.value;
        }
        oss << "]";
    }

    if (!node->children.empty()) { 
        oss << " {";
        bool firstChild = true;
        for (const auto& ch : node->children) {
            if (!firstChild) oss << " | ";
            firstChild = false;
            oss << operationToString(ch, depth + 1);
        }
        oss << "}";
    }

    return oss.str();
}

static void writeCFGToDot(const FunctionInfo& func, std::ostream& out) {
    out << "digraph \"" << escapeDotString(func.signature.name) << "\" {\n";
    out << "  node [shape=box];\n";

    // Узлы блоков
    for (const auto& block : func.cfg.blocks) {
        if (!block) continue;
        std::ostringstream label;
        label << "B" << block->id;
        if (!block->label.empty()) {
            label << " (" << block->label << ")";
        }
        label << "\\n";

        for (const auto& op : block->operations) {
            label << escapeDotString(operationToString(op)) << "\\n";
        }

        out << "  \"" << block->id << "\" [label=\""
            << label.str() << "\"];\n";
    }

    // Рёбра
    for (const auto& block : func.cfg.blocks) {
        if (!block) continue;
        for (const auto& e : block->edges) {
            if (!e.target) continue;
            out << "  \"" << block->id << "\" -> \"" << e.target->id << "\"";
            if (e.kind == EdgeKind::TrueBranch) {
                out << " [label=\"T\"]";
            } else if (e.kind == EdgeKind::FalseBranch) {
                out << " [label=\"F\"]";
            }
            out << ";\n";
        }
    }

    out << "}\n";
}

// ---------- Построение графа вызовов по AST ----------

using CallGraph = std::map<std::string, std::set<std::string>>;

static void collectCallsFromAST(const ASTNodePtr& node,
                                const std::string& caller,
                                const std::set<std::string>& functionNames,
                                CallGraph& cg)
{
    if (!node) return;

    // Ищем вызовы: CallExpr( Identifier(<callee>), ... )
    if (node->name == "CallExpr" && !node->children.empty()) {
        auto calleeAst = node->children.front();
        if (calleeAst && calleeAst->name == "Identifier") {
            const std::string& callee = calleeAst->value;
            // считаем вызовом только если это действительно имя функции
            if (functionNames.count(callee)) {
                cg[caller].insert(callee);
            }
        }
    }

    // Обходим рекурсивно всех детей
    for (const auto& ch : node->children) {
        collectCallsFromAST(ch, caller, functionNames, cg);
    }
}


static void writeCallGraphToDot(const CallGraph& cg,
                                const std::set<std::string>& functionNames,
                                std::ostream& out)
{
    out << "digraph CallGraph {\n";
    out << "  node [shape=ellipse];\n";

    // Все функции как вершины
    for (const auto& f : functionNames) {
        out << "  \"" << escapeDotString(f) << "\";\n";
    }

    // Рёбра вызовов
    for (const auto& [caller, callees] : cg) {
        for (const auto& callee : callees) {
            out << "  \"" << escapeDotString(caller) << "\" -> \""
                << escapeDotString(callee) << "\";\n";
        }
    }

    out << "}\n";
}

// ---------- Assembly listing printer (ProgramImage -> asm-listing style) ----------

static const char* bankToString(stackdyn64::BankName b) {
    using B = stackdyn64::BankName;
    switch (b) {
        case B::code:     return "code";
        case B::dataMem:  return "dataMem";
        case B::stackMem: return "stackMem";
    }
    return "<bank>";
}

static const char* dataDirToString(stackdyn64::DataDirective d) {
    using D = stackdyn64::DataDirective;
    switch (d) {
        case D::db: return "db";
        case D::dw: return "dw";
        case D::dd: return "dd";
        case D::dq: return "dq";
    }
    return "db";
}

static const char* resDirToString(stackdyn64::ReserveDirective d) {
    using D = stackdyn64::ReserveDirective;
    switch (d) {
        case D::resb: return "resb";
        case D::resw: return "resw";
        case D::resd: return "resd";
        case D::resq: return "resq";
    }
    return "resb";
}

static std::string hexU64(std::uint64_t v, int width = 0) {
    std::ostringstream oss;
    oss << "0x" << std::hex << std::uppercase;
    if (width > 0) {
        oss << std::setw(width) << std::setfill('0');
    }
    oss << v;
    return oss.str();
}

static std::string operandToString(const stackdyn64::Operand& op) {
    using K = stackdyn64::OperandKind;
    switch (op.kind) {
        case K::Imm8:   return hexU64(static_cast<std::uint8_t>(op.imm), 2);
        case K::Imm16:  return hexU64(static_cast<std::uint16_t>(op.imm), 4);
        case K::Imm64:  return hexU64(static_cast<std::uint64_t>(op.imm), 16);
        case K::FrameDisp16: {
            // Keep signed displacement readable.
            return std::to_string(static_cast<std::int16_t>(op.imm));
        }
        case K::LabelRef:
            return op.label;
    }
    return "?";
}

static void printInstruction(std::ostream& out, const stackdyn64::Instruction& ins) {
    out << stackdyn64::toString(ins.mnemonic);
    if (!ins.operands.empty()) {
        out << " ";
        for (std::size_t i = 0; i < ins.operands.size(); ++i) {
            if (i) out << ", ";
            out << operandToString(ins.operands[i]);
        }
    }
    if (!ins.comment.empty()) {
        out << " ; " << ins.comment;
    }
    out << "\n";
}

static void printDataDef(std::ostream& out, const stackdyn64::DataDef& d) {
    out << dataDirToString(d.dir);
    if (!d.values.empty()) {
        out << " ";
        for (std::size_t i = 0; i < d.values.size(); ++i) {
            if (i) out << ", ";
            // Print values in natural width for the directive.
            const int w = (d.dir == stackdyn64::DataDirective::db) ? 2 :
                          (d.dir == stackdyn64::DataDirective::dw) ? 4 :
                          (d.dir == stackdyn64::DataDirective::dd) ? 8 : 16;
            out << hexU64(d.values[i], w);
        }
    }
    if (!d.comment.empty()) {
        out << " ; " << d.comment;
    }
    out << "\n";
}

static void printReserveDef(std::ostream& out, const stackdyn64::ReserveDef& r) {
    out << resDirToString(r.dir) << " " << r.count;
    if (!r.comment.empty()) {
        out << " ; " << r.comment;
    }
    out << "\n";
}

static void printLineItem(std::ostream& out, const stackdyn64::LineItem& li, int indent = 0);

static void printTimes(std::ostream& out, const stackdyn64::Times& t, int indent) {
    out << std::string(indent, ' ') << "times " << t.count << " ";
    // times payload is a single LineItem, but we only allow payload part (no label).
    stackdyn64::LineItem tmp = t.item;
    tmp.label.reset();
    // Print payload into a temporary buffer without newline indent tricks.
    std::ostringstream oss;
    printLineItem(oss, tmp, 0);
    std::string s = oss.str();
    // remove trailing newline
    if (!s.empty() && s.back() == '\n') s.pop_back();
    out << s;
    out << "\n";
}

static void printLineItem(std::ostream& out, const stackdyn64::LineItem& li, int indent) {
    // Label, if present, printed on its own line.
    if (li.label.has_value()) {
        out << std::string(indent, ' ') << li.label->rawName << ":\n";
    }

    const int payloadIndent = li.label.has_value() ? (indent + 2) : indent;
    out << std::string(payloadIndent, ' ');

    if (std::holds_alternative<stackdyn64::Instruction>(li.payload)) {
        printInstruction(out, std::get<stackdyn64::Instruction>(li.payload));
        return;
    }
    if (std::holds_alternative<stackdyn64::DataDef>(li.payload)) {
        printDataDef(out, std::get<stackdyn64::DataDef>(li.payload));
        return;
    }
    if (std::holds_alternative<stackdyn64::ReserveDef>(li.payload)) {
        printReserveDef(out, std::get<stackdyn64::ReserveDef>(li.payload));
        return;
    }
    if (std::holds_alternative<stackdyn64::CommentLine>(li.payload)) {
        const auto& c = std::get<stackdyn64::CommentLine>(li.payload);
        out << "; " << c.text << "\n";
        return;
    }
    if (std::holds_alternative<std::shared_ptr<stackdyn64::Times>>(li.payload)) {
        auto t = std::get<std::shared_ptr<stackdyn64::Times>>(li.payload);
        if (t) {
            // Re-print without the earlier payloadIndent prefix.
            // Remove the prefix we already output:
            // easiest: printTimes with indent and return, but we already printed spaces.
            // So, if we hit Times we re-do the line:
            //   1) back up: (not possible), therefore handle Times before prefix in callers.
        }
        out << "; <times?>\n";
        return;
    }

    out << "; <unknown line>\n";
}

static void printProgramImage(std::ostream& out, const stackdyn64::ProgramImage& img) {
    for (const auto& sec : img.sections) {
        out << "[section " << sec.decl.name;
        if (sec.decl.bank.has_value()) {
            out << ", " << bankToString(*sec.decl.bank);
        }
        out << "]\n\n";

        for (const auto& li : sec.lines) {
            // Special-case Times so we can print it on one line nicely.
            if (std::holds_alternative<std::shared_ptr<stackdyn64::Times>>(li.payload)) {
                // Label still printed on its own line.
                if (li.label.has_value()) {
                    out << li.label->rawName << ":\n";
                }
                auto t = std::get<std::shared_ptr<stackdyn64::Times>>(li.payload);
                if (t) {
                    printTimes(out, *t, li.label.has_value() ? 2 : 0);
                } else {
                    out << "; <null times>\n";
                }
                continue;
            }

            printLineItem(out, li, 0);
        }

        out << "\n";
    }
}

// ---------- main ----------

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Использование: " << argv[0]
                  << " <input1> [input2 ...] -o <out.asm> [--dump-cfg]\n";
        return 1;
    }

    std::vector<std::string> inputFiles;
    std::string outputAsmFile;
    bool dumpCfg = false;

    // Args:
    //   -o/--out/--output <file> : output assembly listing file
    //   --dump-cfg               : write CFG & callgraph DOT files (optional)
    // Everything else is treated as an input source file.
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-o" || arg == "--out" || arg == "--output") {
            if (i + 1 >= argc) {
                std::cerr << "Ошибка: после " << arg << " требуется имя выходного файла .asm\n";
                return 1;
            }
            outputAsmFile = argv[++i];
        } else if (arg == "--dump-cfg" || arg == "--cfg") {
            dumpCfg = true;
        } else {
            inputFiles.push_back(arg);
        }
    }

    if (inputFiles.empty()) {
        std::cerr << "Ошибка: не указаны входные файлы.\n";
        return 1;
    }

    if (outputAsmFile.empty()) {
        // default: place output next to first input
        fs::path p(inputFiles.front());
        outputAsmFile = (p.parent_path() / "out.asm").string();
    }

    bool hadErrors = false;

    // --- Шаг 1: синтаксический анализ всех файлов и построение AST ---

    std::vector<FileUnit> fileUnits;
    fileUnits.reserve(inputFiles.size());

    for (const auto& pathStr : inputFiles) {
        fs::path path(pathStr);

        std::ifstream in(path);
        if (!in.is_open()) {
            std::cerr << "Ошибка: не удалось открыть входной файл " << path << "\n";
            hadErrors = true;
            continue;
        }

        std::stringstream buffer;
        buffer << in.rdbuf();
        const std::string source = buffer.str();

        ParseResult pr = parseFromString(source);

        if (!pr.errors.empty()) {
            std::cerr << "Ошибки разбора в файле " << path << ":\n";
            for (const auto& msg : pr.errors) {
                std::cerr << "  " << msg << "\n";
            }
            hadErrors = true;
        }

        if (!pr.root) {
            std::cerr << "AST для файла " << path << " не построен, файл пропускается.\n";
            hadErrors = true;
            continue;
        }

        FileUnit fu;
        fu.fileName = path.string();
        fu.root = pr.root;
        fileUnits.push_back(std::move(fu));
    }

    if (fileUnits.empty()) {
        std::cerr << "Не удалось разобрать ни одного файла.\n";
        return 1;
    }

    // --- Шаг 2: построение CFG для всех подпрограмм ---

    CFGAnalysisResult analysis = buildControlFlowGraphs(fileUnits);

    if (!analysis.errors.empty()) {
        for (const auto& err : analysis.errors) {
            std::cerr << "Ошибка CFG";
            if (!err.fileName.empty()) std::cerr << " в файле " << err.fileName;
            if (!err.functionName.empty()) std::cerr << ", функция " << err.functionName;
            std::cerr << ": " << err.message << "\n";
        }
        hadErrors = true;
    }

    // --- Шаг 3 (опционально): вывод CFG каждой подпрограммы в отдельный файл ---

    fs::path outAsmPath(outputAsmFile);
    fs::path outDirPath = outAsmPath.parent_path();
    if (outDirPath.empty()) outDirPath = fs::current_path();

    if (dumpCfg) {
        std::error_code ec;
        fs::create_directories(outDirPath, ec); // если уже существует — ок

        for (const auto& func : analysis.functions) {
            fs::path srcPath(func.sourceFile);

            std::string srcName = srcPath.stem().string();
            std::string funcName = func.signature.name;
            fs::path dotPath = outDirPath / (srcName + "." + funcName + ".dot");

            std::ofstream out(dotPath);
            if (!out.is_open()) {
                std::cerr << "Ошибка: не удалось создать файл CFG " << dotPath << "\n";
                hadErrors = true;
                continue;
            }

            writeCFGToDot(func, out);
            std::cerr << "CFG функции " << funcName << " записан в " << dotPath << "\n";
        }
    }

    // --- Шаг 4 (опционально): построение графа вызовов по всем подпрограммам ---

    std::set<std::string> functionNames;
    for (const auto& func : analysis.functions) {
        functionNames.insert(func.signature.name);
    }

    CallGraph cg;

    for (const auto& func : analysis.functions) {
        if (!func.funcAst) continue;
        collectCallsFromAST(func.funcAst,
                            func.signature.name,
                            functionNames,
                            cg);
    }

    if (dumpCfg) {
        std::error_code ec;
        fs::create_directories(outDirPath, ec);

        fs::path callGraphPath = outDirPath / "callgraph.dot";
        std::ofstream out(callGraphPath);
        if (!out.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл графа вызовов " << callGraphPath << "\n";
            hadErrors = true;
        } else {
            writeCallGraphToDot(cg, functionNames, out);
            std::cerr << "Граф вызовов записан в " << callGraphPath << "\n";
        }
    }

    // --- Шаг 5: CodeGen -> ProgramImage ---

    stackdyn64_codegen::CodeGenResult gen = stackdyn64_codegen::buildProgramImage(analysis);

    // --- Шаг 6: вывести ассемблерный листинг в выходной файл ---

    {
        std::error_code ec;
        fs::create_directories(outDirPath, ec);

        std::ofstream out(outAsmPath);
        if (!out.is_open()) {
            std::cerr << "Ошибка: не удалось открыть выходной файл " << outAsmPath << "\n";
            return 1;
        }

        printProgramImage(out, gen.image);
        std::cerr << "Листинг записан в " << outAsmPath << "\n";
    }

    return hadErrors ? 1 : 0;
}