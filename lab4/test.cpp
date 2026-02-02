#include <iostream>
#include "Tree.h" 
#include "CError.h"
#include "CResult.h"
#include "CResultSaver.h" 
#include <string>


//------
CResult<int, CError> divide(int a, int b) {
    if (b == 0) return CResult<int, CError>::cFail(new CError("Division by zero"));
    return CResult<int, CError>::cOk(a / b);
}

//------
CResult<void, CError> doSomething(bool fail) {
    if (fail) {
        std::vector<CError*> errors;
        errors.push_back(new CError("First error"));
        errors.push_back(new CError("Second error"));

        return CResult<void, CError>::cFail(errors);
    }

    return CResult<void, CError>::cOk();
}

//------
CResult<Tree*, CError> buildTreeFromExpression(const std::string& expr) {
    if (expr.empty()) {
        return CResult<Tree*, CError>::cFail(new CError("Wyrażenie jest puste"));
    }

    Tree* tree = new Tree();
    tree->buildFromString(expr);

    
    if (tree->printPrefix() == "Drzewo jest puste.") {
        delete tree; 
        return CResult<Tree*, CError>::cFail(new CError("Niepoprawne wyrażenie"));
    }

    return CResult<Tree*, CError>::cOk(tree);
}

//------
int main() {
    std::string filename = "results.txt";

    // --- Test CResult<int, CError> ---
    auto result1 = divide(10, 2);
    auto result2 = divide(5, 0);
    CResultSaver<int>::saveToFile(result1, filename);
    CResultSaver<int>::saveToFile(result2, filename);

    std::cout << "Test CResult<int, CError>:" << std::endl;
    if (result1.bIsSuccess())
        std::cout << "10 / 2 = " << result1.cGetValue() << std::endl;
    else
        for (auto err : result1.vGetErrors())
            std::cout << "Error: " << err->sGetDescription() << std::endl;

    if (result2.bIsSuccess())
        std::cout << "5 / 0 = " << result2.cGetValue() << std::endl;
    else
        for (auto err : result2.vGetErrors())
            std::cout << "Error: " << err->sGetDescription() << std::endl;

    // --- Test CResult<void, CError> ---
    auto voidResult1 = doSomething(false);
    auto voidResult2 = doSomething(true);

    CResultSaver<void>::saveToFile(voidResult1, filename);
    CResultSaver<void>::saveToFile(voidResult2, filename);

    std::cout << "\nTest CResult<void, CError>:" << std::endl;
    if (voidResult1.bIsSuccess())
        std::cout << "doSomething(false) succeeded" << std::endl;
    else
        for (auto err : voidResult1.vGetErrors())
            std::cout << "Error: " << err->sGetDescription() << std::endl;

    if (voidResult2.bIsSuccess())
        std::cout << "doSomething(true) succeeded" << std::endl;
    else
        for (auto err : voidResult2.vGetErrors())
            std::cout << "Error: " << err->sGetDescription() << std::endl;

    // --- Test CResult<Tree*, CError> ---
    std::string expr1 = "+ 2 3";
    std::string expr2 = "";     

    auto treeResult1 = buildTreeFromExpression(expr1);
    auto treeResult2 = buildTreeFromExpression(expr2);

    CResultSaver<Tree*>::saveToFile(treeResult1, filename);
    CResultSaver<Tree*>::saveToFile(treeResult2, filename);

    std::cout << "\nTest CResult<Tree*, CError>:" << std::endl;

    if (treeResult1.bIsSuccess()) {
        std::cout << "Wyrażenie \"" << expr1 << "\" -> " 
                  << treeResult1.cGetValue()->printPrefix() << std::endl;
        delete treeResult1.cGetValue();
    } else
        for (auto err : treeResult1.vGetErrors())
            std::cout << "Error: " << err->sGetDescription() << std::endl;

    if (treeResult2.bIsSuccess()) {
        std::cout << "Wyrażenie \"" << expr2 << "\" -> " 
                  << treeResult2.cGetValue()->printPrefix() << std::endl;
        delete treeResult2.cGetValue();
    } else
        for (auto err : treeResult2.vGetErrors())
            std::cout << "Error: " << err->sGetDescription() << std::endl;

    return 0;
}

//g++ test.cpp App.cpp Tree.cpp Node.cpp NodeCreator.cpp Error.cpp -o Tester