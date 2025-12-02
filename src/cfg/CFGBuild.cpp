// src/cfg/CFGBuild.cpp
#include "CFGBuild.h"

#include <stdexcept>

// ---------- Вспомогательные структуры ----------

struct LoopContext {
    BasicBlockPtr continueTarget; // пока не используем, но пригодится для continue
    BasicBlockPtr breakTarget;
};

struct BuildContext {
    ControlFlowGraph& cfg;
    int nextBlockId = 0;
    std::vector<LoopContext> loopStack;
    std::string fileName;
    std::string funcName;
    std::vector<CFGError>& errors;
};

// Создать новый базовый блок
static BasicBlockPtr newBlock(BuildContext& ctx, const std::string& label) {
    auto b = std::make_shared<BasicBlock>();
    b->id = ctx.nextBlockId++;
    b->label = label;
    ctx.cfg.blocks.push_back(b);
    return b;
}

// ---------- Построение операций ----------

static OperationNodePtr buildExprOperation(const ASTNodePtr& node);

// VarDecl: "dim a, b as int"
static OperationNodePtr buildVarDeclOperation(const ASTNodePtr& stmt) {
    if (!stmt) return nullptr;
    auto opNode = std::make_shared<OperationNode>();
    opNode->kind = OperationKind::VarDecl;
    opNode->op   = "dim";

    ASTNodePtr idList;
    ASTNodePtr typeRef;

    for (const auto& ch : stmt->children) {
        if (!ch) continue;
        if (ch->name == "IdentifierList") {
            idList = ch;
        } else if (!typeRef) {
            typeRef = ch;
        }
    }

    // тип кладём в op
    if (typeRef) {
        if (!typeRef->value.empty()) {
            opNode->op = typeRef->value;
        } else {
            opNode->op = typeRef->name;
        }
    }

    // идентификаторы — в operands
    if (idList) {
        for (const auto& idNode : idList->children) {
            if (!idNode) continue;
            if (idNode->name == "Identifier") {
                Operand varOp;
                varOp.kind  = OperandKind::Variable;
                varOp.value = idNode->value;
                opNode->operands.push_back(varOp);
            }
        }
    }

    return opNode;
}

// Построение дерева операций для выражения
static OperationNodePtr buildExprOperation(const ASTNodePtr& node) {
    if (!node) return nullptr;

    const std::string& name = node->name;

    // Присваивание: AssignExpr(left, right)
    if (name == "AssignExpr") {
        auto opNode = std::make_shared<OperationNode>();
        opNode->kind = OperationKind::Assign;
        opNode->op   = "=";
        for (const auto& ch : node->children) {
            auto childOp = buildExprOperation(ch);
            if (childOp) opNode->children.push_back(childOp);
        }
        return opNode;
    }

    // Бинарные выражения (Add/Sub/Mul/Div/And/Or/CompareExpr)
    if (name == "AddExpr" || name == "SubExpr" ||
        name == "MulExpr" || name == "DivExpr" ||
        name == "AndExpr" || name == "OrExpr" ||
        name == "CompareExpr") {

        auto opNode = std::make_shared<OperationNode>();
        opNode->kind = OperationKind::BinaryOp;
        opNode->op   = name; // вид операции (с точностью до типа AST-узла)

        for (const auto& ch : node->children) {
            auto childOp = buildExprOperation(ch);
            if (childOp) opNode->children.push_back(childOp);
        }
        return opNode;
    }

    // Унарное выражение: UnaryExpr(child)
    if (name == "UnaryExpr") {
        auto opNode = std::make_shared<OperationNode>();
        opNode->kind = OperationKind::UnaryOp;
        opNode->op   = "UnaryExpr";
        if (!node->children.empty()) {
            auto childOp = buildExprOperation(node->children.front());
            if (childOp) opNode->children.push_back(childOp);
        }
        return opNode;
    }

    // Вызов / индексатор: CallExpr( base, ArgExprList... )
    if (name == "CallExpr") {
        auto opNode = std::make_shared<OperationNode>();
        opNode->kind = OperationKind::Call;
        opNode->op   = "call";

        if (!node->children.empty()) {
            // первый ребёнок — база вызова (обычно Identifier с именем функции)
            auto calleeAst = node->children.front();
            auto calleeOp  = buildExprOperation(calleeAst);
            if (calleeOp) opNode->children.push_back(calleeOp);

            // если это Identifier и его имя нам пригодится — сохраним его прямо в op
            if (calleeAst && calleeAst->name == "Identifier") {
                opNode->op = calleeAst->value; // имя функции
            }

            // остальные дети — списки аргументов/выражения
            for (size_t i = 1; i < node->children.size(); ++i) {
                auto argListAst = node->children[i];
                if (!argListAst) continue;
                for (const auto& argExprAst : argListAst->children) {
                    auto argOp = buildExprOperation(argExprAst);
                    if (argOp) opNode->children.push_back(argOp);
                }
            }
        }

        return opNode;
    }

    // Литерал
    if (name == "Literal") {
        auto opNode = std::make_shared<OperationNode>();
        opNode->kind = OperationKind::Nop;
        opNode->op   = "Literal";
        Operand c;
        c.kind  = OperandKind::Constant;
        c.value = node->value; // текст литерала
        opNode->operands.push_back(c);
        return opNode;
    }

    // Идентификатор
    if (name == "Identifier") {
        auto opNode = std::make_shared<OperationNode>();
        opNode->kind = OperationKind::Nop;
        opNode->op   = "Identifier";
        Operand v;
        v.kind  = OperandKind::Variable;
        v.value = node->value; // имя переменной
        opNode->operands.push_back(v);
        return opNode;
    }

    // PrimaryExpr / Primary / Atom — просто обёртки вокруг вложенного expr/identifier/literal
    if ((name == "PrimaryExpr" || name == "Primary" || name == "Atom") &&
        !node->children.empty()) {
        return buildExprOperation(node->children.front());
    }

    // По умолчанию: просто пробрасываем имя и рекурсивно строим детей
    auto opNode = std::make_shared<OperationNode>();
    opNode->kind = OperationKind::Nop;
    opNode->op   = name;
    for (const auto& ch : node->children) {
        auto childOp = buildExprOperation(ch);
        if (childOp) opNode->children.push_back(childOp);
    }
    return opNode;
}

// ---------- Сигнатура функции и тело ----------

static FunctionSignature buildSignatureFromAST(const ASTNodePtr& funcDef) {
    FunctionSignature sig;
    if (!funcDef) return sig;

    sig.name = funcDef->value; // FuncDef(value = имя функции)

    ASTNodePtr signatureNode;
    for (const auto& ch : funcDef->children) {
        if (ch && ch->name == "FuncSignature") {
            signatureNode = ch;
            break;
        }
    }
    if (!signatureNode) return sig;

    for (const auto& ch : signatureNode->children) {
        if (!ch) continue;
        if (ch->name == "ArgList") {
            for (const auto& arg : ch->children) {
                if (!arg) continue;
                // ArgDef(value = имя параметра)
                sig.paramNames.push_back(arg->value);
            }
        } else if (sig.returnType.empty()) {
            sig.returnType = ch->name;
            if (!ch->value.empty()) {
                sig.returnType += ":" + ch->value;
            }
        }
    }

    return sig;
}

// Собираем операторы тела функции (после FuncSignature)
static std::vector<ASTNodePtr> collectFunctionBody(const ASTNodePtr& funcDef) {
    std::vector<ASTNodePtr> body;
    if (!funcDef) return body;

    bool afterSignature = false;
    for (const auto& ch : funcDef->children) {
        if (!ch) continue;
        if (!afterSignature) {
            if (ch->name == "FuncSignature") {
                afterSignature = true;
            }
            continue;
        }
        body.push_back(ch);
    }
    return body;
}

// ---------- Объявления билдеров операторов ----------

static BasicBlockPtr buildStatementsSequence(const std::vector<ASTNodePtr>& stmts,
                                             BuildContext& ctx,
                                             BasicBlockPtr current);
static BasicBlockPtr buildStatement(const ASTNodePtr& stmt,
                                    BuildContext& ctx,
                                    BasicBlockPtr current);

// ---------- Построение CFG для одной функции ----------

static ControlFlowGraph buildCFGForFunction(const ASTNodePtr& funcDef,
                                            const std::string& fileName,
                                            std::vector<CFGError>& errors) {
    ControlFlowGraph cfg;
    BuildContext ctx{cfg, 0, {}, fileName, funcDef ? funcDef->value : "", errors};

    cfg.entry = newBlock(ctx, "entry");
    cfg.exit  = newBlock(ctx, "exit");

    auto bodyStmts = collectFunctionBody(funcDef);

    // функция без тела (прототип)
    if (bodyStmts.empty()) {
        cfg.entry->edges.push_back({EdgeKind::Fallthrough, cfg.exit});
        return cfg;
    }

    BasicBlockPtr last = cfg.entry;
    last = buildStatementsSequence(bodyStmts, ctx, last);

    // "нормальный" выход в конец функции
    if (last && !last->isTerminal) {
        last->edges.push_back({EdgeKind::Fallthrough, cfg.exit});
    }

    return cfg;
}

// ---------- Публичная функция анализа всех файлов ----------

CFGAnalysisResult buildControlFlowGraphs(const std::vector<FileUnit>& files) {
    CFGAnalysisResult result;

    for (const auto& file : files) {
        if (!file.root) {
            result.errors.push_back({
                file.fileName,
                "",
                "Пустой корневой AST (ожидался узел Source)",
                -1, -1
            });
            continue;
        }

        if (file.root->name != "Source") {
            result.errors.push_back({
                file.fileName,
                "",
                "Корневой узел AST должен быть Source",
                -1, -1
            });
            continue;
        }

        for (const auto& child : file.root->children) {
            if (!child) continue;
            if (child->name != "FuncDef") continue;

            FunctionInfo f;
            f.signature = buildSignatureFromAST(child);
            f.sourceFile = file.fileName;
            f.funcAst = child;

            try {
                f.cfg = buildCFGForFunction(child, file.fileName, result.errors);
                result.functions.push_back(std::move(f));
            } catch (const std::exception& ex) {
                result.errors.push_back({
                    file.fileName,
                    f.signature.name,
                    std::string("Исключение при построении CFG: ") + ex.what(),
                    -1, -1
                });
            }
        }
    }

    return result;
}

// ---------- Обработка управляющих конструкций ----------

static BasicBlockPtr buildIfStmt(const ASTNodePtr& stmt,
                                 BuildContext& ctx,
                                 BasicBlockPtr current) {
    if (!stmt || !current) return current;

    ASTNodePtr condNode;
    ASTNodePtr thenNode;
    ASTNodePtr elseNode;

    if (!stmt->children.empty()) {
        condNode = stmt->children[0];
    }
    if (stmt->children.size() >= 2) {
        thenNode = stmt->children[1];
    }
    if (stmt->children.size() >= 3) {
        elseNode = stmt->children[2];
    }

    // условие в текущем блоке
    if (condNode) {
        auto condOp = buildExprOperation(condNode);
        if (condOp) current->operations.push_back(condOp);
    }

    auto joinBlock = newBlock(ctx, "if.join");

    // THEN-ветка
    BasicBlockPtr thenEntry = newBlock(ctx, "if.then");
    current->edges.push_back({EdgeKind::TrueBranch, thenEntry});

    BasicBlockPtr thenExit = thenEntry;
    if (thenNode) {
        thenExit = buildStatementsSequence(thenNode->children, ctx, thenEntry);
    }
    if (thenExit && !thenExit->isTerminal) {
        thenExit->edges.push_back({EdgeKind::Fallthrough, joinBlock});
    }

    // ELSE-ветка
    if (elseNode) {
        BasicBlockPtr elseEntry = newBlock(ctx, "if.else");
        current->edges.push_back({EdgeKind::FalseBranch, elseEntry});

        BasicBlockPtr elseExit = buildStatementsSequence(elseNode->children, ctx, elseEntry);
        if (elseExit && !elseExit->isTerminal) {
            elseExit->edges.push_back({EdgeKind::Fallthrough, joinBlock});
        }
    } else {
        // без else — ложная ветка сразу в join
        current->edges.push_back({EdgeKind::FalseBranch, joinBlock});
    }

    return joinBlock;
}

static BasicBlockPtr buildWhileStmt(const ASTNodePtr& stmt,
                                    BuildContext& ctx,
                                    BasicBlockPtr current) {
    if (!stmt || !current) return current;

    ASTNodePtr condNode;
    std::vector<ASTNodePtr> bodyStmts;

    if (!stmt->children.empty()) {
        condNode = stmt->children[0];
        bodyStmts.assign(stmt->children.begin() + 1, stmt->children.end());
    }

    auto condBlock  = newBlock(ctx, "while.cond");
    auto bodyBlock  = newBlock(ctx, "while.body");
    auto afterBlock = newBlock(ctx, "while.after");

    current->edges.push_back({EdgeKind::Fallthrough, condBlock});

    if (condNode) {
        auto condOp = buildExprOperation(condNode);
        if (condOp) condBlock->operations.push_back(condOp);
    }

    condBlock->edges.push_back({EdgeKind::TrueBranch, bodyBlock});
    condBlock->edges.push_back({EdgeKind::FalseBranch, afterBlock});

    ctx.loopStack.push_back(LoopContext{condBlock, afterBlock});

    BasicBlockPtr bodyExit = buildStatementsSequence(bodyStmts, ctx, bodyBlock);
    if (bodyExit && !bodyExit->isTerminal) {
        bodyExit->edges.push_back({EdgeKind::Fallthrough, condBlock});
    }

    ctx.loopStack.pop_back();

    return afterBlock;
}

static BasicBlockPtr buildDoLoopStmt(const ASTNodePtr& stmt,
                                     BuildContext& ctx,
                                     BasicBlockPtr current) {
    if (!stmt || !current) return current;

    std::vector<ASTNodePtr> bodyStmts;
    ASTNodePtr condNode;

    if (stmt->children.empty()) {
        return current;
    }

    // В ASTBuilder: сначала операторы тела, в конце (опционально) CompareExpr с value "WHILE"/"UNTIL"
    if (stmt->children.back()->name == "CompareExpr") {
        condNode = stmt->children.back();
        bodyStmts.assign(stmt->children.begin(), stmt->children.end() - 1);
    } else {
        bodyStmts = stmt->children;
    }

    auto bodyEntry  = newBlock(ctx, "do.body");
    auto afterBlock = newBlock(ctx, "do.after");

    current->edges.push_back({EdgeKind::Fallthrough, bodyEntry});

    ctx.loopStack.push_back(LoopContext{bodyEntry, afterBlock});

    BasicBlockPtr bodyExit = buildStatementsSequence(bodyStmts, ctx, bodyEntry);

    if (condNode && bodyExit && !bodyExit->isTerminal) {
        auto condOp = buildExprOperation(condNode);
        if (condOp) bodyExit->operations.push_back(condOp);

        const std::string mode = condNode->value; // "WHILE" или "UNTIL"

        if (mode == "WHILE") {
            bodyExit->edges.push_back({EdgeKind::TrueBranch, bodyEntry});
            bodyExit->edges.push_back({EdgeKind::FalseBranch, afterBlock});
        } else if (mode == "UNTIL") {
            bodyExit->edges.push_back({EdgeKind::TrueBranch, afterBlock});
            bodyExit->edges.push_back({EdgeKind::FalseBranch, bodyEntry});
        } else {
            ctx.errors.push_back({
                ctx.fileName,
                ctx.funcName,
                "Неизвестный режим DoLoopStmt (ожидался WHILE или UNTIL)",
                -1, -1
            });
            bodyExit->edges.push_back({EdgeKind::Fallthrough, afterBlock});
        }
    }

    ctx.loopStack.pop_back();

    return afterBlock;
}

static BasicBlockPtr buildBreakStmt(const ASTNodePtr& /*stmt*/,
                                    BuildContext& ctx,
                                    BasicBlockPtr current) {
    if (!current) return nullptr;

    if (ctx.loopStack.empty()) {
        ctx.errors.push_back({
            ctx.fileName,
            ctx.funcName,
            "Оператор break вне цикла",
            -1, -1
        });
        return current;
    }

    auto target = ctx.loopStack.back().breakTarget;

    auto breakOp = std::make_shared<OperationNode>();
    breakOp->kind = OperationKind::Nop;
    breakOp->op   = "break";
    current->operations.push_back(breakOp);

    current->edges.push_back({EdgeKind::Fallthrough, target});
    current->isTerminal = true;

    // дальнейшие операторы в этой последовательности — недостижимы
    return nullptr;
}

// Один оператор
static BasicBlockPtr buildStatement(const ASTNodePtr& stmt,
                                    BuildContext& ctx,
                                    BasicBlockPtr current) {
    if (!stmt || !current) return current;

    const std::string& name = stmt->name;

    if (name == "VarDecl") {
        auto op = buildVarDeclOperation(stmt);
        if (op) current->operations.push_back(op);
        return current;
    }

    if (name == "IfStmt") {
        return buildIfStmt(stmt, ctx, current);
    }

    if (name == "WhileStmt") {
        return buildWhileStmt(stmt, ctx, current);
    }

    if (name == "DoLoopStmt") {
        return buildDoLoopStmt(stmt, ctx, current);
    }

    if (name == "BreakStmt") {
        return buildBreakStmt(stmt, ctx, current);
    }

    // Остальное считаем оператором-выражением
    auto exprOp = buildExprOperation(stmt);
    if (exprOp) current->operations.push_back(exprOp);
    return current;
}

// Последовательность операторов
static BasicBlockPtr buildStatementsSequence(const std::vector<ASTNodePtr>& stmts,
                                             BuildContext& ctx,
                                             BasicBlockPtr current) {
    BasicBlockPtr last = current;

    for (const auto& stmt : stmts) {
        if (!last) {
            // недостижимый код после break/бесконечного цикла
            continue;
        }
        last = buildStatement(stmt, ctx, last);
    }

    return last;
}
