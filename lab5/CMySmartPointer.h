#pragma once
#include "CRefCounter.h"

template <typename T>
class CMySmartPointer
{
public:
    // konstruktor z surowym wskaźnikiem
    CMySmartPointer(T* pcPointer)
    {
        pc_pointer = pcPointer;
        pc_counter = new CRefCounter();
        pc_counter->iAdd();
    }

    // konstruktor kopiujący
    CMySmartPointer(const CMySmartPointer<T>& cOther)
    {
        pc_pointer = cOther.pc_pointer;
        pc_counter = cOther.pc_counter;
        pc_counter->iAdd();
    }

    CMySmartPointer<T>& operator=(const CMySmartPointer<T>& cOther)
    {
        if (this == &cOther) return *this;

        // 2. Musimy "odpiąć się" od starego wskaźnika,
        // bo zaraz podepniemy się pod nowy.
        // Robimy to samo co w destruktorze.
        if (pc_counter->iDec() == 0)
        {
            delete pc_pointer;
            delete pc_counter;
        }

        // 3. Przepisujemy wskaźniki z drugiego obiektu
        pc_pointer = cOther.pc_pointer;
        pc_counter = cOther.pc_counter;

        // 4. Zwiększamy licznik dla nowego obiektu
        pc_counter->iAdd();

        return *this;
    }

    // destruktor
    ~CMySmartPointer()
    {
        if (pc_counter->iDec() == 0)
        {
            delete pc_pointer;
            delete pc_counter;
        }
    }

    // dereferencja
    T& operator*()
    {
        return *pc_pointer;
    }

    // dostęp do pól/metod
    T* operator->()
    {
        return pc_pointer;
    }

    int iGetRefCount() const { 
    return pc_counter->iGet(); 
}

private:
    T* pc_pointer;
    CRefCounter* pc_counter;
};
