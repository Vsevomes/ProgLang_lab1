
// Generated from Lang.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "LangParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by LangParser.
 */
class  LangVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by LangParser.
   */
    virtual std::any visitSource(LangParser::SourceContext *context) = 0;

    virtual std::any visitSourceItem(LangParser::SourceItemContext *context) = 0;

    virtual std::any visitFuncDef(LangParser::FuncDefContext *context) = 0;

    virtual std::any visitFuncSignature(LangParser::FuncSignatureContext *context) = 0;

    virtual std::any visitArgList(LangParser::ArgListContext *context) = 0;

    virtual std::any visitArgDef(LangParser::ArgDefContext *context) = 0;

    virtual std::any visitCustomTypeRef(LangParser::CustomTypeRefContext *context) = 0;

    virtual std::any visitArrayTypeRef(LangParser::ArrayTypeRefContext *context) = 0;

    virtual std::any visitBuiltinTypeRef(LangParser::BuiltinTypeRefContext *context) = 0;

    virtual std::any visitTypeArgList(LangParser::TypeArgListContext *context) = 0;

    virtual std::any visitVarDecl(LangParser::VarDeclContext *context) = 0;

    virtual std::any visitIfStmt(LangParser::IfStmtContext *context) = 0;

    virtual std::any visitWhileStmt(LangParser::WhileStmtContext *context) = 0;

    virtual std::any visitDoLoopStmt(LangParser::DoLoopStmtContext *context) = 0;

    virtual std::any visitBreakStmt(LangParser::BreakStmtContext *context) = 0;

    virtual std::any visitExprStmt(LangParser::ExprStmtContext *context) = 0;

    virtual std::any visitIdentifierList(LangParser::IdentifierListContext *context) = 0;

    virtual std::any visitUnaryExpr(LangParser::UnaryExprContext *context) = 0;

    virtual std::any visitPrimaryExpr(LangParser::PrimaryExprContext *context) = 0;

    virtual std::any visitAddExpr(LangParser::AddExprContext *context) = 0;

    virtual std::any visitMulExpr(LangParser::MulExprContext *context) = 0;

    virtual std::any visitOrExpr(LangParser::OrExprContext *context) = 0;

    virtual std::any visitAssignExpr(LangParser::AssignExprContext *context) = 0;

    virtual std::any visitAndExpr(LangParser::AndExprContext *context) = 0;

    virtual std::any visitCompareExpr(LangParser::CompareExprContext *context) = 0;

    virtual std::any visitPrimary(LangParser::PrimaryContext *context) = 0;

    virtual std::any visitArgExprList(LangParser::ArgExprListContext *context) = 0;

    virtual std::any visitAtom(LangParser::AtomContext *context) = 0;

    virtual std::any visitLiteral(LangParser::LiteralContext *context) = 0;

    virtual std::any visitIdentifier(LangParser::IdentifierContext *context) = 0;

    virtual std::any visitBuiltinType(LangParser::BuiltinTypeContext *context) = 0;


};

