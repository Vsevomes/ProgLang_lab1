#include "ParserModule.h"
#include "ErrorCollector.h"
#include "../visitor/ASTBuilder.h"

#include "../../generated/LangLexer.h"
#include "../../generated/LangParser.h"
#include <antlr4-runtime.h>

using namespace antlr4;

ParseResult parseFromString(const std::string &source) {
    ParseResult result;

    ANTLRInputStream input(source);
    LangLexer lexer(&input);

    ErrorCollector errCollector;
    lexer.removeErrorListeners();
    lexer.addErrorListener(&errCollector);

    CommonTokenStream tokens(&lexer);
    tokens.fill();

    LangParser parser(&tokens);
    parser.removeErrorListeners();
    parser.addErrorListener(&errCollector);

    auto tree = parser.source();

    result.errors = errCollector.getErrorsAsStrings();

    ASTBuilder builder;
    antlrcpp::Any a = builder.visit(tree);
    if (!a.has_value()) {
        result.root = std::any_cast<ASTNodePtr>(a);
    }

    return result;
}
