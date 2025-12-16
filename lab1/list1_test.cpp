#include <iostream>
using namespace std;

void v_proc_test() {
    int *pi_var;
    pi_var = new int;
    *pi_var=2; 
    cout<<pi_var<<endl;
    cout<<*pi_var<<endl;
    delete pi_var; 
    cout<<pi_var<<endl;
    cout<<*pi_var<<endl;

    double *pd_table;
    pd_table = new double[4];
    pd_table[2] = 9;
    cout<<pd_table<<endl;
    cout<<pd_table[2]<<endl;
    pd_table[0] = 11;
    delete pd_table;

    int i_value = 58;
    int *pi_val;
    char *pc_val;
    void *pv_val;
    pi_val = &i_value;
    pc_val = (char *) &i_value;
    pv_val = (void *) &i_value;
    cout<<*pi_val<<endl;
    cout<<*pc_val<<endl;
    cout<<(int)*pc_val<<endl;
    cout<<*( (int *) pv_val )<<endl;
    int i_value2 = 78;
    int *pi_11, **pi_12, ***pi_13;
    pi_11 = &i_value2;
    pi_12 = &pi_11;
    pi_13 = &pi_12;
    cout<<***pi_13<<endl;

}



int main() {
    v_proc_test();
    return 0;
}