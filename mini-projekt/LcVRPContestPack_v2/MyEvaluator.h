#pragma once
#include <vector>
#include <string>
#include <map>

class MyEvaluator {
public:
    MyEvaluator();
    
    // Metody używane w main.cpp
    bool loadInstance(const std::string &path);
    int getNumOfCustomers() const;
    int getNumOfGroups() const;

    // Metoda używana przez CIndividual
    double calculateFitness(const std::vector<int> &genotyp) const;

private:
    int dimension;
    int capacity;
    int numOfGroups;
    
    std::map<int, std::pair<double, double>> coords;
    std::vector<int> demands;
    std::vector<int> permutation;

    double getDistance(int id1, int id2) const;
};