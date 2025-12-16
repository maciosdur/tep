#include "Constants.h"
#include "Tree.h"
#include "NodeCreator.h"
#include "CResult.h"
#include "CError.h"
#include <sstream>
#include <iostream>
#include <algorithm>

Tree::Tree() {
    root = NULL;
    lastBuildFilledMissing = false;
}

Tree::Tree(const Tree& other) {
    std::cout << "COPY_CONSTRUCTOR ";
    root = NULL;
    if (other.root != NULL) {
        root = other.root->clone();
        buildVariablesMap();
    } else {
        root = NULL;
    }
    lastBuildFilledMissing = other.lastBuildFilledMissing;
}

Tree::~Tree() { clear(); }

void Tree::clear() {
    delete root;
    root = NULL;
    variables.clear();
}

void Tree::buildVariablesMap() {
    variables.clear();
    if (root == NULL) return;

    std::vector<NodeVariable*> allVars;
    root->collectVariables(allVars);

    for (int i = 0; i < allVars.size(); ++i) {
        variables[allVars[i]->getName()].push_back(allVars[i]);
    }
}


Node* Tree::buildTreeRecursive(const std::vector<std::string>& tokens, int& position, bool& filledMissing) {
    std::string token;
    
    if (position < (int)tokens.size()) {
        token = tokens[position];
        position++;
    } else {
        filledMissing = true;
        return new NodeNumber(DEFAULT_NODE_VALUE);
    }

    Node* newNode = NodeCreator::createNode(token);

    if (newNode == NULL) {
        std::cout << "Info: Nieznany token '" << token
                  << "', wstawiono '1'." << std::endl;

        filledMissing = true;
        return new NodeNumber(DEFAULT_NODE_VALUE);
    }

    NodeOperator* op = dynamic_cast<NodeOperator*>(newNode);

    if (op != NULL) {
        int arity = op->getArity();
        for (int i = 0; i < arity; ++i) {
            Node* child = buildTreeRecursive(tokens, position, filledMissing);
            op->addChild(child);
        }
    }
    return newNode;
}


void Tree::buildFromString(const std::string& expression) {
    clear();
    std::vector<std::string> tokens;
    std::stringstream ss(expression);
    std::string token;
    while(ss >> token) tokens.push_back(token);

    if (tokens.empty()) {
        std::cout << "Info: Puste wyrazenie. Wstawiono '1'." << std::endl;
        root = new NodeNumber(DEFAULT_NODE_VALUE);
        buildVariablesMap();
        lastBuildFilledMissing = true;
        std::cout << "Przetwarzana bedzie formula: " << printPrefix() << std::endl;
        return;
    }

    int position = 0;
    bool filledMissing = false;
    root = buildTreeRecursive(tokens, position, filledMissing);

    if (position < (int)tokens.size()) {
        std::cout << "Info: Dodatkowe argumenty w wyrazeniu zostaly zignorowane." << std::endl;
    }

    buildVariablesMap(); 
    lastBuildFilledMissing = filledMissing;

    if (filledMissing) {std::cout << "Info: Wyrazenie bylo niepelne i zostalo uzupełnione" << std::endl;}
    std::cout << "Przetwarzana bedzie formula: " << printPrefix() << std::endl;
}

std::vector<std::string> Tree::getUniqueVariableNames() {
    std::vector<std::string> names;
    for (std::map<std::string, std::vector<NodeVariable*> >::iterator it = variables.begin(); it != variables.end(); ++it) {
        names.push_back(it->first);
    }
    std::sort(names.begin(), names.end());
    return names;
}

void Tree::setVariableValues(const std::vector<double>& values) {
    std::vector<std::string> uniqueNames = getUniqueVariableNames();
    for (int i = 0; i < values.size() && i < uniqueNames.size(); ++i) {
        const std::string& name = uniqueNames[i];
        std::vector<NodeVariable*>& allOccurences = variables[name];
        for (int j = 0; j < allOccurences.size(); ++j) {
            allOccurences[j]->setValue(values[i]);
        }
    }
}

std::pair<Error, double> Tree::calculateExpression(const std::vector<double>& values) {
    if (root == NULL) {
        return std::make_pair(Error(ERR_EMPTY_TREE), 0.0);
    }

    if (values.size() != variables.size()) {
        std::stringstream ss;
        ss << "Blad: Podano " << values.size() << " wartosci, a oczekiwano " << variables.size() << ".";
        return std::make_pair(Error(ERR_INVALID_ARG_COUNT, ss.str()), 0.0);
    }

    setVariableValues(values);
    return root->calculate();
}

std::string Tree::printPrefix() const {
    if (root == NULL) return "Drzewo jest puste.";
    return root->toString();
}


Tree& Tree::operator=(const Tree& other) {
    std::cout << "COPY_ASSIGNMENT ";
    if (this == &other) return *this;
    clear();
    if (other.root != NULL) {
        root = other.root->clone();
        buildVariablesMap();
    }
    lastBuildFilledMissing = other.lastBuildFilledMissing;
    return *this;
}

const Tree Tree::operator+(const Tree& other) const {
    if (this->root == NULL) return Tree(other);
    if (other.root == NULL) return Tree(*this);

    Tree result(*this);
    Node* targetLeaf = result.findFirstLeaf(result.root);
    if (targetLeaf == NULL) return result;

    Node* newSubtree = other.root->clone();

    if (targetLeaf == result.root) {
        delete result.root;
        result.root = newSubtree;
    } else {
        Node* parent = targetLeaf->getParent();
        NodeOperator* parentOp = dynamic_cast<NodeOperator*>(parent);
        if (parentOp) {
            parentOp->replaceChild(targetLeaf, newSubtree);
            delete targetLeaf;
        }
    }
    result.buildVariablesMap();
    return result;
}

void Tree::join(const Tree& other) { *this = *this + other; }

Node* Tree::findFirstLeaf(Node* startNode) {
    if (startNode == NULL || startNode->isLeaf()) return startNode;

    NodeOperator* op = dynamic_cast<NodeOperator*>(startNode);
    if (op) {
        const std::vector<Node*>& children = op->getChildren();
        for (int i = 0; i < children.size(); ++i) {
            Node* foundLeaf = findFirstLeaf(children[i]);
            if (foundLeaf != NULL) return foundLeaf;
        }
    }
    return NULL;
}


Node* Tree::findDoubleLeafNode(Node* startNode) {
    if (startNode == NULL) return NULL;

    NodeOperator* op = dynamic_cast<NodeOperator*>(startNode);
    if (op) {
        const std::vector<Node*>& children = op->getChildren();
        bool allNumbers = !children.empty();
        for (int i = 0; i < children.size(); ++i) {
            if (dynamic_cast<NodeNumber*>(children[i]) == NULL) { allNumbers = false; break; }
        }
        if (allNumbers) {
            std::pair<Error, double> res = startNode->calculate();
            if (!res.first.getHasError()) {
                NodeNumber* newNode = new NodeNumber(res.second);
                Node* parent = startNode->getParent();
                if (parent == NULL) { 
                    delete root;
                    root = newNode;
                    newNode->setParent(NULL);
                } else { 
                    NodeOperator* parentOp = dynamic_cast<NodeOperator*>(parent);
                    if (parentOp) {
                        parentOp->replaceChild(startNode, newNode);
                        delete startNode;
                    } else {
                        delete newNode;
                        return NULL;
                    }
                }
                buildVariablesMap();
                return newNode; 
            }
            return NULL; 
        }
        for (int i = 0; i < children.size(); ++i) {
            Node* found = findDoubleLeafNode(children[i]);
            if (found != NULL) return found;
        }
    }
    return NULL;
}


void Tree::optimaze() {
    while (true) {
        Node* changed = findDoubleLeafNode(root);
        if (changed == NULL) break;
    }
}

CResult<Tree*, CError> Tree::buildFromStringResult(const std::string& expression) {
    clear();

    std::vector<std::string> tokens;
    std::stringstream ss(expression);
    std::string token;
    while(ss >> token) tokens.push_back(token);

    if (tokens.empty()) {
        root = new NodeNumber(DEFAULT_NODE_VALUE);
        buildVariablesMap();
        lastBuildFilledMissing = true;
        return CResult<Tree*, CError>::cFail(new CError("Puste wyrażenie"));
    }

    int position = 0;
    bool filledMissing = false;
    root = buildTreeRecursive(tokens, position, filledMissing);

    if (position < (int)tokens.size()) {
        std::cout << "Info: Dodatkowe argumenty w wyrażeniu zostały zignorowane." << std::endl;
    }

    buildVariablesMap();
    lastBuildFilledMissing = filledMissing;

    if (filledMissing) {
        std::cout << "Info: Wyrażenie było niepełne i zostało uzupełnione" << std::endl;
        return CResult<Tree*, CError>::cFail(new CError("Wyrażenie niekompletne"));
    }

    return CResult<Tree*, CError>::cOk(this);
}

// Konstruktor przenoszący
Tree::Tree(Tree&& other) {
    // 1. "Kradniemy" zasoby
    root = other.root;
    variables = other.variables; // Mapę też możemy przenieść
    lastBuildFilledMissing = other.lastBuildFilledMissing;

    // 2. Zerujemy źródło, aby destruktor 'other' nie usunął root
    other.root = NULL;
    other.variables.clear();
    
    std::cout << "MOVE_CONSTRUCTOR " << std::endl;
}

// Operator przypisania przenoszącego
Tree& Tree::operator=(Tree&& other) {
    // 1. Zabezpieczenie przed przypisaniem do samego siebie
    if (this == &other) return *this;

    // 2. Musimy zwolnić aktualną pamięć (wywołujemy Twoją metodę clear)
    clear();

    // 3. Przejmujemy zasoby z drugiego obiektu
    root = other.root;
    variables = other.variables;
    lastBuildFilledMissing = other.lastBuildFilledMissing;

    // 4. Bardzo ważne: odcinamy źródło od wskaźników
    other.root = NULL;
    other.variables.clear();

    std::cout << "MOVE_ASSIGNMENT " << std::endl;
    return *this;
}


