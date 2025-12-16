#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "CResult.h"
#include "CError.h"
#include "Tree.h"

template <typename T>
class CResultSaver {
public:
    static void saveToFile(const CResult<T, CError>& result, const std::string& filename) {
        std::ofstream file(filename.c_str());
        if (!file.is_open()) return;

        if (result.bIsSuccess()) {
            file << "Brak bledow. (Wynik typu nie-Tree nie jest zapisywany)" << std::endl;
        } else {
            const std::vector<CError*>& errors = result.vGetErrors();
            for (size_t i = 0; i < errors.size(); ++i) {
                file << "Error: " << errors[i]->sGetDescription() << std::endl;
            }
        }

        file.close();
    }
};

//------
template <>
class CResultSaver<Tree*> {
public:
    static void saveToFile(const CResult<Tree*, CError>& result, const std::string& filename) {
        std::ofstream file(filename.c_str());
        if (!file.is_open()) return;

        if (result.bIsSuccess()) {
            Tree* tree = result.cGetValue(); 
            if (tree != nullptr) {
                file << "Drzewo w postaci prefiksowej: " << tree->printPrefix() << std::endl;
            } else {
                file << "Brak drzewa do zapisania." << std::endl;
            }
        } else {
            const std::vector<CError*>& errors = result.vGetErrors();
            for (size_t i = 0; i < errors.size(); ++i) {
                file << "Error: " << errors[i]->sGetDescription() << std::endl;
            }
        }

        file.close();
    }
};

