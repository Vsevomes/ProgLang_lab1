#pragma once

#include "CFGStructures.h"
#include <vector>

// Строит CFG для всех функций во всех файлах.
CFGAnalysisResult buildControlFlowGraphs(const std::vector<FileUnit>& files);
