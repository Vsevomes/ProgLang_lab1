
// Generated from Lang.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "LangVisitor.h"


/**
 * This class provides an empty implementation of LangVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  LangBaseVisitor : public LangVisitor {
public:

  virtual std::any visitSource(LangParser::SourceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSourceItem(LangParser::SourceItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDef(LangParser::FuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncSignature(LangParser::FuncSignatureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgList(LangParser::ArgListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgDef(LangParser::ArgDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCustomTypeRef(LangParser::CustomTypeRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayTypeRef(LangParser::ArrayTypeRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBuiltinTypeRef(LangParser::BuiltinTypeRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeArgList(LangParser::TypeArgListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDecl(LangParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStmt(LangParser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStmt(LangParser::WhileStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDoLoopStmt(LangParser::DoLoopStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStmt(LangParser::BreakStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprStmt(LangParser::ExprStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierList(LangParser::IdentifierListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpr(LangParser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpr(LangParser::PrimaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddExpr(LangParser::AddExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulExpr(LangParser::MulExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrExpr(LangParser::OrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignExpr(LangParser::AssignExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAndExpr(LangParser::AndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCompareExpr(LangParser::CompareExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary(LangParser::PrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgExprList(LangParser::ArgExprListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAtom(LangParser::AtomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(LangParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifier(LangParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBuiltinType(LangParser::BuiltinTypeContext *ctx) override {
    return visitChildren(ctx);
  }


};

