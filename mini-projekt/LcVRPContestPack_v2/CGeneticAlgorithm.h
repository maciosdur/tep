#pragma once
#include <vector>
#include <random>
#include "CIndividual.h"
#include "MyEvaluator.h"

class CGeneticAlgorithm {
public:
    CGeneticAlgorithm(int popSize, double crossProb, double mutProb, MyEvaluator& evaluator);
    ~CGeneticAlgorithm();

    void initialize();      // main.cpp woła to
    void runIteration();    // main.cpp woła to
    double getBestFitness(); // main.cpp woła to

private:
    int popSize;
    double crossProb;
    double mutProb;
    MyEvaluator& evaluator;
    std::mt19937 rng;
    
    // Wektor wskaźników (ręczne zarządzanie pamięcią)
    std::vector<CIndividual*> population;

    // Metody pomocnicze
    CIndividual* selectParent();
    void clearPopulation();
};