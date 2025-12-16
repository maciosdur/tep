#include <iostream>
#include "Tree.h" 

int main() {

    Tree c_sum, c_a, c_b;

    c_a.buildFromString("+ * 2 * * sin 4 ");
    c_a.optimaze();
    std::cout << "c_a: " << c_a.printPrefix() << std::endl;
    c_b.buildFromString("/ 3 0");

    std::cout << "\nStan poczatkowy:" << std::endl;
    std::cout << "c_a: " << c_a.printPrefix() << std::endl;
    std::cout << "c_b: " << c_b.printPrefix() << std::endl;
    std::cout << "c_sum: " << c_sum.printPrefix() << std::endl;

    std::cout << "\nWykonuje operacje c_sum = c_a + c_b;" << std::endl;
    c_sum = c_a + c_b;

std::cout << "\nc_sum po operacji: " << c_sum.printPrefix() << std::endl;
std::cout << "c_a po operacji: " << c_a.printPrefix() << std::endl;
std::cout << "c_b po operacji: " << c_b.printPrefix() << std::endl;
std::vector<double> values;
std::pair<Error,double> result = c_b.calculateExpression(values);
    if (result.first.getHasError()) {
        std::cout << result.first.getMessage() << std::endl;
    } else {
        std::cout << "Wynik: " << result.second << std::endl;
    }
std::cout << "c_sum: " << c_sum.printPrefix() << std::endl;



    

    return 0;
}
//g++ test.cpp App.cpp Tree.cpp Node.cpp NodeCreator.cpp Error.cpp -o Tester