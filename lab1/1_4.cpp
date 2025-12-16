#include <iostream>
#include <string>
using namespace std;

class CTable {
private:
    string s_name;
    int *pi_table;
    int i_table_len;

public:
    CTable() {
        s_name = "default";
        i_table_len = 10;
        pi_table = new int[i_table_len];
        cout << "bezp: '" << s_name << "'" << endl;
    }

    CTable(string sName, int iTableLen) {
        s_name = sName;
        i_table_len = iTableLen;
        pi_table = new int[i_table_len];
        cout << "parametr: '" << s_name << "'" << endl;
    }

    CTable(CTable &pcOther) {
        s_name = pcOther.s_name + "_copy";
        i_table_len = pcOther.i_table_len;

        pi_table = new int[i_table_len];
        for (int i = 0; i < i_table_len; i++)
            pi_table[i] = pcOther.pi_table[i];

        cout << "kopiuj: '" << s_name << "'" << endl;
    }

    ~CTable() {
        delete[] pi_table;
        cout << "usuwam: '" << s_name << "'" << endl;
    }

    void vSetName(string sName) {
        s_name = sName;
    }

    bool bSetNewSize(int iTableLen) {
        if (iTableLen <= 0) return false;

        int *new_table = new int[iTableLen];
        int limit = (iTableLen < i_table_len) ? iTableLen : i_table_len;

        for (int i = 0; i < limit; i++)
            new_table[i] = pi_table[i];

        delete[] pi_table;
        pi_table = new_table;
        i_table_len = iTableLen;

        return true;
    }

    CTable* pcClone() {
        return new CTable(*this);
    }

    void vPrint() {
        cout << s_name << " [";
        for (int i = 0; i < i_table_len; i++) {
            cout << pi_table[i];
            if (i < i_table_len - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

};

void v_mod_tab(CTable *pcTab, int iNewSize) {
    pcTab->bSetNewSize(iNewSize);
}

void v_mod_tab(CTable cTab, int iNewSize) {
    cTab.bSetNewSize(iNewSize);
}

int main() {
    cout << "1" << endl;
    CTable c_tab_0;
    CTable c_tab_1("tablica", 5);

    cout << "2" << endl;
    CTable *pc_new_tab = c_tab_1.pcClone();

    cout << "3" << endl;
    v_mod_tab(&c_tab_1, 10);

    cout << "4" << endl;
    v_mod_tab(c_tab_1, 7);

    cout << "5" << endl;
    delete pc_new_tab;

    cout << "6" << endl;

    CTable tab("test", 5);

    
    v_mod_tab(&tab, 10); 
    tab.vPrint();       
    cout << "7" << endl;
    
    v_mod_tab(tab, 20);  
    tab.vPrint();        
     cout << "7" << endl;

    CTable tab2("test2", 6);
    tab2.vPrint();

    return 0;
}
