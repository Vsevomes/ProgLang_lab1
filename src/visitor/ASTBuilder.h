#pragma once
#include "../../generated/LangVisitor.h"
#include "../../generated/LangParser.h"
#include "../ast/AST.h"
#include <memory>

class ASTBuilder : public LangVisitor {
public:
    ASTBuilder() = default;

    // Реализация всех методов, перечисленных в LangVisitor
    std::any visitSource(LangParser::SourceContext *ctx) override;
    std::any visitSourceItem(LangParser::SourceItemContext *ctx) override;
    std::any visitFuncDef(LangParser::FuncDefContext *ctx) override;
    std::any visitFuncSignature(LangParser::FuncSignatureContext *ctx) override;
    std::any visitArgList(LangParser::ArgListContext *ctx) override;
    std::any visitArgDef(LangParser::ArgDefContext *ctx) override;
    std::any visitCustomTypeRef(LangParser::CustomTypeRefContext *ctx) override;
    std::any visitArrayTypeRef(LangParser::ArrayTypeRefContext *ctx) override;
    std::any visitBuiltinTypeRef(LangParser::BuiltinTypeRefContext *ctx) override;
    std::any visitTypeArgList(LangParser::TypeArgListContext *ctx) override;
    std::any visitVarDecl(LangParser::VarDeclContext *ctx) override;
    std::any visitIfStmt(LangParser::IfStmtContext *ctx) override;
    std::any visitWhileStmt(LangParser::WhileStmtContext *ctx) override;
    std::any visitDoLoopStmt(LangParser::DoLoopStmtContext *ctx) override;
    std::any visitBreakStmt(LangParser::BreakStmtContext *ctx) override;
    std::any visitExprStmt(LangParser::ExprStmtContext *ctx) override;
    std::any visitIdentifierList(LangParser::IdentifierListContext *ctx) override;
    std::any visitUnaryExpr(LangParser::UnaryExprContext *ctx) override;
    std::any visitPrimaryExpr(LangParser::PrimaryExprContext *ctx) override;
    std::any visitAddExpr(LangParser::AddExprContext *ctx) override;
    std::any visitMulExpr(LangParser::MulExprContext *ctx) override;
    std::any visitOrExpr(LangParser::OrExprContext *ctx) override;
    std::any visitAssignExpr(LangParser::AssignExprContext *ctx) override;
    std::any visitAndExpr(LangParser::AndExprContext *ctx) override;
    std::any visitCompareExpr(LangParser::CompareExprContext *ctx) override;
    std::any visitPrimary(LangParser::PrimaryContext *ctx) override;
    std::any visitArgExprList(LangParser::ArgExprListContext *ctx) override;
    std::any visitAtom(LangParser::AtomContext *ctx) override;
    std::any visitLiteral(LangParser::LiteralContext *ctx) override;
    std::any visitIdentifier(LangParser::IdentifierContext *ctx) override;
    std::any visitBuiltinType(LangParser::BuiltinTypeContext *ctx) override;
};
