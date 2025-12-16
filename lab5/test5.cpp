#include "CMySmartPointer.h"
#include "CSellData.h"
#include <iostream>
#include "Tree.h" 
#include "CError.h"
#include "CResult.h"
#include "CResultSaver.h" 
#include <string>

int main() {
    // --- CZĘŚĆ 1: PODSTAWY ---
    std::cout << "=== TEST 1: Konstruktor i podstawowa obsluga ===\n";
    {
        CMySmartPointer<CSellData> smart(new CSellData());
        smart->vPrintData();
        std::cout << "Licznik: " << smart.iGetRefCount() << " (oczekiwane: 1)\n";
    } // Tutaj obiekt jest usuwany

    // --- CZĘŚĆ 2: KONSTRUKTOR KOPIUJĄCY ---
    std::cout << "\n=== TEST 2: Konstruktor kopiujacy i zasieg ===\n";
    CMySmartPointer<CSellData> smart1(new CSellData());
    std::cout << "smart1 stworzony. Licznik: " << smart1.iGetRefCount() << "\n";

    {
        std::cout << "Tworzenie smart2 i smart3 przez kopiowanie...\n";
        CMySmartPointer<CSellData> smart2 = smart1; 
        CMySmartPointer<CSellData> smart3 = smart1;

        std::cout << "Licznik smart1: " << smart1.iGetRefCount() << " (oczekiwane: 3)\n";
        std::cout << "Licznik smart2: " << smart2.iGetRefCount() << " (oczekiwane: 3)\n";
        std::cout << "Licznik smart3: " << smart3.iGetRefCount() << " (oczekiwane: 3)\n";
        
        std::cout << "Wyjscie z bloku - smart2 i smart3 zostana zniszczone.\n";
    }

    std::cout << "Po bloku. Licznik smart1: " << smart1.iGetRefCount() << " (oczekiwane: 1)\n";

    // --- CZĘŚĆ 3: OPERATOR PRZYPISANIA (Zadanie 2) ---
    std::cout << "\n=== TEST 3: Operator przypisania ===\n";
    CMySmartPointer<CSellData> smart_A(new CSellData());
    CMySmartPointer<CSellData> smart_C = smart_A;
    CMySmartPointer<CSellData> smart_B(new CSellData());

    std::cout << "Przed przypisaniem:\n";
    std::cout << "smart_A ref: " << smart_A.iGetRefCount() << "\n";
    std::cout << "smart_B ref: " << smart_B.iGetRefCount() << "\n";

    std::cout << "Wykonuje: smart_B = smart_A\n";
    smart_B = smart_A; // Obiekt pierwotnie w smart_B powinien zostac usuniety

    std::cout << "Po przypisaniu:\n";
    std::cout << "smart_A ref: " << smart_A.iGetRefCount() << " (oczekiwane: 3)\n";
    std::cout << "smart_B ref: " << smart_B.iGetRefCount() << " (oczekiwane: 3)\n";

    std::cout << "\n=== TEST 4: Autoprzypisanie ===\n";
    smart_A = smart_A; // Test zabezpieczenia 'if (this == &cOther)'
    std::cout << "Po autoprzypisaniu smart_A ref: " << smart_A.iGetRefCount() << " (nadal: 3)\n";

    std::cout << "\n=== KONIEC PROGRAMU (czyszczenie reszty) ===\n";

    std::cout << "\n=== TEST 4: wskaźnik na pamięć zaalokowaną statycznie ===\n";

    CMySmartPointer<int> smart_global(NULL); // wskaźnik, który żyje długo
    {
        int x = 10; 
        CMySmartPointer<int> smart_local(&x);
        smart_global = smart_local; // smart_global teraz też patrzy na 'x'
        // Licznik wynosi 2
    }
    std::cout << *smart_global;



    Tree tree1, tree3;
    
    tree1.buildFromString("+ 1 2");
    tree3.buildFromString("+ 3 4");
    std::cout<<"tree1: "<<tree1.printPrefix() << std::endl;
    std::cout<<"tree3: "<<tree3.printPrefix() << std::endl;
    std::cout << "konstr przenoszący:" << std::endl;
    Tree tree2 = std::move(tree3);
    std::cout<<"tree1: "<<tree1.printPrefix() << std::endl;
    std::cout<<"tree2: "<<tree2.printPrefix() << std::endl;
    std::cout<<"tree3: "<<tree3.printPrefix() << std::endl;

    std::cout << "Przed przeniesieniem:" << std::endl;
    std::cout<<"tree1: "<<tree1.printPrefix() << std::endl;
    std::cout<<"tree2: "<<tree2.printPrefix() << std::endl;

    tree1 = std::move(tree2); // Tu powinien wypisac "MOVE_ASSIGNMENT"
    std::cout << "Po przeniesieniu." << std::endl;
    std::cout<<"tree1: "<<tree1.printPrefix() << std::endl;
    std::cout<<"tree2: "<<tree2.printPrefix() << std::endl;


    Tree t1, t2;
    t1.buildFromString("+ a b");
    t2.buildFromString("+ c d");

    std::cout << "\n--- TEST 1: Kopiowanie (bez move) ---" << std::endl;
    Tree t3(t1); // Tu zobaczysz "COPY_CONSTRUCTOR"

    std::cout << "\n--- TEST 2: Przenoszenie (std::move) ---" << std::endl;
    //Tree t4(std::move(t1)); // Tu zobaczysz "MOVE_CONSTRUCTOR"
    Tree t4(t1);

    std::cout << "\n--- TEST 3: Operator + (zwracanie przez wartosc) ---" << std::endl;
    // result zostanie przeniesiony (MOVE) do t5, a nie skopiowany
    Tree t5 = t4 + t2;

    std::cout << "\n--- TEST: Łańcuch dodawania (t1 + t2 + t3 + t4) ---" << std::endl;
    Tree t_res;
    // Wyrażenie złożone
    t_res = t1 + t2 + t3 + t4;
    //zad5 wynik po zakomentowaniu konstr przenoszacego i operatora przypisania przenoszacego
        // --- TEST 1: Kopiowanie (bez move) ---
        // COPY_CONSTRUCTOR
        // --- TEST 2: Przenoszenie (std::move) ---
        // COPY_CONSTRUCTOR
        // --- TEST 3: Operator + (zwracanie przez wartosc) ---
        // COPY_CONSTRUCTOR COPY_CONSTRUCTOR
        
        // --- TEST: ┼üa┼äcuch dodawania (t1 + t2 + t3 + t4) ---
        // COPY_CONSTRUCTOR COPY_CONSTRUCTOR COPY_CONSTRUCTOR COPY_CONSTRUCTOR COPY_CONSTRUCTOR COPY_CONSTRUCTOR COPY_ASSIGNMENT
    //zad5 wynik z odkomentowaniem konstr przenoszacego i operatora przypisania przenoszacego
        // --- TEST 1: Kopiowanie (bez move) ---
        // COPY_CONSTRUCTOR
        // --- TEST 2: Przenoszenie (std::move) ---
        // COPY_CONSTRUCTOR
        // --- TEST 3: Operator + (zwracanie przez wartosc) ---
        // COPY_CONSTRUCTOR MOVE_CONSTRUCTOR

        // --- TEST: ┼üa┼äcuch dodawania (t1 + t2 + t3 + t4) ---
        // COPY_CONSTRUCTOR MOVE_CONSTRUCTOR
        // COPY_CONSTRUCTOR MOVE_CONSTRUCTOR
        // COPY_CONSTRUCTOR MOVE_CONSTRUCTOR
        // COPY_ASSIGNMENT

    return 0;
}
//g++ test5.cpp App.cpp Tree.cpp Node.cpp NodeCreator.cpp Error.cpp -o Tester5