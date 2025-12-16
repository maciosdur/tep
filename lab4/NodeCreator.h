
#pragma once
#include "Node.h"
#include <string>

namespace NodeCreator {
    Node* createNode(const std::string& token);
    bool isVariable(const std::string& token);
    bool isNumber(const std::string& token);
    std::string cleanToken(const std::string& token, bool &changed);
}

