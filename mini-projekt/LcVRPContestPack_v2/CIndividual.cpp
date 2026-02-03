#include "CIndividual.h"

using namespace std; // To naprawia błąd z mt19937

// Konstruktor losowy
CIndividual::CIndividual(MyEvaluator& evaluator, mt19937& rng) {
    int n = evaluator.getNumOfCustomers();
    int k = evaluator.getNumOfGroups();
    
    uniform_int_distribution<int> dist(0, k - 1);
    
    genotype.resize(n);
    for(int i = 0; i < n; ++i) {
        genotype[i] = dist(rng);
    }
    
    calculateFitness(evaluator);
}

// Konstruktor kopiujący
CIndividual::CIndividual(const CIndividual& other) {
    genotype = other.genotype; // Poprawione: bez "_" na końcu
    fitness = other.fitness;   // Poprawione: bez "_" na końcu
}

// Metoda licząca fitness (zamiast Evaluate)
void CIndividual::calculateFitness(MyEvaluator& evaluator) {
    fitness = evaluator.calculateFitness(genotype);
}

// Mutacja
void CIndividual::mutate(double mutProb, mt19937& rng, int numGroups, MyEvaluator& evaluator) {
    uniform_real_distribution<double> probDist(0.0, 1.0);
    uniform_int_distribution<int> groupDist(0, numGroups - 1);
    
    bool changed = false;
    for (size_t i = 0; i < genotype.size(); ++i) {
        if (probDist(rng) < mutProb) {
            genotype[i] = groupDist(rng);
            changed = true;
        }
    }

    // Jeśli genotyp się zmienił, musimy przeliczyć fitness!
    if (changed) {
        calculateFitness(evaluator);
    }
}

// Krzyżowanie
pair<CIndividual*, CIndividual*> CIndividual::crossover(CIndividual* other, double crossProb, mt19937& rng, MyEvaluator& evaluator) {
    // Tworzymy kopie rodziców jako bazę dla dzieci
    CIndividual* child1 = new CIndividual(*this);
    CIndividual* child2 = new CIndividual(*other);

    uniform_real_distribution<double> probDist(0.0, 1.0);

    // Sprawdzamy czy krzyżowanie zachodzi
    if (probDist(rng) < crossProb) {
        uniform_int_distribution<int> cutDist(1, (int)genotype.size() - 2);
        int cutPoint = cutDist(rng);

        // Wymiana genów
        for (size_t i = cutPoint; i < genotype.size(); ++i) {
            child1->genotype[i] = other->genotype[i];
            child2->genotype[i] = this->genotype[i];
        }
        
        // Po wymianie genów trzeba przeliczyć fitness dzieci
        child1->calculateFitness(evaluator);
        child2->calculateFitness(evaluator);
    }

    return make_pair(child1, child2);
}