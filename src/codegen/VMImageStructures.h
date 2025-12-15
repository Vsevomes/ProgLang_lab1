#pragma once

// ============================================================================
// VMImageStructures.h
//
// Data structures for representing a program *image* (CODE + dataMem) and a
// structured assembly *listing* for the target VM "stackdyn64".
//
// This file is meant for project integration (task part 1):
//   (a) For each instruction: mnemonic name + operands in terms of this VM.
//   (b) For each data element: either a literal value or a reserved size.
//
// The *textual* look of the final listing (sections, labels, db/dw/dd/dq,
// resb/resw/resd/resq, times, comments) is described in asm-listing.pdf.
// These structures keep enough information to print exactly in that style.
// ============================================================================

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <memory>

namespace stackdyn64 {

// =============================================================================
// 1) Target VM mnemonics (MUST match stackdyn64.target.pdsl)
// =============================================================================

enum class Mnemonic {
    // control / termination
    nop,
    hlt,
    jmp,
    jz,
    jnz,
    call,
    ret,

    // stack / data movement / constants
    ldsp,
    ldbp,
    push,
    dup,
    drop,
    swap,
    load,
    store,
    ldfp,
    stfp,

    // arithmetic / compare / logical
    add,
    sub,
    mul,
    div,
    mod,
    eq,
    neq,
    lt,
    gt,
    le,
    ge,
    land,
    lor,
    lnot,
    neg,

    // io
    setio,
    inb,
    outb,
};

inline const char* toString(Mnemonic m) {
    switch (m) {
        case Mnemonic::nop:   return "nop";
        case Mnemonic::hlt:   return "hlt";
        case Mnemonic::jmp:   return "jmp";
        case Mnemonic::jz:    return "jz";
        case Mnemonic::jnz:   return "jnz";
        case Mnemonic::call:  return "call";
        case Mnemonic::ret:   return "ret";
        case Mnemonic::ldsp:  return "ldsp";
        case Mnemonic::ldbp:  return "ldbp";
        case Mnemonic::push:  return "push";
        case Mnemonic::dup:   return "dup";
        case Mnemonic::drop:  return "drop";
        case Mnemonic::swap:  return "swap";
        case Mnemonic::load:  return "load";
        case Mnemonic::store: return "store";
        case Mnemonic::ldfp:  return "ldfp";
        case Mnemonic::stfp:  return "stfp";
        case Mnemonic::add:   return "add";
        case Mnemonic::sub:   return "sub";
        case Mnemonic::mul:   return "mul";
        case Mnemonic::div:   return "div";
        case Mnemonic::mod:   return "mod";
        case Mnemonic::eq:    return "eq";
        case Mnemonic::neq:   return "neq";
        case Mnemonic::lt:    return "lt";
        case Mnemonic::gt:    return "gt";
        case Mnemonic::le:    return "le";
        case Mnemonic::ge:    return "ge";
        case Mnemonic::land:  return "land";
        case Mnemonic::lor:   return "lor";
        case Mnemonic::lnot:  return "lnot";
        case Mnemonic::neg:   return "neg";
        case Mnemonic::setio: return "setio";
        case Mnemonic::inb:   return "inb";
        case Mnemonic::outb:  return "outb";
    }
    return "<unknown>";
}

// =============================================================================
// 2) Operands (in terms of this VM)
// =============================================================================

// Where a symbolic label lives (needed for fixups and for printing).
enum class LabelSpace { Code, Data };

// In PDSL the ISA uses imm8/imm16/imm64 fields. We keep those distinctions.
// LabelRef is the "symbolic" form that later becomes Imm16.
enum class OperandKind {
    Imm8,
    Imm16,
    Imm64,
    FrameDisp16,  // signed 16-bit displacement for ldfp/stfp
    LabelRef      // label reference; resolves to a 16-bit address
};

struct Operand {
    OperandKind kind{OperandKind::Imm16};

    // For Imm* and FrameDisp16.
    // (Validation of width/range should be done by assembler/emitter.)
    std::int64_t imm{0};

    // For LabelRef.
    std::string label;
    LabelSpace  labelSpace{LabelSpace::Code};

    static Operand imm8(std::uint8_t v)  { return Operand{OperandKind::Imm8,  v, {}, LabelSpace::Code}; }
    static Operand imm16(std::uint16_t v){ return Operand{OperandKind::Imm16, v, {}, LabelSpace::Code}; }
    static Operand imm64(std::uint64_t v){ return Operand{OperandKind::Imm64, static_cast<std::int64_t>(v), {}, LabelSpace::Code}; }
    static Operand disp16(std::int16_t d){ return Operand{OperandKind::FrameDisp16, d, {}, LabelSpace::Code}; }
    static Operand codeLabel(std::string l){ return Operand{OperandKind::LabelRef, 0, std::move(l), LabelSpace::Code}; }
    static Operand dataLabel(std::string l){ return Operand{OperandKind::LabelRef, 0, std::move(l), LabelSpace::Data}; }
};

// =============================================================================
// 3) Listing line payloads (instructions + data directives)
// =============================================================================

// Requirement 1(a): mnemonic + operand list.
struct Instruction {
    Mnemonic mnemonic{Mnemonic::nop};
    std::vector<Operand> operands;   // printed as: <mnem> op1, op2, ...
    std::string comment;            // printed as: ; ...
};

// --- Data definitions (db/dw/dd/dq) ---

enum class DataDirective { db, dw, dd, dq };

inline constexpr std::size_t unitSize(DataDirective d) {
    switch (d) {
        case DataDirective::db: return 1;
        case DataDirective::dw: return 2;
        case DataDirective::dd: return 4;
        case DataDirective::dq: return 8;
    }
    return 1;
}

// Requirement 1(b) literal: db/dw/dd/dq <values...>
struct DataDef {
    DataDirective dir{DataDirective::db};
    // Values are stored as 64-bit and truncated/validated by emitter based on dir size.
    std::vector<std::uint64_t> values;
    std::string comment;
};

// --- Reservation (resb/resw/resd/resq) ---

enum class ReserveDirective { resb, resw, resd, resq };

inline constexpr std::size_t unitSize(ReserveDirective d) {
    switch (d) {
        case ReserveDirective::resb: return 1;
        case ReserveDirective::resw: return 2;
        case ReserveDirective::resd: return 4;
        case ReserveDirective::resq: return 8;
    }
    return 1;
}

// Requirement 1(b) size: res* <count>
struct ReserveDef {
    ReserveDirective dir{ReserveDirective::resb};
    std::uint64_t count{0};
    std::string comment;

    constexpr std::uint64_t totalBytes() const {
        return count * static_cast<std::uint64_t>(unitSize(dir));
    }
};

// --- Labels and comments ---

// Label with raw textual spelling and a fully-qualified name.
// Local labels in the listing may start with '.' and are scoped to the latest
// non-local label. Keep both forms so the printer can reproduce raw text while
// the linker uses qualifiedName.
struct Label {
    std::string rawName;        // as printed, e.g. ".loop" or "start"
    std::string qualifiedName;  // resolved scope name, e.g. "fun.loop"
};

struct CommentLine {
    std::string text; // without leading ';'
};

// --- times N <something> ---

struct Times; // forward

// A single line in a section. A line may optionally start with a label.
struct LineItem {
    std::optional<Label> label;

    // Exactly one payload per line (matches listing concept).
    std::variant<
        Instruction,
        DataDef,
        ReserveDef,
        CommentLine,
        std::shared_ptr<Times>
    > payload;
};

struct Times {
    std::uint64_t count{0};
    LineItem item; // the repeated payload
};

// =============================================================================
// 4) Sections (for listing and for memory placement)
// =============================================================================

// Memory banks from the VM architecture description.
enum class BankName { code, dataMem, stackMem };

// Listing directive: [section <name>[, <bank>[, <startAddr>]]]
struct SectionDecl {
    std::string name;                          // e.g. "_code", "_data"
    std::optional<BankName> bank;              // optional bank override
    std::optional<std::uint16_t> startAddr;    // optional absolute start in that bank
};

struct Section {
    SectionDecl decl;
    std::vector<LineItem> lines;
};

// =============================================================================
// 5) Program image (sections + labels + fixups)
// =============================================================================

struct LabelInfo {
    LabelSpace space{LabelSpace::Code};
    std::uint16_t address{0};
};

// Patch-table entry: which instruction operand needs label resolution.
struct Fixup {
    std::size_t sectionIndex{0};
    std::size_t lineIndex{0};
    std::size_t operandIndex{0};
    std::string targetLabel;      // should be qualifiedName
    LabelSpace  targetSpace{LabelSpace::Code};
};

struct ProgramImage {
    std::vector<Section> sections;

    // Optional convenience metadata.
    std::optional<std::string> entryLabel;   // symbol name (before resolution)
    std::optional<std::uint16_t> entryPoint; // address after resolution

    // Filled by a later layout/link step (next parts of the task).
    std::unordered_map<std::string, LabelInfo> labels;
    std::vector<Fixup> fixups;
};

} // namespace stackdyn64
