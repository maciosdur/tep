

#pragma once 
#include "Tree.h"
#include <string> 

class App {
private:
    Tree mainTree;

    void cmdHelp();
    void cmdEnter(const std::string& expression);
    void cmdPrint();
    void cmdVars();
    void cmdComp(const std::string& tail);
    void cmdJoin(const std::string& expression);
    void cmdLeafs();

public:
    void run();
};

