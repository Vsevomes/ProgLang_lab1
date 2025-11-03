#include "ASTBuilder.h"
#include <iostream>

using ASTNodePtr = std::shared_ptr<ASTNode>;

// --- Утилита ---
static ASTNodePtr makeNode(const std::string &name, const std::string &value = "") {
    return std::make_shared<ASTNode>(name, value);
}

// ---------------- Source / SourceItem ----------------
std::any ASTBuilder::visitSource(LangParser::SourceContext *ctx) {
    auto root = makeNode("Source");
    for (auto si : ctx->sourceItem()) {
        if (auto child = std::any_cast<ASTNodePtr>(visit(si)); child)
            root->children.push_back(child);
    }
    return root;
}

std::any ASTBuilder::visitSourceItem(LangParser::SourceItemContext *ctx) {
    if (ctx->funcDef()) return visit(ctx->funcDef());
    return std::any();
}

// ---------------- Function ----------------
std::any ASTBuilder::visitFuncDef(LangParser::FuncDefContext *ctx) {
    std::string fname;
    if (ctx->funcSignature() && ctx->funcSignature()->identifier())
        fname = ctx->funcSignature()->identifier()->getText();

    auto node = makeNode("FuncDef", fname);

    if (ctx->funcSignature())
        node->children.push_back(std::any_cast<ASTNodePtr>(visit(ctx->funcSignature())));

    for (auto s : ctx->statement()) {
        if (auto child = std::any_cast<ASTNodePtr>(visit(s)); child)
            node->children.push_back(child);
    }

    return node;
}

std::any ASTBuilder::visitFuncSignature(LangParser::FuncSignatureContext *ctx) {
    auto node = makeNode("FuncSignature", ctx->identifier()->getText());
    if (ctx->argList())
        node->children.push_back(std::any_cast<ASTNodePtr>(visit(ctx->argList())));
    if (ctx->typeRef())
        node->children.push_back(std::any_cast<ASTNodePtr>(visit(ctx->typeRef())));
    return node;
}

// ---------------- Args ----------------
std::any ASTBuilder::visitArgList(LangParser::ArgListContext *ctx) {
    auto node = makeNode("ArgList");
    for (auto a : ctx->argDef())
        node->children.push_back(std::any_cast<ASTNodePtr>(visit(a)));
    return node;
}

std::any ASTBuilder::visitArgDef(LangParser::ArgDefContext *ctx) {
    auto node = makeNode("ArgDef", ctx->identifier()->getText());
    if (ctx->typeRef()) node->children.push_back(std::any_cast<ASTNodePtr>(visit(ctx->typeRef())));
    return node;
}

// ---------------- TypeRefs ----------------
std::any ASTBuilder::visitBuiltinTypeRef(LangParser::BuiltinTypeRefContext *ctx) {
    return visit(ctx->builtinType());
}

std::any ASTBuilder::visitCustomTypeRef(LangParser::CustomTypeRefContext *ctx) {
    return makeNode("CustomTypeRef", ctx->identifier()->getText());
}

std::any ASTBuilder::visitArrayTypeRef(LangParser::ArrayTypeRefContext *ctx) {
    auto node = makeNode("ArrayTypeRef");
    node->children.push_back(std::any_cast<ASTNodePtr>(visit(ctx->typeRef())));
    if (ctx->typeArgList()) node->children.push_back(std::any_cast<ASTNodePtr>(visit(ctx->typeArgList())));
    return node;
}

std::any ASTBuilder::visitTypeArgList(LangParser::TypeArgListContext *ctx) {
    auto node = makeNode("TypeArgList");
    for (auto t : ctx->typeRef()) node->children.push_back(std::any_cast<ASTNodePtr>(visit(t)));
    return node;
}

// ---------------- Statements ----------------
std::any ASTBuilder::visitVarDecl(LangParser::VarDeclContext *ctx) {
    auto node = makeNode("VarDecl");
    if (ctx->identifierList()) node->children.push_back(std::any_cast<ASTNodePtr>(visit(ctx->identifierList())));
    if (ctx->typeRef()) node->children.push_back(std::any_cast<ASTNodePtr>(visit(ctx->typeRef())));
    return node;
}

std::any ASTBuilder::visitIfStmt(LangParser::IfStmtContext *ctx) {
    auto node = makeNode("IfStmt");

    // условие
    if (ctx->expr())
        node->children.push_back(std::any_cast<ASTNodePtr>(visit(ctx->expr())));

    auto thenNode = makeNode("Then");
    auto elseNode = makeNode("Else");

    for (auto s : ctx->statement()) {
        auto child = std::any_cast<ASTNodePtr>(visit(s));
        // если токен ELSE присутствует и statement начинается после ELSE — это else
        if (ctx->ELSE() && s->getStart()->getTokenIndex() > ctx->ELSE()->getSymbol()->getTokenIndex()) {
            elseNode->children.push_back(child);
        } else {
            thenNode->children.push_back(child);
        }
    }

    node->children.push_back(thenNode);
    if (!elseNode->children.empty())
        node->children.push_back(elseNode);

    return std::any(node);
}

std::any ASTBuilder::visitWhileStmt(LangParser::WhileStmtContext *ctx) {
    auto node = makeNode("WhileStmt");
    if (ctx->expr()) node->children.push_back(std::any_cast<ASTNodePtr>(visit(ctx->expr())));
    for (auto s : ctx->statement()) node->children.push_back(std::any_cast<ASTNodePtr>(visit(s)));
    return node;
}

std::any ASTBuilder::visitDoLoopStmt(LangParser::DoLoopStmtContext *ctx) {
    auto node = std::make_shared<ASTNode>("DoLoopStmt");

    // Добавляем все операторы тела цикла
    for (auto stmtCtx : ctx->statement()) {
        node->children.push_back(std::any_cast<ASTNodePtr>(visit(stmtCtx)));
    }

    // Определяем, есть ли условие (WHILE expr или UNTIL expr)
    if (ctx->expr()) {
        auto condNode = std::any_cast<ASTNodePtr>(visit(ctx->expr()));

        // Если условие не CompareExpr — создаём CompareExpr вручную
        std::shared_ptr<ASTNode> compareNode;
        if (condNode->name != "CompareExpr") {
            compareNode = std::make_shared<ASTNode>("CompareExpr");
            compareNode->children.push_back(condNode);
        } else {
            compareNode = condNode;
        }

        // Добавляем информацию о типе условия
        if (ctx->WHILE()) {
            compareNode->value = "WHILE";
        } else if (ctx->UNTIL()) {
            compareNode->value = "UNTIL";
        }

        node->children.push_back(compareNode);
    }

    return node;
}



std::any ASTBuilder::visitBreakStmt(LangParser::BreakStmtContext *ctx) {
    return makeNode("BreakStmt");
}

std::any ASTBuilder::visitExprStmt(LangParser::ExprStmtContext *ctx) {
    if (!ctx->expr()) return std::any();
    return visit(ctx->expr());
}

// ---------------- IdentifierList ----------------
std::any ASTBuilder::visitIdentifierList(LangParser::IdentifierListContext *ctx) {
    auto node = makeNode("IdentifierList");
    for (auto id : ctx->identifier()) node->children.push_back(makeNode("Identifier", id->getText()));
    return node;
}

// ---------------- Expressions ----------------
std::any ASTBuilder::visitAssignExpr(LangParser::AssignExprContext *ctx) {
    auto node = makeNode("AssignExpr");
    if (ctx->expr().size() >= 2) {
        auto left  = std::any_cast<ASTNodePtr>(visit(ctx->expr(0)));
        auto right = std::any_cast<ASTNodePtr>(visit(ctx->expr(1)));
        if (left)  node->children.push_back(left);
        if (right) node->children.push_back(right);
    }
    return node;
}

std::any ASTBuilder::visitAddExpr(LangParser::AddExprContext *ctx) {
    auto node = makeNode(ctx->ADD() ? "AddExpr" : "SubExpr");
    for (auto e : ctx->expr()) {
        auto child = std::any_cast<ASTNodePtr>(visit(e));
        if (child) node->children.push_back(child);
    }
    return node;
}

std::any ASTBuilder::visitMulExpr(LangParser::MulExprContext *ctx) {
    auto node = makeNode(ctx->MUL() ? "MulExpr" : "DivExpr");
    for (auto e : ctx->expr()) {
        auto child = std::any_cast<ASTNodePtr>(visit(e));
        if (child) node->children.push_back(child);
    }
    return node;
}

std::any ASTBuilder::visitAndExpr(LangParser::AndExprContext *ctx) {
    auto node = makeNode("AndExpr");
    for (auto e : ctx->expr()) {
        auto child = std::any_cast<ASTNodePtr>(visit(e));
        if (child) node->children.push_back(child);
    }
    return node;
}

std::any ASTBuilder::visitOrExpr(LangParser::OrExprContext *ctx) {
    auto node = makeNode("OrExpr");
    for (auto e : ctx->expr()) {
        auto child = std::any_cast<ASTNodePtr>(visit(e));
        if (child) node->children.push_back(child);
    }
    return node;
}

std::any ASTBuilder::visitCompareExpr(LangParser::CompareExprContext *ctx) {
    auto node = makeNode("CompareExpr");
    for (auto e : ctx->expr()) {
        auto child = std::any_cast<ASTNodePtr>(visit(e));
        if (child) node->children.push_back(child);
    }
    return node;
}

std::any ASTBuilder::visitUnaryExpr(LangParser::UnaryExprContext *ctx) {
    auto node = makeNode("UnaryExpr");
    if (ctx->expr()) {
        auto child = std::any_cast<ASTNodePtr>(visit(ctx->expr()));
        if (child) node->children.push_back(child);
    }
    return node;
}


std::any ASTBuilder::visitPrimaryExpr(LangParser::PrimaryExprContext *ctx) {
    // PrimaryExpr содержит один PrimaryContext
    if (ctx->primary()) {
        return visit(ctx->primary());
    }
    return std::any();
}

std::any ASTBuilder::visitPrimary(LangParser::PrimaryContext *ctx) {
    if (ctx->atom()) return visit(ctx->atom());
    if (!ctx->argExprList().empty()) {
        // аргументы функций
        auto node = makeNode("ArgExprListContainer");
        for (auto args : ctx->argExprList()) {
            auto child = std::any_cast<ASTNodePtr>(visit(args));
            if (child) node->children.push_back(child);
        }
        return node;
    }
    return std::any();
}

std::any ASTBuilder::visitArgExprList(LangParser::ArgExprListContext *ctx) {
    auto node = makeNode("ArgExprList");
    for (auto e : ctx->expr()) {
        auto child = std::any_cast<ASTNodePtr>(visit(e));
        if (child) node->children.push_back(child);
    }
    return node;
}

std::any ASTBuilder::visitAtom(LangParser::AtomContext *ctx) {
    if (ctx->identifier()) return visit(ctx->identifier());
    if (ctx->literal()) return visit(ctx->literal());
    if (ctx->expr()) return visit(ctx->expr());
    return makeNode("Atom", ctx->getText());
}

std::any ASTBuilder::visitLiteral(LangParser::LiteralContext *ctx) {
    if (ctx->BOOL()) return makeNode("Literal", ctx->BOOL()->getText());
    if (ctx->STRING()) return makeNode("Literal", ctx->STRING()->getText());
    if (ctx->CHAR()) return makeNode("Literal", ctx->CHAR()->getText());
    if (ctx->HEX()) return makeNode("Literal", ctx->HEX()->getText());
    if (ctx->BITS()) return makeNode("Literal", ctx->BITS()->getText());
    if (ctx->DEC()) return makeNode("Literal", ctx->DEC()->getText());
    return makeNode("Literal");
}

std::any ASTBuilder::visitIdentifier(LangParser::IdentifierContext *ctx) {
    if (ctx->Identifier()) return makeNode("Identifier", ctx->Identifier()->getText());
    return std::any();
}

std::any ASTBuilder::visitBuiltinType(LangParser::BuiltinTypeContext *ctx) {
    return makeNode("BuiltinType", ctx->getText());
}
