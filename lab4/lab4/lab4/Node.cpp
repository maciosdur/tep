

#include "Node.h"
#include <sstream>
#include <cmath>
#include <iostream>
#include "Constants.h"

NodeVariable::NodeVariable(std::string varName) {
    name = varName;
    value = 0.0;
}
void NodeVariable::setValue(double val) { 
    value = val; 
}
std::string NodeVariable::getName() const {
    return name; 
}
std::pair<Error, double> NodeVariable::calculate() {
    return std::make_pair(Error(), value); 
}
std::string NodeVariable::toString() const {
    return name; 
}
void NodeVariable::collectVariables(std::vector<NodeVariable*>& vars) {
    vars.push_back(this); 
}
Node* NodeVariable::clone() const {
    return new NodeVariable(*this); 
}
bool NodeVariable::isLeaf() const {
    return true; 
}


NodeNumber::NodeNumber(double val) {
    value = val;
}
std::pair<Error, double> NodeNumber::calculate() {
    return std::make_pair(Error(), value); 
}
std::string NodeNumber::toString() const {
    std::stringstream ss;
    ss << value;
    return ss.str(); 
}
void NodeNumber::collectVariables(std::vector<NodeVariable*>& vars) {}
Node* NodeNumber::clone() const {
    return new NodeNumber(*this); 
}
bool NodeNumber::isLeaf() const {
    return true; 
}


NodeOperator::NodeOperator(std::string op) {
    op_string = op; 
}
NodeOperator::~NodeOperator() {
    for (int i = 0; i < children.size(); ++i) { 
        delete children[i]; 
    } 
}
void NodeOperator::addChild(Node* child) {
    if (child) {
        children.push_back(child); 
        child->setParent(this); 
    } 
}
const std::vector<Node*>& NodeOperator::getChildren() const {
    return children; 
//W wektorze children nie przechowujemy obiektów Node bezpośrednio
//Przechowujemy wskaźniki na nie (Node*)
}
std::string NodeOperator::toString() const { 
    std::string res = op_string; 
    for (int i = 0; i < children.size(); ++i) {
        res += " " + children[i]->toString(); 
    } 
    return res; 
}
void NodeOperator::collectVariables(std::vector<NodeVariable*>& vars) {
    for (int i = 0; i < children.size(); ++i) {
        children[i]->collectVariables(vars); 
    } 
}
bool NodeOperator::isLeaf() const {
    return false; 
}
void NodeOperator::replaceChild(Node* oldChild, Node* newChild) {
    for (int i = 0; i < children.size(); ++i) {
        if (children[i] == oldChild) {
            children[i] = newChild;
            if (newChild) newChild->setParent(this);
            return;
        }
    }
}


NodeOpPlus::NodeOpPlus() : NodeOperator(OP_ADD) {}
std::pair<Error, double> NodeOpPlus::calculate() {

    std::pair<Error, double> res1 = children[0]->calculate();
    if (res1.first.getHasError()) return res1;
    std::pair<Error, double> res2 = children[1]->calculate();
    if (res2.first.getHasError()) return res2;

    return std::make_pair(Error(), res1.second + res2.second);
}
Node* NodeOpPlus::clone() const {
    NodeOpPlus* new_op = new NodeOpPlus();
    for(int i=0; i<children.size(); ++i) {
        new_op->addChild(children[i]->clone());
    }
    return new_op; 
}
int NodeOpPlus::getArity() const {
    return NUM_OF_CHILDREN_FOR_OPERATORS;
}

NodeOpMinus::NodeOpMinus() : NodeOperator(OP_SUB) {}
std::pair<Error, double> NodeOpMinus::calculate() {

    std::pair<Error, double> res1 = children[0]->calculate();
    if (res1.first.getHasError()) return res1;
    std::pair<Error, double> res2 = children[1]->calculate();
    if (res2.first.getHasError()) return res2;

    return std::make_pair(Error(), res1.second - res2.second);
}
Node* NodeOpMinus::clone() const {
    NodeOpMinus* new_op = new NodeOpMinus();
    for(int i=0; i<children.size(); ++i) {
        new_op->addChild(children[i]->clone());
    }
    return new_op; 
}
int NodeOpMinus::getArity() const {
    return NUM_OF_CHILDREN_FOR_OPERATORS; 
}
///////////////////////////////////////////////////////////////////
NodeOpMultiply::NodeOpMultiply() : NodeOperator(OP_MUL) {}
std::pair<Error, double> NodeOpMultiply::calculate() {

    std::pair<Error, double> res1 = children[0]->calculate();
    if (res1.first.getHasError()) return res1;
    std::pair<Error, double> res2 = children[1]->calculate();
    if (res2.first.getHasError()) return res2;

    return std::make_pair(Error(), res1.second * res2.second);
}
Node* NodeOpMultiply::clone() const {
    NodeOpMultiply* new_op = new NodeOpMultiply();
    for(int i=0; i<children.size(); ++i) {
        new_op->addChild(children[i]->clone());
    }
    return new_op; 
}
int NodeOpMultiply::getArity() const {
    return NUM_OF_CHILDREN_FOR_OPERATORS; 
}

////////////////////////////////////////////////////////////////

NodeOpDivide::NodeOpDivide() : NodeOperator(OP_DIV) {}
std::pair<Error, double> NodeOpDivide::calculate() {

    std::pair<Error, double> res1 = children[0]->calculate();
    if (res1.first.getHasError()) return res1;
    std::pair<Error, double> res2 = children[1]->calculate();
    if (res2.first.getHasError()) return res2;

    if (res2.second == 0.0) return std::make_pair(Error(ERR_DIVISION_BY_ZERO), 0.0);

    return std::make_pair(Error(), res1.second / res2.second);
}
Node* NodeOpDivide::clone() const {
    NodeOpDivide* new_op = new NodeOpDivide();
    for(int i=0; i<children.size(); ++i) {
        new_op->addChild(children[i]->clone());
    }
    return new_op; 
}
int NodeOpDivide::getArity() const {
    return NUM_OF_CHILDREN_FOR_OPERATORS; 
}

//////////////////////////////////////////////////////////////

NodeOpSin::NodeOpSin() : NodeOperator(OP_SIN) {}
std::pair<Error, double> NodeOpSin::calculate() {
    std::pair<Error, double> res = children[0]->calculate();
    if (res.first.getHasError()) return res;

    return std::make_pair(Error(), sin(res.second));
}
Node* NodeOpSin::clone() const {
    NodeOpSin* new_op = new NodeOpSin();
    for(int i=0; i<children.size(); ++i) {
        new_op->addChild(children[i]->clone());
    }
    return new_op; }
int NodeOpSin::getArity() const { return 1; }

///////////////////////////////////////////////////////////////

NodeOpCos::NodeOpCos() : NodeOperator(OP_COS) {}
std::pair<Error, double> NodeOpCos::calculate() {
    std::pair<Error, double> res = children[0]->calculate();
    if (res.first.getHasError()) return res;

    return std::make_pair(Error(), cos(res.second));
}

Node* NodeOpCos::clone() const {
    NodeOpCos* new_op = new NodeOpCos();
    for(int i=0; i<children.size(); ++i) {
        new_op->addChild(children[i]->clone());
    }
    return new_op; 
}
int NodeOpCos::getArity() const { return 1; }
