#include <iostream>
using namespace std;

void v_alloc_table_fill_34(int iSize)
{
    if (iSize <= 0)
    {
        cout << "bledny rozmiar tablicy" << endl;
        return;
    }

    const int FILL_VALUE = 34;

    int *pi_table = new int[iSize];

    for (int i = 0; i < iSize; i++)
    {
        pi_table[i] = FILL_VALUE;
    }

    cout << "Zawartosc tablicy: ";
    for (int i = 0; i < iSize; i++)
    {
        cout << pi_table[i] << " ";
    }
    cout << endl;

    delete[] pi_table;
}






int main() {
    int iSize =-1 ;

    v_alloc_table_fill_34(iSize);

    return 0;
}