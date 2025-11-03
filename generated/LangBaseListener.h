
// Generated from Lang.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "LangListener.h"


/**
 * This class provides an empty implementation of LangListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  LangBaseListener : public LangListener {
public:

  virtual void enterSource(LangParser::SourceContext * /*ctx*/) override { }
  virtual void exitSource(LangParser::SourceContext * /*ctx*/) override { }

  virtual void enterSourceItem(LangParser::SourceItemContext * /*ctx*/) override { }
  virtual void exitSourceItem(LangParser::SourceItemContext * /*ctx*/) override { }

  virtual void enterFuncDef(LangParser::FuncDefContext * /*ctx*/) override { }
  virtual void exitFuncDef(LangParser::FuncDefContext * /*ctx*/) override { }

  virtual void enterFuncSignature(LangParser::FuncSignatureContext * /*ctx*/) override { }
  virtual void exitFuncSignature(LangParser::FuncSignatureContext * /*ctx*/) override { }

  virtual void enterArgList(LangParser::ArgListContext * /*ctx*/) override { }
  virtual void exitArgList(LangParser::ArgListContext * /*ctx*/) override { }

  virtual void enterArgDef(LangParser::ArgDefContext * /*ctx*/) override { }
  virtual void exitArgDef(LangParser::ArgDefContext * /*ctx*/) override { }

  virtual void enterCustomTypeRef(LangParser::CustomTypeRefContext * /*ctx*/) override { }
  virtual void exitCustomTypeRef(LangParser::CustomTypeRefContext * /*ctx*/) override { }

  virtual void enterArrayTypeRef(LangParser::ArrayTypeRefContext * /*ctx*/) override { }
  virtual void exitArrayTypeRef(LangParser::ArrayTypeRefContext * /*ctx*/) override { }

  virtual void enterBuiltinTypeRef(LangParser::BuiltinTypeRefContext * /*ctx*/) override { }
  virtual void exitBuiltinTypeRef(LangParser::BuiltinTypeRefContext * /*ctx*/) override { }

  virtual void enterTypeArgList(LangParser::TypeArgListContext * /*ctx*/) override { }
  virtual void exitTypeArgList(LangParser::TypeArgListContext * /*ctx*/) override { }

  virtual void enterVarDecl(LangParser::VarDeclContext * /*ctx*/) override { }
  virtual void exitVarDecl(LangParser::VarDeclContext * /*ctx*/) override { }

  virtual void enterIfStmt(LangParser::IfStmtContext * /*ctx*/) override { }
  virtual void exitIfStmt(LangParser::IfStmtContext * /*ctx*/) override { }

  virtual void enterWhileStmt(LangParser::WhileStmtContext * /*ctx*/) override { }
  virtual void exitWhileStmt(LangParser::WhileStmtContext * /*ctx*/) override { }

  virtual void enterDoLoopStmt(LangParser::DoLoopStmtContext * /*ctx*/) override { }
  virtual void exitDoLoopStmt(LangParser::DoLoopStmtContext * /*ctx*/) override { }

  virtual void enterBreakStmt(LangParser::BreakStmtContext * /*ctx*/) override { }
  virtual void exitBreakStmt(LangParser::BreakStmtContext * /*ctx*/) override { }

  virtual void enterExprStmt(LangParser::ExprStmtContext * /*ctx*/) override { }
  virtual void exitExprStmt(LangParser::ExprStmtContext * /*ctx*/) override { }

  virtual void enterIdentifierList(LangParser::IdentifierListContext * /*ctx*/) override { }
  virtual void exitIdentifierList(LangParser::IdentifierListContext * /*ctx*/) override { }

  virtual void enterUnaryExpr(LangParser::UnaryExprContext * /*ctx*/) override { }
  virtual void exitUnaryExpr(LangParser::UnaryExprContext * /*ctx*/) override { }

  virtual void enterPrimaryExpr(LangParser::PrimaryExprContext * /*ctx*/) override { }
  virtual void exitPrimaryExpr(LangParser::PrimaryExprContext * /*ctx*/) override { }

  virtual void enterAddExpr(LangParser::AddExprContext * /*ctx*/) override { }
  virtual void exitAddExpr(LangParser::AddExprContext * /*ctx*/) override { }

  virtual void enterMulExpr(LangParser::MulExprContext * /*ctx*/) override { }
  virtual void exitMulExpr(LangParser::MulExprContext * /*ctx*/) override { }

  virtual void enterOrExpr(LangParser::OrExprContext * /*ctx*/) override { }
  virtual void exitOrExpr(LangParser::OrExprContext * /*ctx*/) override { }

  virtual void enterAssignExpr(LangParser::AssignExprContext * /*ctx*/) override { }
  virtual void exitAssignExpr(LangParser::AssignExprContext * /*ctx*/) override { }

  virtual void enterAndExpr(LangParser::AndExprContext * /*ctx*/) override { }
  virtual void exitAndExpr(LangParser::AndExprContext * /*ctx*/) override { }

  virtual void enterCompareExpr(LangParser::CompareExprContext * /*ctx*/) override { }
  virtual void exitCompareExpr(LangParser::CompareExprContext * /*ctx*/) override { }

  virtual void enterPrimary(LangParser::PrimaryContext * /*ctx*/) override { }
  virtual void exitPrimary(LangParser::PrimaryContext * /*ctx*/) override { }

  virtual void enterArgExprList(LangParser::ArgExprListContext * /*ctx*/) override { }
  virtual void exitArgExprList(LangParser::ArgExprListContext * /*ctx*/) override { }

  virtual void enterAtom(LangParser::AtomContext * /*ctx*/) override { }
  virtual void exitAtom(LangParser::AtomContext * /*ctx*/) override { }

  virtual void enterLiteral(LangParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(LangParser::LiteralContext * /*ctx*/) override { }

  virtual void enterIdentifier(LangParser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(LangParser::IdentifierContext * /*ctx*/) override { }

  virtual void enterBuiltinType(LangParser::BuiltinTypeContext * /*ctx*/) override { }
  virtual void exitBuiltinType(LangParser::BuiltinTypeContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

