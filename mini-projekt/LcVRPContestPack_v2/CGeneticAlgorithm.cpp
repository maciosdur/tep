#include "CGeneticAlgorithm.h"
#include <limits>

CGeneticAlgorithm::CGeneticAlgorithm(int ps, double cp, double mp, MyEvaluator& eval)
    : popSize(ps), crossProb(cp), mutProb(mp), evaluator(eval) 
{
    std::random_device rd;
    rng = std::mt19937(rd());
}

CGeneticAlgorithm::~CGeneticAlgorithm() {
    clearPopulation();
}

void CGeneticAlgorithm::clearPopulation() {
    for (CIndividual* ind : population) {
        delete ind;
    }
    population.clear();
}

void CGeneticAlgorithm::initialize() {
    clearPopulation();
    for (int i = 0; i < popSize; ++i) {
        population.push_back(new CIndividual(evaluator, rng));
    }
}

void CGeneticAlgorithm::runIteration() {
    std::vector<CIndividual*> newPopulation;
    newPopulation.reserve(popSize);

    while (newPopulation.size() < popSize) {
        // 1. Wybór rodziców (Turniej)
        CIndividual* p1 = selectParent();
        CIndividual* p2 = selectParent();

        // 2. Krzyżowanie (zwraca nowe obiekty stworzone przez new)
        std::pair<CIndividual*, CIndividual*> children = p1->crossover(p2, crossProb, rng, evaluator);
        
        CIndividual* c1 = children.first;
        CIndividual* c2 = children.second;

        // 3. Mutacja
        c1->mutate(mutProb, rng, evaluator.getNumOfGroups(), evaluator);
        c2->mutate(mutProb, rng, evaluator.getNumOfGroups(), evaluator);

        // 4. Dodanie do nowej populacji
        newPopulation.push_back(c1);
        
        if (newPopulation.size() < popSize) {
            newPopulation.push_back(c2);
        } else {
            delete c2; // Jeśli c2 się nie zmieścił, musimy go usunąć ręcznie!
        }
    }

    // 5. Podmiana starej populacji na nową
    clearPopulation(); // Usuwa stare obiekty z pamięci
    population = newPopulation;
}

CIndividual* CGeneticAlgorithm::selectParent() {
    // Prosty turniej losowy: wybieramy 2 i bierzemy lepszego
    std::uniform_int_distribution<int> dist(0, population.size() - 1);
    
    CIndividual* i1 = population[dist(rng)];
    CIndividual* i2 = population[dist(rng)];

    if (i1->getFitness() < i2->getFitness()) {
        return i1;
    } else {
        return i2;
    }
}

double CGeneticAlgorithm::getBestFitness() {
    if (population.empty()) return 0.0;

    double best = std::numeric_limits<double>::max();
    for (CIndividual* ind : population) {
        if (ind->getFitness() < best) {
            best = ind->getFitness();
        }
    }
    return best;
}