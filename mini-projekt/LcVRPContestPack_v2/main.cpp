#include <iostream>
#include <ctime>
#include <vector>
#include "CGeneticAlgorithm.h"
#include "MyEvaluator.h"
#include "Constants.h"

using namespace std;

int main() {
    // 1. Ustalenie ścieżki do pliku
    // Upewnij się, że ten plik faktycznie istnieje w folderze data/lcvrp/Vrp-Set-A/
    string sciezkaDoPliku = "data/lcvrp/Vrp-Set-A/A-n32-k5.lcvrp";

    // 2. Tworzenie i ładowanie ewaluatora (Sędziego)
    MyEvaluator evaluator;
    cout << "Proba wczytania pliku: " << sciezkaDoPliku << "..." << endl;

    if (!evaluator.loadInstance(sciezkaDoPliku)) {
        cerr << "BLAD KRYTYCZNY: Nie udalo sie wczytac pliku wejsciowego!" << endl;
        cerr << "Sprawdz czy sciezka jest poprawna i czy folder 'data' jest w tym samym miejscu co plik .exe" << endl;
        return -1;
    }

    // Wyświetlenie informacji o wczytanym problemie
    cout << "Sukces! Wczytano dane:" << endl;
    cout << " -> Liczba klientow: " << evaluator.getNumOfCustomers() << endl;
    cout << " -> Liczba grup (ciezarowek): " << evaluator.getNumOfGroups() << endl;

    // 3. Konfiguracja Algorytmu Genetycznego
    // Pobieramy parametry z pliku Constants.h
    cout << "\nInicjalizacja Algorytmu Genetycznego..." << endl;
    cout << "Populacja: " << Cst::POP_SIZE 
         << ", Krzyzowanie: " << Cst::CROSS_PROB 
         << ", Mutacja: " << Cst::MUT_PROB << endl;

    CGeneticAlgorithm myAlgo(Cst::POP_SIZE, Cst::CROSS_PROB, Cst::MUT_PROB, evaluator);

    // 4. Tworzenie pierwszej populacji
    myAlgo.initialize();
    cout << "Startowy najlepszy wynik (losowy): " << myAlgo.getBestFitness() << endl;

    // 5. Pętla główna (uruchamiamy przez określony czas)
    time_t startCzasu = time(NULL);
    long numerIteracji = 0;
    
    cout << "\nRozpoczynam optymalizacje (czas max: " << Cst::MAX_TIME_SECONDS << "s)..." << endl;

    while (difftime(time(NULL), startCzasu) < Cst::MAX_TIME_SECONDS) {
        // Wykonaj jeden krok ewolucji
        myAlgo.runIteration();
        numerIteracji++;

        // Co pewien czas wypisz postęp, żebyś wiedział, że program nie zawisł
        if (numerIteracji % Cst::DEBUG_ITERATION_STEP == 0) {
            cout << "Iteracja [" << numerIteracji << "] -> Najlepszy koszt: " << myAlgo.getBestFitness() << endl;
        }
    }

    // 6. Podsumowanie wyników
    cout << "\n------------------------------------------------" << endl;
    cout << "KONIEC OBLICZEN" << endl;
    cout << "Czas operacji uplynal." << endl;
    cout << "Wykonano iteracji: " << numerIteracji << endl;
    cout << "OSTATECZNY WYNIK (Koszt trasy): " << myAlgo.getBestFitness() << endl;
    cout << "------------------------------------------------" << endl;

    return 0;
}