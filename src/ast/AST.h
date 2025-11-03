#pragma once
#include <string>
#include <vector>
#include <memory>

struct ASTNode {
    std::string name;   // тип узла
    std::string value;  // значение
    std::vector<std::shared_ptr<ASTNode>> children;

    ASTNode(const std::string& n) : name(n) {}
    ASTNode(const std::string& n, const std::string& v) : name(n), value(v) {}

    void addChild(std::shared_ptr<ASTNode> child) {
        if (child) children.push_back(child);
    }
};

using ASTNodePtr = std::shared_ptr<ASTNode>;
