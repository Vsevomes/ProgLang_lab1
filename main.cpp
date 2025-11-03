#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

#include "antlr4-runtime.h"
#include "generated/LangLexer.h"
#include "generated/LangParser.h"

#include "src/parser/ErrorCollector.h"
#include "src/visitor/ASTBuilder.h"
#include "src/ast/AST.h"

using namespace antlr4;

void printAST(const std::shared_ptr<ASTNode> &node, std::ostream &out, int indent = 0) {
    if (!node) return;
    out << std::string(indent, ' ') << node->name;
    if (!node->value.empty()) out << " (" << node->value << ")";
    out << "\n";
    for (const auto &child : node->children) {
        printAST(child, out, indent + 2);
    }
}

int main(int argc, const char *argv[]) {
    if (argc < 3) {
        std::cerr << "Использование: " << argv[0] << " <входной_файл> <выходной_файл>\n";
        return 1;
    }

    const std::string inputFile = argv[1];
    const std::string outputFile = argv[2];

    // Чтение входного файла
    std::ifstream stream(inputFile);
    if (!stream.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << inputFile << "\n";
        return 1;
    }

    ANTLRInputStream input(stream);
    LangLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LangParser parser(&tokens);

    // Подключаем сборщик ошибок
    ErrorCollector errorCollector;
    parser.removeErrorListeners();
    parser.addErrorListener(&errorCollector);

    // Запуск парсера
    LangParser::SourceContext *tree = parser.source();

    // Проверяем ошибки
    auto errors = errorCollector.getErrors();
    if (!errors.empty()) {
        std::cerr << "Ошибки парсера:\n";
        for (const auto &err : errors) {
            std::cerr << "  " << err.toString() << "\n";
        }
        return 1;
    } else {
        std::cerr << "Парсинг завершен без ошибок.\n";
    }

    // Строим AST
    ASTBuilder builder;
    antlrcpp::Any result = builder.visitSource(tree);

    // Извлекаем дерево
    std::shared_ptr<ASTNode> ast;
    try {
        ast = std::any_cast<std::shared_ptr<ASTNode>>(result);
    } catch (const std::bad_any_cast &e) {
        std::cerr << "Ошибка при построении AST: " << e.what() << "\n";
        return 1;
    }

    // Проверяем, пустое ли дерево
    if (!ast) {
        std::cerr << "AST пуст.\n";
        return 1;
    }

    // Записываем дерево в выходной файл
    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть выходной файл " << outputFile << "\n";
        return 1;
    }

    printAST(ast, outFile);
    std::cerr << "AST записан в файл: " << outputFile << "\n";

    return 0;
}
