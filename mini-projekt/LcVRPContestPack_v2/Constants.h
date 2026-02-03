#pragma once
#include <string>

namespace Cst {
    // Parametry algorytmu (wymagane przez main.cpp)
    const int POP_SIZE = 100;
    const double CROSS_PROB = 0.6;
    const double MUT_PROB = 0.05;
    const double MAX_TIME_SECONDS = 4.0;
    const int DEBUG_ITERATION_STEP = 1;

    // Stałe do parsera plików (wymagane przez MyEvaluator.cpp)
    const std::string DIMENSION = "DIMENSION";
    const std::string CAPACITY = "CAPACITY";
    const std::string PERMUTATION = "PERMUTATION";
    const std::string NODE_COORD_SECTION = "NODE_COORD_SECTION";
    const std::string DEMAND_SECTION = "DEMAND_SECTION";
    const std::string DEPOT_SECTION = "DEPOT_SECTION";
    const std::string COLON = ":";
    const int DEPOT_ID = 1;
    
    const double PENALTY_FACTOR = 1000.0; // Kara za przeładowanie
    const double ERROR_FITNESS = 1e9;
}