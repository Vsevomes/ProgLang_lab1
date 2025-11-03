#include "ErrorCollector.h"

void ErrorCollector::syntaxError(antlr4::Recognizer *recognizer,
                                 antlr4::Token *offendingSymbol,
                                 size_t line, size_t charPositionInLine,
                                 const std::string &msg,
                                 std::exception_ptr /*e*/)
{
    // Определим, от кого пришла ошибка (лексер или парсер).
    // Если recognizer - это Lexer -> лексическая ошибка, иначе синтаксическая.
    ParseError::Kind kind = ParseError::Kind::PARSER;
    if (dynamic_cast<antlr4::Lexer*>(recognizer) != nullptr) {
        kind = ParseError::Kind::LEXER;
    }

    std::ostringstream oss;
    // Если есть offendingSymbol, можно добавить его текст
    if (offendingSymbol != nullptr) {
        oss << msg << " (offending: \"" << offendingSymbol->getText() << "\")";
    } else {
        oss << msg;
    }

    ParseError pe(kind, line, charPositionInLine, oss.str());

    {
        std::lock_guard<std::mutex> lock(mutex_);
        errors_.push_back(std::move(pe));
    }
}

const std::vector<ParseError>& ErrorCollector::getErrors() const {
    return errors_;
}

std::vector<std::string> ErrorCollector::getErrorsAsStrings() const {
    std::vector<std::string> out;
    std::lock_guard<std::mutex> lock(mutex_);
    out.reserve(errors_.size());
    for (const auto &e : errors_) out.push_back(e.toString());
    return out;
}

void ErrorCollector::clear() {
    std::lock_guard<std::mutex> lock(mutex_);
    errors_.clear();
}
