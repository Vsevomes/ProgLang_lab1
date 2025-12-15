#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "../cfg/CFGStructures.h"
#include "VMImageStructures.h"

namespace stackdyn64_codegen {

// Where variables live in the function's frame.
//
// Frame layout convention used by this codegen:
//   After 'call', BP points to saved caller BP at [bp+0], return IP at [bp+8].
//   Return value slot is at [bp+16] (as required by the VM spec).
//   Parameters start at [bp+24] (first parameter), then +8 each.
//   Locals are allocated by pushing zero-initialized cells in the prolog and
//   addressed with negative displacements: -8, -16, ...
struct FrameLayout {
    std::unordered_map<std::string, std::int16_t> localDisp; // name -> disp (negative)
    std::unordered_map<std::string, std::int16_t> paramDisp; // name -> disp (positive)
    std::size_t localCount{0};
};

// Linear codegen result for a set of functions.
struct CodeGenResult {
    stackdyn64::ProgramImage image;
    // Per-function frame metadata (useful for debugging, later passes).
    std::unordered_map<std::string, FrameLayout> frames;
};

// Main entry point:
//  - input: CFGs + signatures (CFGAnalysisResult from CFGBuild)
//  - output: ProgramImage (structures from task 1)
CodeGenResult buildProgramImage(const CFGAnalysisResult& analysis);

} // namespace stackdyn64_codegen
