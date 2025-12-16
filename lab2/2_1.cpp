#include <iostream>
#include <string>
using namespace std;

#define NUMBER_DEFAULT_LENGHT 10
class CNumber {
public:
    CNumber(){
        i_lenght = NUMBER_DEFAULT_LENGHT;
        pi_number = new int[i_lenght];
        for (int i = 0; i < i_lenght; i++) {
            pi_number[i] = 0;
        }
    }
    ~CNumber(){
        delete pi_number;
    }
    void vSet(int NewVal){
        for (int i = 0; i < i_lenght; i++) {
            pi_number[i] = 0;
        }
        int i=0;
        int val = NewVal;

        while (val > 0 && i < i_lenght) {
            pi_number[i] = val % 10;
            val /= 10;
            i++;
        }
    }
    CNumber& operator=(const int iValue){
        vSet(iValue);
        return *this;
    }
    void operator=(const CNumber &pcOther);
    
    string sToStr(){
        string s="";
        for(int i=i_lenght-1;i>=0;i--){
            s+=char(pi_number[i] + '0');
        }
        return s;
    }
private:
    int *pi_number;
    int i_lenght;
};

void CNumber::operator=(const CNumber &pcOther)
{
    pi_number = pcOther.pi_number;
    i_lenght = pcOther.i_lenght;
}


int main() {
    // //zad1
    CNumber c_num;
    c_num.vSet(12345);

    cout << c_num.sToStr() << endl;

    c_num = 67890;
    cout << c_num.sToStr() << endl;

    //zad2
    CNumber c_num_0, c_num_1;
    c_num_0 = 368;
    c_num_1 = 1567;
    c_num_0 = c_num_1;
    cout << c_num_0.sToStr() << endl;
    cout << c_num_1.sToStr() << endl;
    //[Running] cd "c:\Users\macie\OneDrive\film_maciek\Documents\sem5\TEP\lab2\" && g++ 2_1.cpp -o 2_1 && "c:\Users\macie\OneDrive\film_maciek\Documents\sem5\TEP\lab2\"2_1
    // 0000012345
    // 0000067890

    // [Done] exited with code=3221226356 in 1.759 seconds

    //zad3 bez destruktora
    //     [Running] cd "c:\Users\macie\OneDrive\film_maciek\Documents\sem5\TEP\lab2\" && g++ 2_1.cpp -o 2_1 && "c:\Users\macie\OneDrive\film_maciek\Documents\sem5\TEP\lab2\"2_1
    // 0000012345
    // 0000067890

    // [Done] exited with code=0 in 1.257 seconds

    

    return 0;
}
