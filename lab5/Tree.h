
#pragma once
#include "Node.h"
#include "CResult.h"
#include "CError.h"
#include <string>
#include <vector>
#include <map>
#include <utility>

class Tree {
private:
    Node* root;
    std::map<std::string, std::vector<NodeVariable*> > variables;
    void clear();
    void buildVariablesMap();
    Node* buildTreeRecursive(const std::vector<std::string>& tokens, int& position, bool &filledMissing);
    Node* findFirstLeaf(Node* startNode);
    void setVariableValues(const std::vector<double>& values);
    bool lastBuildFilledMissing;
    Node* findDoubleLeafNode(Node* startNode); 

public:
    Tree();
    Tree(const Tree& other);
    ~Tree();
    
    void buildFromString(const std::string& expression);
    std::pair<Error, double> calculateExpression(const std::vector<double>& values);
    std::vector<std::string> getUniqueVariableNames();
    std::string printPrefix() const;
    CResult<Tree*, CError> buildFromStringResult(const std::string& expression);

    void optimaze();
    void join(const Tree& other);
    Tree& operator=(const Tree& other);
    Tree(Tree&& other); // Konstruktor przenoszący
    Tree& operator=(Tree&& other); // Operator przypisania przenoszącego
    const Tree operator+(const Tree& other) const;

};

