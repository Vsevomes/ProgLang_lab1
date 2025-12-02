#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../ast/AST.h"

// 1. Операнды и операции (деревья операций внутри базовых блоков)

enum class OperandKind {
    Variable,   // имя переменной
    Constant,   // литерал
    Temporary   // что-то служебное / вычисленное
};

struct Operand {
    OperandKind kind = OperandKind::Variable;
    std::string value;
};

enum class OperationKind {
    Nop,        // просто узел/обёртка
    Assign,     // присваивание (=)
    BinaryOp,   // бинарные операции (+, -, *, /, and, or, сравнение и т.д.)
    UnaryOp,    // унарная операция (unOp expr)
    Call,       // вызов/индексатор
    VarDecl     // dim ... as ...
};

struct OperationNode {
    OperationKind kind = OperationKind::Nop;
    std::string op;                        // имя операции (например, "AddExpr", "=" или "Literal")
    std::vector<Operand> operands;         // плоские операнды (идентификаторы, литералы)
    std::vector<std::shared_ptr<OperationNode>> children; // вложенные операции/выражения
};

using OperationNodePtr = std::shared_ptr<OperationNode>;

// 2. CFG: базовые блоки и рёбра

enum class EdgeKind {
    Fallthrough, // обычный переход по потоку
    TrueBranch,  // ветка по условию == true
    FalseBranch  // ветка по условию == false
};

struct BasicBlock;
using BasicBlockPtr = std::shared_ptr<BasicBlock>;

struct CFGEdge {
    EdgeKind kind = EdgeKind::Fallthrough;
    BasicBlockPtr target;
};

struct BasicBlock {
    int id = -1;                     // уникальный ID внутри функции
    std::string label;               // метка: "entry", "while.body1" и т.п.
    std::vector<OperationNodePtr> operations; // дерево(а) операций этого блока
    std::vector<CFGEdge> edges;      // исходящие переходы
    bool isTerminal = false;         // из блока дальнейший контроль не идёт (break, бесконечный цикл и т.д.)
};

struct ControlFlowGraph {
    std::vector<BasicBlockPtr> blocks;
    BasicBlockPtr entry;             // входной блок
    BasicBlockPtr exit;              // синтетический выходной блок (для визуализации/анализа)
};

// 3. Подпрограммы

struct FunctionSignature {
    std::string name;
    std::vector<std::string> paramNames;
    std::string returnType;
};

struct FunctionInfo {
    FunctionSignature signature;
    std::string sourceFile;
    ControlFlowGraph cfg;
    ASTNodePtr funcAst;              // узел FuncDef из AST
};

// 4. Входные файлы (имя + AST)

struct FileUnit {
    std::string fileName;
    ASTNodePtr root;                 // корень "Source"
};

// 5. Ошибки и результат анализа

struct CFGError {
    std::string fileName;
    std::string functionName;
    std::string message;
    int line   = -1; // координаты можно будет добавить, если расширишь ASTNode
    int column = -1;
};

struct CFGAnalysisResult {
    std::vector<FunctionInfo> functions; // все разобранные подпрограммы
    std::vector<CFGError> errors;        // ошибки анализа CFG
};
