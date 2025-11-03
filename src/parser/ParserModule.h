#pragma once

#include "../ast/AST.h"
#include <string>
#include <vector>

struct ParseResult {
    ASTNodePtr root;               // nullptr при неуспешном построении AST
    std::vector<std::string> errors;
};

/// Разбирает исходный код `source` и возвращает AST + список ошибок.
/// Работает с сгенерированными файлами ANTLR (LangLexer/LangParser) и
/// системой ErrorCollector + ASTBuilder (visitor).
ParseResult parseFromString(const std::string &source);
