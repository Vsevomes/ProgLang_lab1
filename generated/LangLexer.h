
// Generated from Lang.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  LangLexer : public antlr4::Lexer {
public:
  enum {
    FUNCTION = 1, END = 2, IF = 3, THEN = 4, ELSE = 5, WHILE = 6, WEND = 7, 
    DO = 8, LOOP = 9, BREAK = 10, DIM = 11, AS = 12, UNTIL = 13, TRUE = 14, 
    FALSE = 15, RETURN = 16, BOOL = 17, BUILTIN_BOOL = 18, BUILTIN_BYTE = 19, 
    BUILTIN_INT = 20, BUILTIN_UINT = 21, BUILTIN_LONG = 22, BUILTIN_ULONG = 23, 
    BUILTIN_CHAR = 24, BUILTIN_STRING = 25, HEX = 26, BITS = 27, DEC = 28, 
    STRING = 29, CHAR = 30, Identifier = 31, ASSIGN = 32, EQ = 33, NEQ = 34, 
    LT = 35, GT = 36, LE = 37, GE = 38, ADD = 39, SUB = 40, MUL = 41, DIV = 42, 
    MOD = 43, AND = 44, OR = 45, NOT = 46, LPAREN = 47, RPAREN = 48, LBRACK = 49, 
    RBRACK = 50, COMMA = 51, SEMI = 52, WS = 53, LINE_COMMENT = 54, BLOCK_COMMENT = 55
  };

  explicit LangLexer(antlr4::CharStream *input);

  ~LangLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

