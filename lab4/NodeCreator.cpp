#include "NodeCreator.h"
#include "Constants.h"
#include <cctype>
#include <cstdlib>
#include <iostream>


bool NodeCreator::isNumber(const std::string& token) {
    if (token.empty()) return false;

    for (int i = 0; i < token.length(); ++i) {
        unsigned char c = token[i];
        if (!isdigit(c)) return false;
    }
    return true;
}

std::string NodeCreator::cleanToken(const std::string& token, bool& changed) {
    std::string cleaned;
    changed = false;

    for (int i = 0; i < token.length(); ++i) {
        unsigned char c = token[i];
        if (isalnum(c)) {
            cleaned.push_back(c);
        } else {
            changed = true;
        }
    }
    return cleaned;
}

bool NodeCreator::isVariable(const std::string& token) {
    if (token.empty()) return false;
    bool hasLetter = false;
    int i = 0;

    while (i < token.length() && !hasLetter) {
        if (isalpha((unsigned char)token[i])) {
            hasLetter = true; 
        }
        i++; 
    }
    return hasLetter;
}

Node* NodeCreator::createNode(const std::string& token) {

    if (token == OP_ADD) return new NodeOpPlus();
    if (token == OP_SUB) return new NodeOpMinus();
    if (token == OP_MUL) return new NodeOpMultiply();
    if (token == OP_DIV) return new NodeOpDivide();
    if (token == OP_SIN) return new NodeOpSin();
    if (token == OP_COS) return new NodeOpCos();

    if (isNumber(token)) {
        double val = atof(token.c_str());
        return new NodeNumber(val);
    }

    bool changed = false;
    std::string cleaned = cleanToken(token, changed);

    if (isVariable(cleaned)) {
        if (changed) {
            std::cout << "Info: token '" << token
                      << "' zawieral niedozwolone znaki i zostal zmodyfikowany do '"
                      << cleaned << std::endl;
        }
        return new NodeVariable(cleaned);
    }

    return NULL;
}
