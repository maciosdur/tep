#pragma once
#include <vector>
#include <random>
#include "MyEvaluator.h"

class CIndividual {
public:
    // Konstruktor tworzący losowego osobnika
    CIndividual(MyEvaluator& evaluator, std::mt19937& rng);
    
    // Konstruktor kopiujący
    CIndividual(const CIndividual& other);

    // Gettery
    double getFitness() const { return fitness; }
    std::vector<int> getGenotype() const { return genotype; }

    // Mutacja
    void mutate(double mutProb, std::mt19937& rng, int numGroups, MyEvaluator& evaluator);
    
    // Krzyżowanie (zwraca parę wskaźników na nowe dzieci)
    std::pair<CIndividual*, CIndividual*> crossover(CIndividual* other, double crossProb, std::mt19937& rng, MyEvaluator& evaluator);

private:
    std::vector<int> genotype; // BEZ PODKREŚLENIA
    double fitness;            // BEZ PODKREŚLENIA
    
    // Metoda pomocnicza
    void calculateFitness(MyEvaluator& evaluator);
};