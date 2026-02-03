#include "MyEvaluator.h"
#include "Constants.h"
#include <fstream>
#include <cmath>
#include <iostream>

using namespace std;

// Konstruktor
MyEvaluator::MyEvaluator() 
    : dimension(0), capacity(0), numOfGroups(0) 
{
}

// Gettery (używane w main.cpp i CIndividual)
int MyEvaluator::getNumOfCustomers() const {
    // Liczba klientów to wymiar minus 1 (baza)
    return dimension - 1;
}

int MyEvaluator::getNumOfGroups() const {
    return numOfGroups;
}

// Metoda pomocnicza: Obliczanie dystansu euklidesowego
double MyEvaluator::getDistance(int id1, int id2) const {
    // Pobieramy współrzędne z mapy coords
    // .at() jest bezpieczniejsze niż [], bo rzuci błąd jak nie znajdzie klucza
    double x1 = coords.at(id1).first;
    double y1 = coords.at(id1).second;
    
    double x2 = coords.at(id2).first;
    double y2 = coords.at(id2).second;

    double dx = x1 - x2;
    double dy = y1 - y2;

    return sqrt(dx*dx + dy*dy);
}

// Główna funkcja wczytująca plik
bool MyEvaluator::loadInstance(const string &path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "BLAD: Nie mozna otworzyc pliku: " << path << endl;
        return false;
    }

    // Resetowanie zmiennych przed wczytaniem
    coords.clear();
    demands.clear();
    permutation.clear();
    dimension = 0;
    capacity = 0;
    
    string token;
    long totalDemand = 0;

    // Pętla czytająca plik słowo po słowie
    while (file >> token) {
        if (token == Cst::DIMENSION) {
            string temp;
            file >> temp; // Wczytaj dwukropek lub liczbę
            if (temp == Cst::COLON) file >> dimension;
            else dimension = stoi(temp);

            // Rezerwacja pamięci
            demands.resize(dimension + 1);
        }
        else if (token == Cst::CAPACITY) {
            string temp;
            file >> temp;
            if (temp == Cst::COLON) file >> capacity;
            else capacity = stoi(temp);
        }
        else if (token == Cst::PERMUTATION) {
             string temp;
             file >> temp; // Pomiń dwukropek jeśli jest
             
             // Wczytaj permutację (kolejność klientów)
             // Zakładamy, że jest dimension-1 klientów w permutacji
             for (int i = 0; i < dimension - 1; ++i) {
                 int id;
                 file >> id;
                 permutation.push_back(id);
             }
        }
        else if (token == Cst::NODE_COORD_SECTION) {
            for (int i = 1; i <= dimension; ++i) {
                int id;
                double x, y;
                file >> id >> x >> y;
                coords[id] = make_pair(x, y);
            }
        }
        else if (token == Cst::DEMAND_SECTION) {
            for (int i = 1; i <= dimension; ++i) {
                int id, demand;
                file >> id >> demand;
                demands[id] = demand;
                totalDemand += demand;
            }
        }
        else if (token == Cst::DEPOT_SECTION) {
            // Sekcja DEPOT zwykle kończy się -1, pomijamy ją
            int id;
            while(file >> id && id != -1);
        }
    }

    file.close();

    // Walidacja czy wczytano poprawnie
    if (dimension == 0 || capacity == 0 || coords.empty()) {
        return false;
    }

    // Oblicz minimalną liczbę ciężarówek potrzebną do przewiezienia towaru
    // (TotalDemand / Capacity) zaokrąglone w górę
    if (capacity > 0) {
        numOfGroups = (totalDemand + capacity - 1) / capacity;
    } else {
        numOfGroups = 1; // Zabezpieczenie
    }

    return true;
}

// Funkcja oceny (Fitness Function)
double MyEvaluator::calculateFitness(const vector<int> &genotyp) const {
    // Zabezpieczenie przed pustym genotypem
    if (genotyp.empty()) return Cst::ERROR_FITNESS;

    // 1. Podział klientów na trasy (ciężarówki)
    // Tworzymy wektor wektorów. Indeks to numer ciężarówki.
    vector<vector<int>> routes(numOfGroups);

    // Iterujemy po PERMUTACJI (ważne! kolejność jest narzucona przez plik)
    for (int customerID : permutation) {
        // Klient ID np. 2 ma indeks 0 w genotypie
        int genotypeIndex = customerID - 2;

        // Sprawdzamy czy indeks jest poprawny
        if (genotypeIndex >= 0 && genotypeIndex < (int)genotyp.size()) {
            int truckID = genotyp[genotypeIndex];
            
            // Przypisujemy klienta do odpowiedniej ciężarówki
            if (truckID >= 0 && truckID < numOfGroups) {
                routes[truckID].push_back(customerID);
            }
        }
    }

    double totalCost = 0.0;

    // 2. Obliczanie kosztu dla każdej ciężarówki
    for (const auto &route : routes) {
        if (route.empty()) continue;

        double routeDist = 0.0;
        int currentLoad = 0;
        int lastLocationID = Cst::DEPOT_ID; // Start z bazy (ID 1)

        // Jedziemy od klienta do klienta w danej trasie
        for (int customerID : route) {
            // Dodajemy dystans
            routeDist += getDistance(lastLocationID, customerID);
            
            // Dodajemy ładunek
            currentLoad += demands[customerID];
            
            // Przesuwamy się
            lastLocationID = customerID;
        }

        // Powrót do bazy
        routeDist += getDistance(lastLocationID, Cst::DEPOT_ID);

        // Dodajemy koszt trasy do całości
        totalCost += routeDist;

        // 3. Sprawdzanie kar (Constraints)
        // Jeśli ciężarówka jest przeładowana, dodajemy ogromną karę
        if (currentLoad > capacity) {
            double overload = currentLoad - capacity;
            totalCost += (overload * Cst::PENALTY_FACTOR);
        }
    }

    return totalCost;
}