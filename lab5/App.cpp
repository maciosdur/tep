

#include "App.h"
#include "Constants.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void App::run() {
    std::string line;
    cmdHelp(); 

    bool isRunning = true;
    while (isRunning && std::getline(std::cin, line)) {
        std::cout << "> ";
        
        std::stringstream line_stream(line);
        std::string command;
        line_stream >> command;
        
        if (!command.empty()) {
            if (command == CMD_EXIT) { 
                isRunning = false;
            } else if (command == CMD_HELP) {
                cmdHelp();
            } else if (command == CMD_ENTER) {
                std::string expression;
                std::getline(line_stream >> std::ws, expression);
                cmdEnter(expression);
            } else if (command == CMD_PRINT) {
                cmdPrint();
            } else if (command == CMD_VARS) {
                cmdVars();
            } else if (command == CMD_COMP) {
                std::string tail;
                std::getline(line_stream >> std::ws, tail);
                cmdComp(tail);
            } else if (command == CMD_JOIN) {
                std::string expression;
                std::getline(line_stream >> std::ws, expression);
                cmdJoin(expression);
            }
             else {
                std::cout << Error::defaultMessage(ERR_UNKNOWN_CMD) << std::endl;
            }
        }
    
    }
    std::cout << "Program zakończony" << std::endl;
}


void App::cmdHelp() {
    std::cout << "--- lista komend ---\n"
              << "enter <formula>   - Wprowadz nowe wyrazenie w notacji prefiksowej\n"
              << "vars              - Wyswietl zmienne z wyrazenia\n"
              << "print             - Wyswietl biezace wyrazenie\n"
              << "comp <v1> <v2>... - Oblicz wyrazenie, podajac wartosci dla zmiennych\n"
              << "join <formula>    - Dolacz nowe wyrazenie do biezacego\n"
              << "help              - Wyswietl menu\n"
              << "exit              - Zakoncz program\n"
              << "--------------------\n";
}

void App::cmdEnter(const std::string& expression) {
    mainTree.buildFromString(expression);
}

void App::cmdPrint() {
    std::cout << mainTree.printPrefix() << std::endl;
}

void App::cmdVars() {
    std::vector<std::string> vars = mainTree.getUniqueVariableNames();
    if (vars.empty()) {
        std::cout << "Brak zmiennych w wyrazeniu." << std::endl;
    } else {
        std::cout << "Zmienne z aktualnie wprowadzonego drzewa: ";
        for (size_t i = 0; i < vars.size(); ++i) {
            std::cout << vars[i] << " ";
        }
        std::cout << std::endl;
    }
}

void App::cmdComp(const std::string& tail) {
    std::stringstream ss(tail);
    std::vector<double> values;
    double val;
    while (ss >> val) values.push_back(val);

    std::pair<Error,double> result = mainTree.calculateExpression(values);
    if (result.first.getHasError()) {
        std::cout << result.first.getMessage() << std::endl;
    } else {
        std::cout << "Wynik: " << result.second << std::endl;
    }
}

void App::cmdJoin(const std::string& expression) {
    Tree join_tree;
    join_tree.buildFromString(expression);
    mainTree.join(join_tree);
    std::cout << "Nowe wyrazenie: " << mainTree.printPrefix() << std::endl;
}


