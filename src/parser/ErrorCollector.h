#pragma once
#include <antlr4-runtime.h>
#include <string>
#include <vector>
#include <sstream>
#include <mutex>

// Простая структура ошибки с позицией и текстом
struct ParseError {
    enum class Kind { LEXER, PARSER };

    Kind kind;
    size_t line;
    size_t charPositionInLine;
    std::string message;

    ParseError(Kind k, size_t l, size_t c, std::string m)
        : kind(k), line(l), charPositionInLine(c), message(std::move(m)) {}

    std::string toString() const {
        std::ostringstream oss;
        oss << ((kind == Kind::LEXER) ? "LEXER" : "PARSER")
            << " error at " << line << ":" << charPositionInLine << " - " << message;
        return oss.str();
    }
};

/// ErrorCollector: собирает ошибки парсера и лексера ANTLR4.
/// Можно использовать один экземпляр как для лексера, так и для парсера.
class ErrorCollector : public antlr4::BaseErrorListener {
public:
    ErrorCollector() = default;

    // Перезаписанный метод BaseErrorListener для синтаксических ошибок (parser + lexer)
    void syntaxError(antlr4::Recognizer *recognizer,
                     antlr4::Token *offendingSymbol,
                     size_t line, size_t charPositionInLine,
                     const std::string &msg,
                     std::exception_ptr e) override;

    // Получить все ошибки как объекты
    const std::vector<ParseError>& getErrors() const;

    // Получить все ошибки в виде строк (удобно для ParseResult)
    std::vector<std::string> getErrorsAsStrings() const;

    // Очистить накопленные ошибки
    void clear();

private:
    std::vector<ParseError> errors_;
    mutable std::mutex mutex_; // на случай многопоточного использования
};
