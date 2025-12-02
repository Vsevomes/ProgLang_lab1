#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <filesystem>

#include "src/parser/ParserModule.h"   // ParseResult, parseFromString
#include "src/cfg/CFGStructures.h"     // FileUnit, CFGAnalysisResult, FunctionInfo
#include "src/cfg/CFGBuild.h"          // buildControlFlowGraphs

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

// ---------- main ----------

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Использование: " << argv[0]
                  << " <input1> [input2 ...] [-o <output_dir>]\n";
        return 1;
    }

    std::vector<std::string> inputFiles;
    std::string outputDir;

    // Разбор аргументов: все, что не -o/--out, считаем входными файлами
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-o" || arg == "--out" || arg == "--output") {
            if (i + 1 >= argc) {
                std::cerr << "Ошибка: после " << arg << " требуется директория вывода.\n";
                return 1;
            }
            outputDir = argv[++i];
        } else {
            inputFiles.push_back(arg);
        }
    }

    if (inputFiles.empty()) {
        std::cerr << "Ошибка: не указаны входные файлы.\n";
        return 1;
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

    // --- Шаг 3: вывод CFG каждой подпрограммы в отдельный файл ---

    for (const auto& func : analysis.functions) {
        fs::path srcPath(func.sourceFile);
        fs::path outDirPath;

        if (!outputDir.empty()) {
            outDirPath = fs::path(outputDir);
        } else {
            outDirPath = srcPath.parent_path(); // по-умолчанию — директория исходника
        }

        std::error_code ec;
        fs::create_directories(outDirPath, ec); // если уже существует — ок

        std::string srcName = srcPath.stem().string();          // sourceName
        std::string funcName = func.signature.name;             // functionName
        fs::path outPath = outDirPath / (srcName + "." + funcName + ".dot");

        std::ofstream out(outPath);
        if (!out.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл CFG " << outPath << "\n";
            hadErrors = true;
            continue;
        }

        writeCFGToDot(func, out);
        std::cerr << "CFG функции " << funcName << " записан в " << outPath << "\n";
    }

    // --- Шаг 4: построение графа вызовов по всем подпрограммам ---

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

    // Определяем директорию для файла графа вызовов
    fs::path callGraphDir;
    std::string mainSourceFile;

    for (const auto& func : analysis.functions) {
        if (func.signature.name == "main") {
            mainSourceFile = func.sourceFile;
            break;
        }
    }

    if (!outputDir.empty()) {
        callGraphDir = fs::path(outputDir);
    } else if (!mainSourceFile.empty()) {
        callGraphDir = fs::path(mainSourceFile).parent_path();
    } else {
        // fallback: директория первого входного файла
        callGraphDir = fs::path(inputFiles.front()).parent_path();
    }

    std::error_code ec;
    fs::create_directories(callGraphDir, ec);

    fs::path callGraphPath = callGraphDir / "callgraph.dot";

    {
        std::ofstream out(callGraphPath);
        if (!out.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл графа вызовов " << callGraphPath << "\n";
            hadErrors = true;
        } else {
            writeCallGraphToDot(cg, functionNames, out);
            std::cerr << "Граф вызовов записан в " << callGraphPath << "\n";
        }
    }

    return hadErrors ? 1 : 0;
}
