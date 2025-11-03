
// Generated from Lang.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "LangParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by LangParser.
 */
class  LangListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterSource(LangParser::SourceContext *ctx) = 0;
  virtual void exitSource(LangParser::SourceContext *ctx) = 0;

  virtual void enterSourceItem(LangParser::SourceItemContext *ctx) = 0;
  virtual void exitSourceItem(LangParser::SourceItemContext *ctx) = 0;

  virtual void enterFuncDef(LangParser::FuncDefContext *ctx) = 0;
  virtual void exitFuncDef(LangParser::FuncDefContext *ctx) = 0;

  virtual void enterFuncSignature(LangParser::FuncSignatureContext *ctx) = 0;
  virtual void exitFuncSignature(LangParser::FuncSignatureContext *ctx) = 0;

  virtual void enterArgList(LangParser::ArgListContext *ctx) = 0;
  virtual void exitArgList(LangParser::ArgListContext *ctx) = 0;

  virtual void enterArgDef(LangParser::ArgDefContext *ctx) = 0;
  virtual void exitArgDef(LangParser::ArgDefContext *ctx) = 0;

  virtual void enterCustomTypeRef(LangParser::CustomTypeRefContext *ctx) = 0;
  virtual void exitCustomTypeRef(LangParser::CustomTypeRefContext *ctx) = 0;

  virtual void enterArrayTypeRef(LangParser::ArrayTypeRefContext *ctx) = 0;
  virtual void exitArrayTypeRef(LangParser::ArrayTypeRefContext *ctx) = 0;

  virtual void enterBuiltinTypeRef(LangParser::BuiltinTypeRefContext *ctx) = 0;
  virtual void exitBuiltinTypeRef(LangParser::BuiltinTypeRefContext *ctx) = 0;

  virtual void enterTypeArgList(LangParser::TypeArgListContext *ctx) = 0;
  virtual void exitTypeArgList(LangParser::TypeArgListContext *ctx) = 0;

  virtual void enterVarDecl(LangParser::VarDeclContext *ctx) = 0;
  virtual void exitVarDecl(LangParser::VarDeclContext *ctx) = 0;

  virtual void enterIfStmt(LangParser::IfStmtContext *ctx) = 0;
  virtual void exitIfStmt(LangParser::IfStmtContext *ctx) = 0;

  virtual void enterWhileStmt(LangParser::WhileStmtContext *ctx) = 0;
  virtual void exitWhileStmt(LangParser::WhileStmtContext *ctx) = 0;

  virtual void enterDoLoopStmt(LangParser::DoLoopStmtContext *ctx) = 0;
  virtual void exitDoLoopStmt(LangParser::DoLoopStmtContext *ctx) = 0;

  virtual void enterBreakStmt(LangParser::BreakStmtContext *ctx) = 0;
  virtual void exitBreakStmt(LangParser::BreakStmtContext *ctx) = 0;

  virtual void enterExprStmt(LangParser::ExprStmtContext *ctx) = 0;
  virtual void exitExprStmt(LangParser::ExprStmtContext *ctx) = 0;

  virtual void enterIdentifierList(LangParser::IdentifierListContext *ctx) = 0;
  virtual void exitIdentifierList(LangParser::IdentifierListContext *ctx) = 0;

  virtual void enterUnaryExpr(LangParser::UnaryExprContext *ctx) = 0;
  virtual void exitUnaryExpr(LangParser::UnaryExprContext *ctx) = 0;

  virtual void enterPrimaryExpr(LangParser::PrimaryExprContext *ctx) = 0;
  virtual void exitPrimaryExpr(LangParser::PrimaryExprContext *ctx) = 0;

  virtual void enterAddExpr(LangParser::AddExprContext *ctx) = 0;
  virtual void exitAddExpr(LangParser::AddExprContext *ctx) = 0;

  virtual void enterMulExpr(LangParser::MulExprContext *ctx) = 0;
  virtual void exitMulExpr(LangParser::MulExprContext *ctx) = 0;

  virtual void enterOrExpr(LangParser::OrExprContext *ctx) = 0;
  virtual void exitOrExpr(LangParser::OrExprContext *ctx) = 0;

  virtual void enterAssignExpr(LangParser::AssignExprContext *ctx) = 0;
  virtual void exitAssignExpr(LangParser::AssignExprContext *ctx) = 0;

  virtual void enterAndExpr(LangParser::AndExprContext *ctx) = 0;
  virtual void exitAndExpr(LangParser::AndExprContext *ctx) = 0;

  virtual void enterCompareExpr(LangParser::CompareExprContext *ctx) = 0;
  virtual void exitCompareExpr(LangParser::CompareExprContext *ctx) = 0;

  virtual void enterPrimary(LangParser::PrimaryContext *ctx) = 0;
  virtual void exitPrimary(LangParser::PrimaryContext *ctx) = 0;

  virtual void enterArgExprList(LangParser::ArgExprListContext *ctx) = 0;
  virtual void exitArgExprList(LangParser::ArgExprListContext *ctx) = 0;

  virtual void enterAtom(LangParser::AtomContext *ctx) = 0;
  virtual void exitAtom(LangParser::AtomContext *ctx) = 0;

  virtual void enterLiteral(LangParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(LangParser::LiteralContext *ctx) = 0;

  virtual void enterIdentifier(LangParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(LangParser::IdentifierContext *ctx) = 0;

  virtual void enterBuiltinType(LangParser::BuiltinTypeContext *ctx) = 0;
  virtual void exitBuiltinType(LangParser::BuiltinTypeContext *ctx) = 0;


};

