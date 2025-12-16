
#pragma once
#include <string>
#include <vector>
#include <utility>
#include "Error.h"

class NodeVariable;

class Node {

private:
    Node* parent;
public:
    Node() : parent(NULL) {}
    virtual ~Node() {}

    void setParent(Node* p) { parent = p; }
    Node* getParent() const { return parent; }

    virtual std::pair<Error, double> calculate() = 0;
    virtual std::string toString() const = 0;
    virtual void collectVariables(std::vector<NodeVariable*>& vars) = 0;
//Wszystkie klasy muszą mieć metodę collectVariables,
// aby klasa CTree mogła traktować wszystkie węzły polimorficznie

    virtual Node* clone() const = 0;
    virtual bool isLeaf() const = 0;
};

class NodeVariable : public Node {
private:
    std::string name;
    double value;
public:
    NodeVariable(std::string varName);

    void setValue(double value);
    std::string getName() const;

    virtual std::pair<Error, double> calculate();
    virtual std::string toString() const;
    virtual void collectVariables(std::vector<NodeVariable*>& vars);
    virtual Node* clone() const;
    virtual bool isLeaf() const;
};

class NodeNumber : public Node {
private:
    double value;
public:
    NodeNumber(double value);

    virtual std::pair<Error, double> calculate();
    virtual std::string toString() const;
    virtual void collectVariables(std::vector<NodeVariable*>& vars);
    virtual Node* clone() const;
    virtual bool isLeaf() const;
};

class NodeOperator : public Node {
protected:
    std::vector<Node*> children;
    std::string op_string;
public:
    NodeOperator(std::string op);
    virtual ~NodeOperator();
    void addChild(Node* child);
    void replaceChild(Node* oldChild, Node* newChild);
    const std::vector<Node*>& getChildren() const;
    virtual std::string toString() const;
    virtual void collectVariables(std::vector<NodeVariable*>& vars);
    virtual bool isLeaf() const;
    virtual int getArity() const = 0;
};


class NodeOpPlus : public NodeOperator {
public:
    NodeOpPlus();
    virtual std::pair<Error, double> calculate();
    virtual Node* clone() const;
    virtual int getArity() const;
};

class NodeOpMinus : public NodeOperator {
public:
    NodeOpMinus();
    virtual std::pair<Error, double> calculate();
    virtual Node* clone() const;
    virtual int getArity() const;
};

class NodeOpMultiply : public NodeOperator {
public:
    NodeOpMultiply();
    virtual std::pair<Error, double> calculate();
    virtual Node* clone() const;
    virtual int getArity() const;
};

class NodeOpDivide : public NodeOperator {
public:
    NodeOpDivide();
    virtual std::pair<Error, double> calculate();
    virtual Node* clone() const;
    virtual int getArity() const;
};

class NodeOpSin : public NodeOperator {
public:
    NodeOpSin();
    virtual std::pair<Error, double> calculate();
    virtual Node* clone() const;
    virtual int getArity() const;
};

class NodeOpCos : public NodeOperator {
public:
    NodeOpCos();
    virtual std::pair<Error, double> calculate();
    virtual Node* clone() const;
    virtual int getArity() const;
};

