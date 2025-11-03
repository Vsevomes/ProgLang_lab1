
// Generated from Lang.g4 by ANTLR 4.13.1


#include "LangListener.h"
#include "LangVisitor.h"

#include "LangParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct LangParserStaticData final {
  LangParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  LangParserStaticData(const LangParserStaticData&) = delete;
  LangParserStaticData(LangParserStaticData&&) = delete;
  LangParserStaticData& operator=(const LangParserStaticData&) = delete;
  LangParserStaticData& operator=(LangParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag langParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
LangParserStaticData *langParserStaticData = nullptr;

void langParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (langParserStaticData != nullptr) {
    return;
  }
#else
  assert(langParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<LangParserStaticData>(
    std::vector<std::string>{
      "source", "sourceItem", "funcDef", "funcSignature", "argList", "argDef", 
      "typeRef", "typeArgList", "statement", "identifierList", "expr", "primary", 
      "argExprList", "atom", "literal", "identifier", "builtinType"
    },
    std::vector<std::string>{
      "", "'function'", "'end'", "'if'", "'then'", "'else'", "'while'", 
      "'wend'", "'do'", "'loop'", "'break'", "'dim'", "'as'", "'until'", 
      "'true'", "'false'", "'return'", "", "'bool'", "'byte'", "'int'", 
      "'uint'", "'long'", "'ulong'", "'char'", "'string'", "", "", "", "", 
      "", "", "'='", "'=='", "", "'<'", "'>'", "'<='", "'>='", "'+'", "'-'", 
      "'*'", "'/'", "'%'", "'and'", "'or'", "'not'", "'('", "')'", "'['", 
      "']'", "','", "';'"
    },
    std::vector<std::string>{
      "", "FUNCTION", "END", "IF", "THEN", "ELSE", "WHILE", "WEND", "DO", 
      "LOOP", "BREAK", "DIM", "AS", "UNTIL", "TRUE", "FALSE", "RETURN", 
      "BOOL", "BUILTIN_BOOL", "BUILTIN_BYTE", "BUILTIN_INT", "BUILTIN_UINT", 
      "BUILTIN_LONG", "BUILTIN_ULONG", "BUILTIN_CHAR", "BUILTIN_STRING", 
      "HEX", "BITS", "DEC", "STRING", "CHAR", "Identifier", "ASSIGN", "EQ", 
      "NEQ", "LT", "GT", "LE", "GE", "ADD", "SUB", "MUL", "DIV", "MOD", 
      "AND", "OR", "NOT", "LPAREN", "RPAREN", "LBRACK", "RBRACK", "COMMA", 
      "SEMI", "WS", "LINE_COMMENT", "BLOCK_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,55,230,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,1,0,5,0,36,8,0,10,0,12,0,39,9,0,1,0,1,0,1,1,1,
  	1,1,2,1,2,1,2,5,2,48,8,2,10,2,12,2,51,9,2,1,2,1,2,1,2,1,3,1,3,1,3,3,3,
  	59,8,3,1,3,1,3,1,3,3,3,64,8,3,1,4,1,4,1,4,5,4,69,8,4,10,4,12,4,72,9,4,
  	1,5,1,5,1,5,3,5,77,8,5,1,6,1,6,1,6,3,6,82,8,6,1,6,1,6,1,6,3,6,87,8,6,
  	1,6,5,6,90,8,6,10,6,12,6,93,9,6,1,7,1,7,1,7,5,7,98,8,7,10,7,12,7,101,
  	9,7,1,8,1,8,1,8,1,8,1,8,3,8,108,8,8,1,8,1,8,1,8,1,8,5,8,114,8,8,10,8,
  	12,8,117,9,8,1,8,1,8,5,8,121,8,8,10,8,12,8,124,9,8,3,8,126,8,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,5,8,134,8,8,10,8,12,8,137,9,8,1,8,1,8,1,8,1,8,5,8,143,
  	8,8,10,8,12,8,146,9,8,1,8,1,8,1,8,1,8,1,8,3,8,153,8,8,1,8,1,8,1,8,3,8,
  	158,8,8,1,9,1,9,1,9,5,9,163,8,9,10,9,12,9,166,9,9,1,10,1,10,1,10,1,10,
  	3,10,172,8,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,
  	1,10,1,10,1,10,1,10,1,10,1,10,1,10,5,10,192,8,10,10,10,12,10,195,9,10,
  	1,11,1,11,1,11,3,11,200,8,11,1,11,5,11,203,8,11,10,11,12,11,206,9,11,
  	1,12,1,12,1,12,5,12,211,8,12,10,12,12,12,214,9,12,1,13,1,13,1,13,1,13,
  	1,13,1,13,3,13,222,8,13,1,14,1,14,1,15,1,15,1,16,1,16,1,16,0,2,12,20,
  	17,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,0,7,2,0,6,6,13,13,2,
  	0,40,40,46,46,1,0,33,38,1,0,39,40,1,0,41,43,2,0,17,17,26,30,1,0,18,25,
  	247,0,37,1,0,0,0,2,42,1,0,0,0,4,44,1,0,0,0,6,55,1,0,0,0,8,65,1,0,0,0,
  	10,73,1,0,0,0,12,81,1,0,0,0,14,94,1,0,0,0,16,157,1,0,0,0,18,159,1,0,0,
  	0,20,171,1,0,0,0,22,196,1,0,0,0,24,207,1,0,0,0,26,221,1,0,0,0,28,223,
  	1,0,0,0,30,225,1,0,0,0,32,227,1,0,0,0,34,36,3,2,1,0,35,34,1,0,0,0,36,
  	39,1,0,0,0,37,35,1,0,0,0,37,38,1,0,0,0,38,40,1,0,0,0,39,37,1,0,0,0,40,
  	41,5,0,0,1,41,1,1,0,0,0,42,43,3,4,2,0,43,3,1,0,0,0,44,45,5,1,0,0,45,49,
  	3,6,3,0,46,48,3,16,8,0,47,46,1,0,0,0,48,51,1,0,0,0,49,47,1,0,0,0,49,50,
  	1,0,0,0,50,52,1,0,0,0,51,49,1,0,0,0,52,53,5,2,0,0,53,54,5,1,0,0,54,5,
  	1,0,0,0,55,56,3,30,15,0,56,58,5,47,0,0,57,59,3,8,4,0,58,57,1,0,0,0,58,
  	59,1,0,0,0,59,60,1,0,0,0,60,63,5,48,0,0,61,62,5,12,0,0,62,64,3,12,6,0,
  	63,61,1,0,0,0,63,64,1,0,0,0,64,7,1,0,0,0,65,70,3,10,5,0,66,67,5,51,0,
  	0,67,69,3,10,5,0,68,66,1,0,0,0,69,72,1,0,0,0,70,68,1,0,0,0,70,71,1,0,
  	0,0,71,9,1,0,0,0,72,70,1,0,0,0,73,76,3,30,15,0,74,75,5,12,0,0,75,77,3,
  	12,6,0,76,74,1,0,0,0,76,77,1,0,0,0,77,11,1,0,0,0,78,79,6,6,-1,0,79,82,
  	3,32,16,0,80,82,3,30,15,0,81,78,1,0,0,0,81,80,1,0,0,0,82,91,1,0,0,0,83,
  	84,10,1,0,0,84,86,5,47,0,0,85,87,3,14,7,0,86,85,1,0,0,0,86,87,1,0,0,0,
  	87,88,1,0,0,0,88,90,5,48,0,0,89,83,1,0,0,0,90,93,1,0,0,0,91,89,1,0,0,
  	0,91,92,1,0,0,0,92,13,1,0,0,0,93,91,1,0,0,0,94,99,3,12,6,0,95,96,5,51,
  	0,0,96,98,3,12,6,0,97,95,1,0,0,0,98,101,1,0,0,0,99,97,1,0,0,0,99,100,
  	1,0,0,0,100,15,1,0,0,0,101,99,1,0,0,0,102,103,5,11,0,0,103,104,3,18,9,
  	0,104,105,5,12,0,0,105,107,3,12,6,0,106,108,5,52,0,0,107,106,1,0,0,0,
  	107,108,1,0,0,0,108,158,1,0,0,0,109,110,5,3,0,0,110,111,3,20,10,0,111,
  	115,5,4,0,0,112,114,3,16,8,0,113,112,1,0,0,0,114,117,1,0,0,0,115,113,
  	1,0,0,0,115,116,1,0,0,0,116,125,1,0,0,0,117,115,1,0,0,0,118,122,5,5,0,
  	0,119,121,3,16,8,0,120,119,1,0,0,0,121,124,1,0,0,0,122,120,1,0,0,0,122,
  	123,1,0,0,0,123,126,1,0,0,0,124,122,1,0,0,0,125,118,1,0,0,0,125,126,1,
  	0,0,0,126,127,1,0,0,0,127,128,5,2,0,0,128,129,5,3,0,0,129,158,1,0,0,0,
  	130,131,5,6,0,0,131,135,3,20,10,0,132,134,3,16,8,0,133,132,1,0,0,0,134,
  	137,1,0,0,0,135,133,1,0,0,0,135,136,1,0,0,0,136,138,1,0,0,0,137,135,1,
  	0,0,0,138,139,5,7,0,0,139,158,1,0,0,0,140,144,5,8,0,0,141,143,3,16,8,
  	0,142,141,1,0,0,0,143,146,1,0,0,0,144,142,1,0,0,0,144,145,1,0,0,0,145,
  	147,1,0,0,0,146,144,1,0,0,0,147,148,5,9,0,0,148,149,7,0,0,0,149,158,3,
  	20,10,0,150,152,5,10,0,0,151,153,5,52,0,0,152,151,1,0,0,0,152,153,1,0,
  	0,0,153,158,1,0,0,0,154,155,3,20,10,0,155,156,5,52,0,0,156,158,1,0,0,
  	0,157,102,1,0,0,0,157,109,1,0,0,0,157,130,1,0,0,0,157,140,1,0,0,0,157,
  	150,1,0,0,0,157,154,1,0,0,0,158,17,1,0,0,0,159,164,3,30,15,0,160,161,
  	5,51,0,0,161,163,3,30,15,0,162,160,1,0,0,0,163,166,1,0,0,0,164,162,1,
  	0,0,0,164,165,1,0,0,0,165,19,1,0,0,0,166,164,1,0,0,0,167,168,6,10,-1,
  	0,168,169,7,1,0,0,169,172,3,20,10,2,170,172,3,22,11,0,171,167,1,0,0,0,
  	171,170,1,0,0,0,172,193,1,0,0,0,173,174,10,8,0,0,174,175,5,45,0,0,175,
  	192,3,20,10,9,176,177,10,7,0,0,177,178,5,44,0,0,178,192,3,20,10,8,179,
  	180,10,6,0,0,180,181,7,2,0,0,181,192,3,20,10,7,182,183,10,5,0,0,183,184,
  	7,3,0,0,184,192,3,20,10,6,185,186,10,4,0,0,186,187,7,4,0,0,187,192,3,
  	20,10,5,188,189,10,3,0,0,189,190,5,32,0,0,190,192,3,20,10,4,191,173,1,
  	0,0,0,191,176,1,0,0,0,191,179,1,0,0,0,191,182,1,0,0,0,191,185,1,0,0,0,
  	191,188,1,0,0,0,192,195,1,0,0,0,193,191,1,0,0,0,193,194,1,0,0,0,194,21,
  	1,0,0,0,195,193,1,0,0,0,196,204,3,26,13,0,197,199,5,47,0,0,198,200,3,
  	24,12,0,199,198,1,0,0,0,199,200,1,0,0,0,200,201,1,0,0,0,201,203,5,48,
  	0,0,202,197,1,0,0,0,203,206,1,0,0,0,204,202,1,0,0,0,204,205,1,0,0,0,205,
  	23,1,0,0,0,206,204,1,0,0,0,207,212,3,20,10,0,208,209,5,51,0,0,209,211,
  	3,20,10,0,210,208,1,0,0,0,211,214,1,0,0,0,212,210,1,0,0,0,212,213,1,0,
  	0,0,213,25,1,0,0,0,214,212,1,0,0,0,215,216,5,47,0,0,216,217,3,20,10,0,
  	217,218,5,48,0,0,218,222,1,0,0,0,219,222,3,30,15,0,220,222,3,28,14,0,
  	221,215,1,0,0,0,221,219,1,0,0,0,221,220,1,0,0,0,222,27,1,0,0,0,223,224,
  	7,5,0,0,224,29,1,0,0,0,225,226,5,31,0,0,226,31,1,0,0,0,227,228,7,6,0,
  	0,228,33,1,0,0,0,26,37,49,58,63,70,76,81,86,91,99,107,115,122,125,135,
  	144,152,157,164,171,191,193,199,204,212,221
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  langParserStaticData = staticData.release();
}

}

LangParser::LangParser(TokenStream *input) : LangParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

LangParser::LangParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  LangParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *langParserStaticData->atn, langParserStaticData->decisionToDFA, langParserStaticData->sharedContextCache, options);
}

LangParser::~LangParser() {
  delete _interpreter;
}

const atn::ATN& LangParser::getATN() const {
  return *langParserStaticData->atn;
}

std::string LangParser::getGrammarFileName() const {
  return "Lang.g4";
}

const std::vector<std::string>& LangParser::getRuleNames() const {
  return langParserStaticData->ruleNames;
}

const dfa::Vocabulary& LangParser::getVocabulary() const {
  return langParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView LangParser::getSerializedATN() const {
  return langParserStaticData->serializedATN;
}


//----------------- SourceContext ------------------------------------------------------------------

LangParser::SourceContext::SourceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LangParser::SourceContext::EOF() {
  return getToken(LangParser::EOF, 0);
}

std::vector<LangParser::SourceItemContext *> LangParser::SourceContext::sourceItem() {
  return getRuleContexts<LangParser::SourceItemContext>();
}

LangParser::SourceItemContext* LangParser::SourceContext::sourceItem(size_t i) {
  return getRuleContext<LangParser::SourceItemContext>(i);
}


size_t LangParser::SourceContext::getRuleIndex() const {
  return LangParser::RuleSource;
}

void LangParser::SourceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSource(this);
}

void LangParser::SourceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSource(this);
}


std::any LangParser::SourceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitSource(this);
  else
    return visitor->visitChildren(this);
}

LangParser::SourceContext* LangParser::source() {
  SourceContext *_localctx = _tracker.createInstance<SourceContext>(_ctx, getState());
  enterRule(_localctx, 0, LangParser::RuleSource);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(37);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LangParser::FUNCTION) {
      setState(34);
      sourceItem();
      setState(39);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(40);
    match(LangParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SourceItemContext ------------------------------------------------------------------

LangParser::SourceItemContext::SourceItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LangParser::FuncDefContext* LangParser::SourceItemContext::funcDef() {
  return getRuleContext<LangParser::FuncDefContext>(0);
}


size_t LangParser::SourceItemContext::getRuleIndex() const {
  return LangParser::RuleSourceItem;
}

void LangParser::SourceItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSourceItem(this);
}

void LangParser::SourceItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSourceItem(this);
}


std::any LangParser::SourceItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitSourceItem(this);
  else
    return visitor->visitChildren(this);
}

LangParser::SourceItemContext* LangParser::sourceItem() {
  SourceItemContext *_localctx = _tracker.createInstance<SourceItemContext>(_ctx, getState());
  enterRule(_localctx, 2, LangParser::RuleSourceItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(42);
    funcDef();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

LangParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> LangParser::FuncDefContext::FUNCTION() {
  return getTokens(LangParser::FUNCTION);
}

tree::TerminalNode* LangParser::FuncDefContext::FUNCTION(size_t i) {
  return getToken(LangParser::FUNCTION, i);
}

LangParser::FuncSignatureContext* LangParser::FuncDefContext::funcSignature() {
  return getRuleContext<LangParser::FuncSignatureContext>(0);
}

tree::TerminalNode* LangParser::FuncDefContext::END() {
  return getToken(LangParser::END, 0);
}

std::vector<LangParser::StatementContext *> LangParser::FuncDefContext::statement() {
  return getRuleContexts<LangParser::StatementContext>();
}

LangParser::StatementContext* LangParser::FuncDefContext::statement(size_t i) {
  return getRuleContext<LangParser::StatementContext>(i);
}


size_t LangParser::FuncDefContext::getRuleIndex() const {
  return LangParser::RuleFuncDef;
}

void LangParser::FuncDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncDef(this);
}

void LangParser::FuncDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncDef(this);
}


std::any LangParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

LangParser::FuncDefContext* LangParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 4, LangParser::RuleFuncDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(44);
    match(LangParser::FUNCTION);
    setState(45);
    funcSignature();
    setState(49);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 212209972153672) != 0)) {
      setState(46);
      statement();
      setState(51);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(52);
    match(LangParser::END);
    setState(53);
    match(LangParser::FUNCTION);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncSignatureContext ------------------------------------------------------------------

LangParser::FuncSignatureContext::FuncSignatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LangParser::IdentifierContext* LangParser::FuncSignatureContext::identifier() {
  return getRuleContext<LangParser::IdentifierContext>(0);
}

tree::TerminalNode* LangParser::FuncSignatureContext::LPAREN() {
  return getToken(LangParser::LPAREN, 0);
}

tree::TerminalNode* LangParser::FuncSignatureContext::RPAREN() {
  return getToken(LangParser::RPAREN, 0);
}

LangParser::ArgListContext* LangParser::FuncSignatureContext::argList() {
  return getRuleContext<LangParser::ArgListContext>(0);
}

tree::TerminalNode* LangParser::FuncSignatureContext::AS() {
  return getToken(LangParser::AS, 0);
}

LangParser::TypeRefContext* LangParser::FuncSignatureContext::typeRef() {
  return getRuleContext<LangParser::TypeRefContext>(0);
}


size_t LangParser::FuncSignatureContext::getRuleIndex() const {
  return LangParser::RuleFuncSignature;
}

void LangParser::FuncSignatureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncSignature(this);
}

void LangParser::FuncSignatureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncSignature(this);
}


std::any LangParser::FuncSignatureContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitFuncSignature(this);
  else
    return visitor->visitChildren(this);
}

LangParser::FuncSignatureContext* LangParser::funcSignature() {
  FuncSignatureContext *_localctx = _tracker.createInstance<FuncSignatureContext>(_ctx, getState());
  enterRule(_localctx, 6, LangParser::RuleFuncSignature);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(55);
    identifier();
    setState(56);
    match(LangParser::LPAREN);
    setState(58);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LangParser::Identifier) {
      setState(57);
      argList();
    }
    setState(60);
    match(LangParser::RPAREN);
    setState(63);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LangParser::AS) {
      setState(61);
      match(LangParser::AS);
      setState(62);
      typeRef(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgListContext ------------------------------------------------------------------

LangParser::ArgListContext::ArgListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LangParser::ArgDefContext *> LangParser::ArgListContext::argDef() {
  return getRuleContexts<LangParser::ArgDefContext>();
}

LangParser::ArgDefContext* LangParser::ArgListContext::argDef(size_t i) {
  return getRuleContext<LangParser::ArgDefContext>(i);
}

std::vector<tree::TerminalNode *> LangParser::ArgListContext::COMMA() {
  return getTokens(LangParser::COMMA);
}

tree::TerminalNode* LangParser::ArgListContext::COMMA(size_t i) {
  return getToken(LangParser::COMMA, i);
}


size_t LangParser::ArgListContext::getRuleIndex() const {
  return LangParser::RuleArgList;
}

void LangParser::ArgListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgList(this);
}

void LangParser::ArgListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgList(this);
}


std::any LangParser::ArgListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitArgList(this);
  else
    return visitor->visitChildren(this);
}

LangParser::ArgListContext* LangParser::argList() {
  ArgListContext *_localctx = _tracker.createInstance<ArgListContext>(_ctx, getState());
  enterRule(_localctx, 8, LangParser::RuleArgList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65);
    argDef();
    setState(70);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LangParser::COMMA) {
      setState(66);
      match(LangParser::COMMA);
      setState(67);
      argDef();
      setState(72);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgDefContext ------------------------------------------------------------------

LangParser::ArgDefContext::ArgDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LangParser::IdentifierContext* LangParser::ArgDefContext::identifier() {
  return getRuleContext<LangParser::IdentifierContext>(0);
}

tree::TerminalNode* LangParser::ArgDefContext::AS() {
  return getToken(LangParser::AS, 0);
}

LangParser::TypeRefContext* LangParser::ArgDefContext::typeRef() {
  return getRuleContext<LangParser::TypeRefContext>(0);
}


size_t LangParser::ArgDefContext::getRuleIndex() const {
  return LangParser::RuleArgDef;
}

void LangParser::ArgDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgDef(this);
}

void LangParser::ArgDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgDef(this);
}


std::any LangParser::ArgDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitArgDef(this);
  else
    return visitor->visitChildren(this);
}

LangParser::ArgDefContext* LangParser::argDef() {
  ArgDefContext *_localctx = _tracker.createInstance<ArgDefContext>(_ctx, getState());
  enterRule(_localctx, 10, LangParser::RuleArgDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(73);
    identifier();
    setState(76);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LangParser::AS) {
      setState(74);
      match(LangParser::AS);
      setState(75);
      typeRef(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeRefContext ------------------------------------------------------------------

LangParser::TypeRefContext::TypeRefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t LangParser::TypeRefContext::getRuleIndex() const {
  return LangParser::RuleTypeRef;
}

void LangParser::TypeRefContext::copyFrom(TypeRefContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CustomTypeRefContext ------------------------------------------------------------------

LangParser::IdentifierContext* LangParser::CustomTypeRefContext::identifier() {
  return getRuleContext<LangParser::IdentifierContext>(0);
}

LangParser::CustomTypeRefContext::CustomTypeRefContext(TypeRefContext *ctx) { copyFrom(ctx); }

void LangParser::CustomTypeRefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCustomTypeRef(this);
}
void LangParser::CustomTypeRefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCustomTypeRef(this);
}

std::any LangParser::CustomTypeRefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitCustomTypeRef(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayTypeRefContext ------------------------------------------------------------------

LangParser::TypeRefContext* LangParser::ArrayTypeRefContext::typeRef() {
  return getRuleContext<LangParser::TypeRefContext>(0);
}

tree::TerminalNode* LangParser::ArrayTypeRefContext::LPAREN() {
  return getToken(LangParser::LPAREN, 0);
}

tree::TerminalNode* LangParser::ArrayTypeRefContext::RPAREN() {
  return getToken(LangParser::RPAREN, 0);
}

LangParser::TypeArgListContext* LangParser::ArrayTypeRefContext::typeArgList() {
  return getRuleContext<LangParser::TypeArgListContext>(0);
}

LangParser::ArrayTypeRefContext::ArrayTypeRefContext(TypeRefContext *ctx) { copyFrom(ctx); }

void LangParser::ArrayTypeRefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayTypeRef(this);
}
void LangParser::ArrayTypeRefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayTypeRef(this);
}

std::any LangParser::ArrayTypeRefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitArrayTypeRef(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BuiltinTypeRefContext ------------------------------------------------------------------

LangParser::BuiltinTypeContext* LangParser::BuiltinTypeRefContext::builtinType() {
  return getRuleContext<LangParser::BuiltinTypeContext>(0);
}

LangParser::BuiltinTypeRefContext::BuiltinTypeRefContext(TypeRefContext *ctx) { copyFrom(ctx); }

void LangParser::BuiltinTypeRefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBuiltinTypeRef(this);
}
void LangParser::BuiltinTypeRefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBuiltinTypeRef(this);
}

std::any LangParser::BuiltinTypeRefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitBuiltinTypeRef(this);
  else
    return visitor->visitChildren(this);
}

LangParser::TypeRefContext* LangParser::typeRef() {
   return typeRef(0);
}

LangParser::TypeRefContext* LangParser::typeRef(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  LangParser::TypeRefContext *_localctx = _tracker.createInstance<TypeRefContext>(_ctx, parentState);
  LangParser::TypeRefContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 12;
  enterRecursionRule(_localctx, 12, LangParser::RuleTypeRef, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(81);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LangParser::BUILTIN_BOOL:
      case LangParser::BUILTIN_BYTE:
      case LangParser::BUILTIN_INT:
      case LangParser::BUILTIN_UINT:
      case LangParser::BUILTIN_LONG:
      case LangParser::BUILTIN_ULONG:
      case LangParser::BUILTIN_CHAR:
      case LangParser::BUILTIN_STRING: {
        _localctx = _tracker.createInstance<BuiltinTypeRefContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(79);
        builtinType();
        break;
      }

      case LangParser::Identifier: {
        _localctx = _tracker.createInstance<CustomTypeRefContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(80);
        identifier();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(91);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<ArrayTypeRefContext>(_tracker.createInstance<TypeRefContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleTypeRef);
        setState(83);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(84);
        match(LangParser::LPAREN);
        setState(86);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 2214330368) != 0)) {
          setState(85);
          typeArgList();
        }
        setState(88);
        match(LangParser::RPAREN); 
      }
      setState(93);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- TypeArgListContext ------------------------------------------------------------------

LangParser::TypeArgListContext::TypeArgListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LangParser::TypeRefContext *> LangParser::TypeArgListContext::typeRef() {
  return getRuleContexts<LangParser::TypeRefContext>();
}

LangParser::TypeRefContext* LangParser::TypeArgListContext::typeRef(size_t i) {
  return getRuleContext<LangParser::TypeRefContext>(i);
}

std::vector<tree::TerminalNode *> LangParser::TypeArgListContext::COMMA() {
  return getTokens(LangParser::COMMA);
}

tree::TerminalNode* LangParser::TypeArgListContext::COMMA(size_t i) {
  return getToken(LangParser::COMMA, i);
}


size_t LangParser::TypeArgListContext::getRuleIndex() const {
  return LangParser::RuleTypeArgList;
}

void LangParser::TypeArgListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeArgList(this);
}

void LangParser::TypeArgListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeArgList(this);
}


std::any LangParser::TypeArgListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitTypeArgList(this);
  else
    return visitor->visitChildren(this);
}

LangParser::TypeArgListContext* LangParser::typeArgList() {
  TypeArgListContext *_localctx = _tracker.createInstance<TypeArgListContext>(_ctx, getState());
  enterRule(_localctx, 14, LangParser::RuleTypeArgList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(94);
    typeRef(0);
    setState(99);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LangParser::COMMA) {
      setState(95);
      match(LangParser::COMMA);
      setState(96);
      typeRef(0);
      setState(101);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

LangParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t LangParser::StatementContext::getRuleIndex() const {
  return LangParser::RuleStatement;
}

void LangParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DoLoopStmtContext ------------------------------------------------------------------

tree::TerminalNode* LangParser::DoLoopStmtContext::DO() {
  return getToken(LangParser::DO, 0);
}

tree::TerminalNode* LangParser::DoLoopStmtContext::LOOP() {
  return getToken(LangParser::LOOP, 0);
}

LangParser::ExprContext* LangParser::DoLoopStmtContext::expr() {
  return getRuleContext<LangParser::ExprContext>(0);
}

tree::TerminalNode* LangParser::DoLoopStmtContext::WHILE() {
  return getToken(LangParser::WHILE, 0);
}

tree::TerminalNode* LangParser::DoLoopStmtContext::UNTIL() {
  return getToken(LangParser::UNTIL, 0);
}

std::vector<LangParser::StatementContext *> LangParser::DoLoopStmtContext::statement() {
  return getRuleContexts<LangParser::StatementContext>();
}

LangParser::StatementContext* LangParser::DoLoopStmtContext::statement(size_t i) {
  return getRuleContext<LangParser::StatementContext>(i);
}

LangParser::DoLoopStmtContext::DoLoopStmtContext(StatementContext *ctx) { copyFrom(ctx); }

void LangParser::DoLoopStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDoLoopStmt(this);
}
void LangParser::DoLoopStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDoLoopStmt(this);
}

std::any LangParser::DoLoopStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitDoLoopStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprStmtContext ------------------------------------------------------------------

LangParser::ExprContext* LangParser::ExprStmtContext::expr() {
  return getRuleContext<LangParser::ExprContext>(0);
}

tree::TerminalNode* LangParser::ExprStmtContext::SEMI() {
  return getToken(LangParser::SEMI, 0);
}

LangParser::ExprStmtContext::ExprStmtContext(StatementContext *ctx) { copyFrom(ctx); }

void LangParser::ExprStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprStmt(this);
}
void LangParser::ExprStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprStmt(this);
}

std::any LangParser::ExprStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitExprStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileStmtContext ------------------------------------------------------------------

tree::TerminalNode* LangParser::WhileStmtContext::WHILE() {
  return getToken(LangParser::WHILE, 0);
}

LangParser::ExprContext* LangParser::WhileStmtContext::expr() {
  return getRuleContext<LangParser::ExprContext>(0);
}

tree::TerminalNode* LangParser::WhileStmtContext::WEND() {
  return getToken(LangParser::WEND, 0);
}

std::vector<LangParser::StatementContext *> LangParser::WhileStmtContext::statement() {
  return getRuleContexts<LangParser::StatementContext>();
}

LangParser::StatementContext* LangParser::WhileStmtContext::statement(size_t i) {
  return getRuleContext<LangParser::StatementContext>(i);
}

LangParser::WhileStmtContext::WhileStmtContext(StatementContext *ctx) { copyFrom(ctx); }

void LangParser::WhileStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhileStmt(this);
}
void LangParser::WhileStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhileStmt(this);
}

std::any LangParser::WhileStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitWhileStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfStmtContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> LangParser::IfStmtContext::IF() {
  return getTokens(LangParser::IF);
}

tree::TerminalNode* LangParser::IfStmtContext::IF(size_t i) {
  return getToken(LangParser::IF, i);
}

LangParser::ExprContext* LangParser::IfStmtContext::expr() {
  return getRuleContext<LangParser::ExprContext>(0);
}

tree::TerminalNode* LangParser::IfStmtContext::THEN() {
  return getToken(LangParser::THEN, 0);
}

tree::TerminalNode* LangParser::IfStmtContext::END() {
  return getToken(LangParser::END, 0);
}

std::vector<LangParser::StatementContext *> LangParser::IfStmtContext::statement() {
  return getRuleContexts<LangParser::StatementContext>();
}

LangParser::StatementContext* LangParser::IfStmtContext::statement(size_t i) {
  return getRuleContext<LangParser::StatementContext>(i);
}

tree::TerminalNode* LangParser::IfStmtContext::ELSE() {
  return getToken(LangParser::ELSE, 0);
}

LangParser::IfStmtContext::IfStmtContext(StatementContext *ctx) { copyFrom(ctx); }

void LangParser::IfStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStmt(this);
}
void LangParser::IfStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStmt(this);
}

std::any LangParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakStmtContext ------------------------------------------------------------------

tree::TerminalNode* LangParser::BreakStmtContext::BREAK() {
  return getToken(LangParser::BREAK, 0);
}

tree::TerminalNode* LangParser::BreakStmtContext::SEMI() {
  return getToken(LangParser::SEMI, 0);
}

LangParser::BreakStmtContext::BreakStmtContext(StatementContext *ctx) { copyFrom(ctx); }

void LangParser::BreakStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakStmt(this);
}
void LangParser::BreakStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakStmt(this);
}

std::any LangParser::BreakStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitBreakStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarDeclContext ------------------------------------------------------------------

tree::TerminalNode* LangParser::VarDeclContext::DIM() {
  return getToken(LangParser::DIM, 0);
}

LangParser::IdentifierListContext* LangParser::VarDeclContext::identifierList() {
  return getRuleContext<LangParser::IdentifierListContext>(0);
}

tree::TerminalNode* LangParser::VarDeclContext::AS() {
  return getToken(LangParser::AS, 0);
}

LangParser::TypeRefContext* LangParser::VarDeclContext::typeRef() {
  return getRuleContext<LangParser::TypeRefContext>(0);
}

tree::TerminalNode* LangParser::VarDeclContext::SEMI() {
  return getToken(LangParser::SEMI, 0);
}

LangParser::VarDeclContext::VarDeclContext(StatementContext *ctx) { copyFrom(ctx); }

void LangParser::VarDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDecl(this);
}
void LangParser::VarDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDecl(this);
}

std::any LangParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}
LangParser::StatementContext* LangParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 16, LangParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(157);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LangParser::DIM: {
        _localctx = _tracker.createInstance<LangParser::VarDeclContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(102);
        match(LangParser::DIM);
        setState(103);
        identifierList();
        setState(104);
        match(LangParser::AS);
        setState(105);
        typeRef(0);
        setState(107);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == LangParser::SEMI) {
          setState(106);
          match(LangParser::SEMI);
        }
        break;
      }

      case LangParser::IF: {
        _localctx = _tracker.createInstance<LangParser::IfStmtContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(109);
        match(LangParser::IF);
        setState(110);
        expr(0);
        setState(111);
        match(LangParser::THEN);
        setState(115);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 212209972153672) != 0)) {
          setState(112);
          statement();
          setState(117);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(125);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == LangParser::ELSE) {
          setState(118);
          match(LangParser::ELSE);
          setState(122);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 212209972153672) != 0)) {
            setState(119);
            statement();
            setState(124);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(127);
        match(LangParser::END);
        setState(128);
        match(LangParser::IF);
        break;
      }

      case LangParser::WHILE: {
        _localctx = _tracker.createInstance<LangParser::WhileStmtContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(130);
        match(LangParser::WHILE);
        setState(131);
        expr(0);
        setState(135);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 212209972153672) != 0)) {
          setState(132);
          statement();
          setState(137);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(138);
        match(LangParser::WEND);
        break;
      }

      case LangParser::DO: {
        _localctx = _tracker.createInstance<LangParser::DoLoopStmtContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(140);
        match(LangParser::DO);
        setState(144);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 212209972153672) != 0)) {
          setState(141);
          statement();
          setState(146);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(147);
        match(LangParser::LOOP);
        setState(148);
        _la = _input->LA(1);
        if (!(_la == LangParser::WHILE

        || _la == LangParser::UNTIL)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(149);
        expr(0);
        break;
      }

      case LangParser::BREAK: {
        _localctx = _tracker.createInstance<LangParser::BreakStmtContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(150);
        match(LangParser::BREAK);
        setState(152);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == LangParser::SEMI) {
          setState(151);
          match(LangParser::SEMI);
        }
        break;
      }

      case LangParser::BOOL:
      case LangParser::HEX:
      case LangParser::BITS:
      case LangParser::DEC:
      case LangParser::STRING:
      case LangParser::CHAR:
      case LangParser::Identifier:
      case LangParser::SUB:
      case LangParser::NOT:
      case LangParser::LPAREN: {
        _localctx = _tracker.createInstance<LangParser::ExprStmtContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(154);
        expr(0);
        setState(155);
        match(LangParser::SEMI);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierListContext ------------------------------------------------------------------

LangParser::IdentifierListContext::IdentifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LangParser::IdentifierContext *> LangParser::IdentifierListContext::identifier() {
  return getRuleContexts<LangParser::IdentifierContext>();
}

LangParser::IdentifierContext* LangParser::IdentifierListContext::identifier(size_t i) {
  return getRuleContext<LangParser::IdentifierContext>(i);
}

std::vector<tree::TerminalNode *> LangParser::IdentifierListContext::COMMA() {
  return getTokens(LangParser::COMMA);
}

tree::TerminalNode* LangParser::IdentifierListContext::COMMA(size_t i) {
  return getToken(LangParser::COMMA, i);
}


size_t LangParser::IdentifierListContext::getRuleIndex() const {
  return LangParser::RuleIdentifierList;
}

void LangParser::IdentifierListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifierList(this);
}

void LangParser::IdentifierListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifierList(this);
}


std::any LangParser::IdentifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitIdentifierList(this);
  else
    return visitor->visitChildren(this);
}

LangParser::IdentifierListContext* LangParser::identifierList() {
  IdentifierListContext *_localctx = _tracker.createInstance<IdentifierListContext>(_ctx, getState());
  enterRule(_localctx, 18, LangParser::RuleIdentifierList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(159);
    identifier();
    setState(164);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LangParser::COMMA) {
      setState(160);
      match(LangParser::COMMA);
      setState(161);
      identifier();
      setState(166);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

LangParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t LangParser::ExprContext::getRuleIndex() const {
  return LangParser::RuleExpr;
}

void LangParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UnaryExprContext ------------------------------------------------------------------

LangParser::ExprContext* LangParser::UnaryExprContext::expr() {
  return getRuleContext<LangParser::ExprContext>(0);
}

tree::TerminalNode* LangParser::UnaryExprContext::NOT() {
  return getToken(LangParser::NOT, 0);
}

tree::TerminalNode* LangParser::UnaryExprContext::SUB() {
  return getToken(LangParser::SUB, 0);
}

LangParser::UnaryExprContext::UnaryExprContext(ExprContext *ctx) { copyFrom(ctx); }

void LangParser::UnaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpr(this);
}
void LangParser::UnaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpr(this);
}

std::any LangParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrimaryExprContext ------------------------------------------------------------------

LangParser::PrimaryContext* LangParser::PrimaryExprContext::primary() {
  return getRuleContext<LangParser::PrimaryContext>(0);
}

LangParser::PrimaryExprContext::PrimaryExprContext(ExprContext *ctx) { copyFrom(ctx); }

void LangParser::PrimaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpr(this);
}
void LangParser::PrimaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpr(this);
}

std::any LangParser::PrimaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddExprContext ------------------------------------------------------------------

std::vector<LangParser::ExprContext *> LangParser::AddExprContext::expr() {
  return getRuleContexts<LangParser::ExprContext>();
}

LangParser::ExprContext* LangParser::AddExprContext::expr(size_t i) {
  return getRuleContext<LangParser::ExprContext>(i);
}

tree::TerminalNode* LangParser::AddExprContext::ADD() {
  return getToken(LangParser::ADD, 0);
}

tree::TerminalNode* LangParser::AddExprContext::SUB() {
  return getToken(LangParser::SUB, 0);
}

LangParser::AddExprContext::AddExprContext(ExprContext *ctx) { copyFrom(ctx); }

void LangParser::AddExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddExpr(this);
}
void LangParser::AddExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddExpr(this);
}

std::any LangParser::AddExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitAddExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulExprContext ------------------------------------------------------------------

std::vector<LangParser::ExprContext *> LangParser::MulExprContext::expr() {
  return getRuleContexts<LangParser::ExprContext>();
}

LangParser::ExprContext* LangParser::MulExprContext::expr(size_t i) {
  return getRuleContext<LangParser::ExprContext>(i);
}

tree::TerminalNode* LangParser::MulExprContext::MUL() {
  return getToken(LangParser::MUL, 0);
}

tree::TerminalNode* LangParser::MulExprContext::DIV() {
  return getToken(LangParser::DIV, 0);
}

tree::TerminalNode* LangParser::MulExprContext::MOD() {
  return getToken(LangParser::MOD, 0);
}

LangParser::MulExprContext::MulExprContext(ExprContext *ctx) { copyFrom(ctx); }

void LangParser::MulExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMulExpr(this);
}
void LangParser::MulExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMulExpr(this);
}

std::any LangParser::MulExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitMulExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OrExprContext ------------------------------------------------------------------

std::vector<LangParser::ExprContext *> LangParser::OrExprContext::expr() {
  return getRuleContexts<LangParser::ExprContext>();
}

LangParser::ExprContext* LangParser::OrExprContext::expr(size_t i) {
  return getRuleContext<LangParser::ExprContext>(i);
}

tree::TerminalNode* LangParser::OrExprContext::OR() {
  return getToken(LangParser::OR, 0);
}

LangParser::OrExprContext::OrExprContext(ExprContext *ctx) { copyFrom(ctx); }

void LangParser::OrExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOrExpr(this);
}
void LangParser::OrExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOrExpr(this);
}

std::any LangParser::OrExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitOrExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignExprContext ------------------------------------------------------------------

std::vector<LangParser::ExprContext *> LangParser::AssignExprContext::expr() {
  return getRuleContexts<LangParser::ExprContext>();
}

LangParser::ExprContext* LangParser::AssignExprContext::expr(size_t i) {
  return getRuleContext<LangParser::ExprContext>(i);
}

tree::TerminalNode* LangParser::AssignExprContext::ASSIGN() {
  return getToken(LangParser::ASSIGN, 0);
}

LangParser::AssignExprContext::AssignExprContext(ExprContext *ctx) { copyFrom(ctx); }

void LangParser::AssignExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignExpr(this);
}
void LangParser::AssignExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignExpr(this);
}

std::any LangParser::AssignExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitAssignExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AndExprContext ------------------------------------------------------------------

std::vector<LangParser::ExprContext *> LangParser::AndExprContext::expr() {
  return getRuleContexts<LangParser::ExprContext>();
}

LangParser::ExprContext* LangParser::AndExprContext::expr(size_t i) {
  return getRuleContext<LangParser::ExprContext>(i);
}

tree::TerminalNode* LangParser::AndExprContext::AND() {
  return getToken(LangParser::AND, 0);
}

LangParser::AndExprContext::AndExprContext(ExprContext *ctx) { copyFrom(ctx); }

void LangParser::AndExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAndExpr(this);
}
void LangParser::AndExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAndExpr(this);
}

std::any LangParser::AndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitAndExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CompareExprContext ------------------------------------------------------------------

std::vector<LangParser::ExprContext *> LangParser::CompareExprContext::expr() {
  return getRuleContexts<LangParser::ExprContext>();
}

LangParser::ExprContext* LangParser::CompareExprContext::expr(size_t i) {
  return getRuleContext<LangParser::ExprContext>(i);
}

tree::TerminalNode* LangParser::CompareExprContext::EQ() {
  return getToken(LangParser::EQ, 0);
}

tree::TerminalNode* LangParser::CompareExprContext::NEQ() {
  return getToken(LangParser::NEQ, 0);
}

tree::TerminalNode* LangParser::CompareExprContext::LT() {
  return getToken(LangParser::LT, 0);
}

tree::TerminalNode* LangParser::CompareExprContext::GT() {
  return getToken(LangParser::GT, 0);
}

tree::TerminalNode* LangParser::CompareExprContext::LE() {
  return getToken(LangParser::LE, 0);
}

tree::TerminalNode* LangParser::CompareExprContext::GE() {
  return getToken(LangParser::GE, 0);
}

LangParser::CompareExprContext::CompareExprContext(ExprContext *ctx) { copyFrom(ctx); }

void LangParser::CompareExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompareExpr(this);
}
void LangParser::CompareExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompareExpr(this);
}

std::any LangParser::CompareExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitCompareExpr(this);
  else
    return visitor->visitChildren(this);
}

LangParser::ExprContext* LangParser::expr() {
   return expr(0);
}

LangParser::ExprContext* LangParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  LangParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  LangParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 20;
  enterRecursionRule(_localctx, 20, LangParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(171);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LangParser::SUB:
      case LangParser::NOT: {
        _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(168);
        _la = _input->LA(1);
        if (!(_la == LangParser::SUB

        || _la == LangParser::NOT)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(169);
        expr(2);
        break;
      }

      case LangParser::BOOL:
      case LangParser::HEX:
      case LangParser::BITS:
      case LangParser::DEC:
      case LangParser::STRING:
      case LangParser::CHAR:
      case LangParser::Identifier:
      case LangParser::LPAREN: {
        _localctx = _tracker.createInstance<PrimaryExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(170);
        primary();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(193);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(191);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<OrExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(173);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(174);
          match(LangParser::OR);
          setState(175);
          expr(9);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AndExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(176);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(177);
          match(LangParser::AND);
          setState(178);
          expr(8);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<CompareExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(179);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(180);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 541165879296) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(181);
          expr(7);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<AddExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(182);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(183);
          _la = _input->LA(1);
          if (!(_la == LangParser::ADD

          || _la == LangParser::SUB)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(184);
          expr(6);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<MulExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(185);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(186);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 15393162788864) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(187);
          expr(5);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<AssignExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(188);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(189);
          match(LangParser::ASSIGN);
          setState(190);
          expr(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(195);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PrimaryContext ------------------------------------------------------------------

LangParser::PrimaryContext::PrimaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LangParser::AtomContext* LangParser::PrimaryContext::atom() {
  return getRuleContext<LangParser::AtomContext>(0);
}

std::vector<tree::TerminalNode *> LangParser::PrimaryContext::LPAREN() {
  return getTokens(LangParser::LPAREN);
}

tree::TerminalNode* LangParser::PrimaryContext::LPAREN(size_t i) {
  return getToken(LangParser::LPAREN, i);
}

std::vector<tree::TerminalNode *> LangParser::PrimaryContext::RPAREN() {
  return getTokens(LangParser::RPAREN);
}

tree::TerminalNode* LangParser::PrimaryContext::RPAREN(size_t i) {
  return getToken(LangParser::RPAREN, i);
}

std::vector<LangParser::ArgExprListContext *> LangParser::PrimaryContext::argExprList() {
  return getRuleContexts<LangParser::ArgExprListContext>();
}

LangParser::ArgExprListContext* LangParser::PrimaryContext::argExprList(size_t i) {
  return getRuleContext<LangParser::ArgExprListContext>(i);
}


size_t LangParser::PrimaryContext::getRuleIndex() const {
  return LangParser::RulePrimary;
}

void LangParser::PrimaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimary(this);
}

void LangParser::PrimaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimary(this);
}


std::any LangParser::PrimaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitPrimary(this);
  else
    return visitor->visitChildren(this);
}

LangParser::PrimaryContext* LangParser::primary() {
  PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, getState());
  enterRule(_localctx, 22, LangParser::RulePrimary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(196);
    atom();
    setState(204);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(197);
        match(LangParser::LPAREN);
        setState(199);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 212209972150272) != 0)) {
          setState(198);
          argExprList();
        }
        setState(201);
        match(LangParser::RPAREN); 
      }
      setState(206);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgExprListContext ------------------------------------------------------------------

LangParser::ArgExprListContext::ArgExprListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LangParser::ExprContext *> LangParser::ArgExprListContext::expr() {
  return getRuleContexts<LangParser::ExprContext>();
}

LangParser::ExprContext* LangParser::ArgExprListContext::expr(size_t i) {
  return getRuleContext<LangParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> LangParser::ArgExprListContext::COMMA() {
  return getTokens(LangParser::COMMA);
}

tree::TerminalNode* LangParser::ArgExprListContext::COMMA(size_t i) {
  return getToken(LangParser::COMMA, i);
}


size_t LangParser::ArgExprListContext::getRuleIndex() const {
  return LangParser::RuleArgExprList;
}

void LangParser::ArgExprListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgExprList(this);
}

void LangParser::ArgExprListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgExprList(this);
}


std::any LangParser::ArgExprListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitArgExprList(this);
  else
    return visitor->visitChildren(this);
}

LangParser::ArgExprListContext* LangParser::argExprList() {
  ArgExprListContext *_localctx = _tracker.createInstance<ArgExprListContext>(_ctx, getState());
  enterRule(_localctx, 24, LangParser::RuleArgExprList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(207);
    expr(0);
    setState(212);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LangParser::COMMA) {
      setState(208);
      match(LangParser::COMMA);
      setState(209);
      expr(0);
      setState(214);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtomContext ------------------------------------------------------------------

LangParser::AtomContext::AtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LangParser::AtomContext::LPAREN() {
  return getToken(LangParser::LPAREN, 0);
}

LangParser::ExprContext* LangParser::AtomContext::expr() {
  return getRuleContext<LangParser::ExprContext>(0);
}

tree::TerminalNode* LangParser::AtomContext::RPAREN() {
  return getToken(LangParser::RPAREN, 0);
}

LangParser::IdentifierContext* LangParser::AtomContext::identifier() {
  return getRuleContext<LangParser::IdentifierContext>(0);
}

LangParser::LiteralContext* LangParser::AtomContext::literal() {
  return getRuleContext<LangParser::LiteralContext>(0);
}


size_t LangParser::AtomContext::getRuleIndex() const {
  return LangParser::RuleAtom;
}

void LangParser::AtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtom(this);
}

void LangParser::AtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtom(this);
}


std::any LangParser::AtomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitAtom(this);
  else
    return visitor->visitChildren(this);
}

LangParser::AtomContext* LangParser::atom() {
  AtomContext *_localctx = _tracker.createInstance<AtomContext>(_ctx, getState());
  enterRule(_localctx, 26, LangParser::RuleAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(221);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LangParser::LPAREN: {
        enterOuterAlt(_localctx, 1);
        setState(215);
        match(LangParser::LPAREN);
        setState(216);
        expr(0);
        setState(217);
        match(LangParser::RPAREN);
        break;
      }

      case LangParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(219);
        identifier();
        break;
      }

      case LangParser::BOOL:
      case LangParser::HEX:
      case LangParser::BITS:
      case LangParser::DEC:
      case LangParser::STRING:
      case LangParser::CHAR: {
        enterOuterAlt(_localctx, 3);
        setState(220);
        literal();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

LangParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LangParser::LiteralContext::BOOL() {
  return getToken(LangParser::BOOL, 0);
}

tree::TerminalNode* LangParser::LiteralContext::STRING() {
  return getToken(LangParser::STRING, 0);
}

tree::TerminalNode* LangParser::LiteralContext::CHAR() {
  return getToken(LangParser::CHAR, 0);
}

tree::TerminalNode* LangParser::LiteralContext::HEX() {
  return getToken(LangParser::HEX, 0);
}

tree::TerminalNode* LangParser::LiteralContext::BITS() {
  return getToken(LangParser::BITS, 0);
}

tree::TerminalNode* LangParser::LiteralContext::DEC() {
  return getToken(LangParser::DEC, 0);
}


size_t LangParser::LiteralContext::getRuleIndex() const {
  return LangParser::RuleLiteral;
}

void LangParser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void LangParser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}


std::any LangParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

LangParser::LiteralContext* LangParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 28, LangParser::RuleLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(223);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2080505856) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

LangParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LangParser::IdentifierContext::Identifier() {
  return getToken(LangParser::Identifier, 0);
}


size_t LangParser::IdentifierContext::getRuleIndex() const {
  return LangParser::RuleIdentifier;
}

void LangParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}

void LangParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}


std::any LangParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

LangParser::IdentifierContext* LangParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 30, LangParser::RuleIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(225);
    match(LangParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BuiltinTypeContext ------------------------------------------------------------------

LangParser::BuiltinTypeContext::BuiltinTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LangParser::BuiltinTypeContext::BUILTIN_BOOL() {
  return getToken(LangParser::BUILTIN_BOOL, 0);
}

tree::TerminalNode* LangParser::BuiltinTypeContext::BUILTIN_BYTE() {
  return getToken(LangParser::BUILTIN_BYTE, 0);
}

tree::TerminalNode* LangParser::BuiltinTypeContext::BUILTIN_INT() {
  return getToken(LangParser::BUILTIN_INT, 0);
}

tree::TerminalNode* LangParser::BuiltinTypeContext::BUILTIN_UINT() {
  return getToken(LangParser::BUILTIN_UINT, 0);
}

tree::TerminalNode* LangParser::BuiltinTypeContext::BUILTIN_LONG() {
  return getToken(LangParser::BUILTIN_LONG, 0);
}

tree::TerminalNode* LangParser::BuiltinTypeContext::BUILTIN_ULONG() {
  return getToken(LangParser::BUILTIN_ULONG, 0);
}

tree::TerminalNode* LangParser::BuiltinTypeContext::BUILTIN_CHAR() {
  return getToken(LangParser::BUILTIN_CHAR, 0);
}

tree::TerminalNode* LangParser::BuiltinTypeContext::BUILTIN_STRING() {
  return getToken(LangParser::BUILTIN_STRING, 0);
}


size_t LangParser::BuiltinTypeContext::getRuleIndex() const {
  return LangParser::RuleBuiltinType;
}

void LangParser::BuiltinTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBuiltinType(this);
}

void LangParser::BuiltinTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBuiltinType(this);
}


std::any LangParser::BuiltinTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LangVisitor*>(visitor))
    return parserVisitor->visitBuiltinType(this);
  else
    return visitor->visitChildren(this);
}

LangParser::BuiltinTypeContext* LangParser::builtinType() {
  BuiltinTypeContext *_localctx = _tracker.createInstance<BuiltinTypeContext>(_ctx, getState());
  enterRule(_localctx, 32, LangParser::RuleBuiltinType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(227);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 66846720) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool LangParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 6: return typeRefSempred(antlrcpp::downCast<TypeRefContext *>(context), predicateIndex);
    case 10: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool LangParser::typeRefSempred(TypeRefContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool LangParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 8);
    case 2: return precpred(_ctx, 7);
    case 3: return precpred(_ctx, 6);
    case 4: return precpred(_ctx, 5);
    case 5: return precpred(_ctx, 4);
    case 6: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void LangParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  langParserInitialize();
#else
  ::antlr4::internal::call_once(langParserOnceFlag, langParserInitialize);
#endif
}
