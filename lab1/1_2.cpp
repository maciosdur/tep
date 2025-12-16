#include <iostream>
using namespace std;

bool b_alloc_table_2_dim(int ***piTable, int iSizeX, int iSizeY)
{
    if (iSizeX <= 0 || iSizeY <= 0)
        return false;

    *piTable = new int *[iSizeX]; 

    for (int i = 0; i < iSizeX; i++)
    {
        (*piTable)[i] = new int[iSizeY]; 
        for (int j = 0; j < iSizeY; j++)
        {
            (*piTable)[i][j] = 0; 
        }
    }

    return true;
}

bool b_dealloc_table_2_dim(int **piTable, int iSizeX)
{
    if (piTable == nullptr || iSizeX <= 0)
        return false;

    for (int i = 0; i < iSizeX; i++)
        delete[] piTable[i];

    delete[] piTable;
    return true;
}

int main()
{
    int **pi_table;

    if (b_alloc_table_2_dim(&pi_table, 5, 3))
    {
        cout <<1<< endl;

        pi_table[2][1] = 42;
        cout << pi_table[2][1] << endl;

        b_dealloc_table_2_dim(pi_table, 5);
    }
    else
    {
        cout << -1 << endl;
    }

    return 0;
}
