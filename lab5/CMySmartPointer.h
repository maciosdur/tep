#pragma once
#include "CRefCounter.h"
#include <iostream>

template <typename T>
class CMySmartPointer
{
public:
    CMySmartPointer(T* pcPointer)
    {
        pc_pointer = pcPointer;
        pc_counter = new CRefCounter();
        pc_counter->iAdd();
    }

    CMySmartPointer(const CMySmartPointer<T>& cOther)
    {
        pc_pointer = cOther.pc_pointer;
        pc_counter = cOther.pc_counter;
        pc_counter->iAdd();
    }

    CMySmartPointer<T>& operator=(const CMySmartPointer<T>& cOther)
    {
        if (this == &cOther) return *this;


        if (pc_counter->iDec() == 0)
        {
            delete pc_pointer;
            delete pc_counter;
        }

        pc_pointer = cOther.pc_pointer;
        pc_counter = cOther.pc_counter;

        pc_counter->iAdd();

        return *this;
    }

    ~CMySmartPointer()
    {
        if (pc_counter->iDec() == 0)
        {
            delete pc_pointer;
            delete pc_counter;
        }
    }

    T& operator*()
    {
        return *pc_pointer;
    }

    T* operator->()
    {
        return pc_pointer;
    }

    int iGetRefCount() const { 
    return pc_counter->iGet(); 
    }

    CMySmartPointer(CMySmartPointer<T>&& cOther) {
        pc_pointer = cOther.pc_pointer;
        pc_counter = cOther.pc_counter;

        
        cOther.pc_pointer = nullptr;
        cOther.pc_counter = nullptr;

        std::cout << "SMART_PTR_MOVE_CONSTRUCTOR" << std::endl;
    }

    CMySmartPointer<T>& operator=(CMySmartPointer<T>&& cOther) {
        if (this == &cOther) return *this;


        if (pc_counter != nullptr && pc_counter->iDec() == 0) {
            delete pc_pointer;
            delete pc_counter;
        }


        pc_pointer = cOther.pc_pointer;
        pc_counter = cOther.pc_counter;

        cOther.pc_pointer = nullptr;
        cOther.pc_counter = nullptr;

        std::cout << "SMART_PTR_MOVE_ASSIGNMENT" << std::endl;
        return *this;
    }
    


private:
    T* pc_pointer;
    CRefCounter* pc_counter;
};
