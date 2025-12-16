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
        b_negative = false;
    }
    CNumber(const CNumber &other) {
    i_lenght = other.i_lenght;
    pi_number = new int[i_lenght];
    for (int i = 0; i < i_lenght; i++) {
        pi_number[i] = other.pi_number[i];
    }
    b_negative = other.b_negative;
    }
    ~CNumber(){
        delete[] pi_number;
    }
    void vSet(int NewVal){
        if (NewVal < 0) {
            b_negative = true;
            NewVal = -NewVal;
        } else {
            b_negative = false;
        }

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

    CNumber operator+(const CNumber &other) const;
    CNumber operator-(const CNumber &other) const;
    CNumber operator*(const CNumber &other) const;
    CNumber operator/(const CNumber &other) const;
    
    string sToStr(){
        string s="";
        if(b_negative){
            s+="-";
        }
        for(int i=i_lenght-1;i>=0;i--){
            s+=char(pi_number[i] + '0');
        }
        return s;
    }
    string fstToStr(){
        string s="";
        s=char(pi_number[0] + '0');
        return s;
    }

private:
    int *pi_number;
    int i_lenght;
    bool b_negative;
};

void CNumber::operator=(const CNumber &pcOther)
{
    delete[] pi_number;
        i_lenght = pcOther.i_lenght;
        pi_number = new int[i_lenght];
        for (int i = 0; i < i_lenght; i++) {
            pi_number[i] = pcOther.pi_number[i]; 
        }
}

CNumber CNumber::operator+(const CNumber &other) const {
    CNumber result;

    // ten sam znak
    if (b_negative == other.b_negative) {
        int carry = 0;
        for (int i = 0; i < i_lenght; i++) {
            int sum = pi_number[i] + other.pi_number[i] + carry;
            result.pi_number[i] = sum % 10;
            carry = sum / 10;
        }
        result.b_negative = b_negative;
    }
    // różne znaki
    else {
        // odej bezw wart
        bool thisBigger = false;
        for (int i = i_lenght - 1; i >= 0; i--) {
            if (pi_number[i] > other.pi_number[i]) { thisBigger = true; break; }
            if (pi_number[i] < other.pi_number[i]) { thisBigger = false; break; }
        }

        const int *larger = thisBigger ? pi_number : other.pi_number;
        const int *smaller = thisBigger ? other.pi_number : pi_number;

        int borrow = 0;
        for (int i = 0; i < i_lenght; i++) {
            int diff = larger[i] - smaller[i] - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else borrow = 0;
            result.pi_number[i] = diff;
        }

        // znak wiekszej (bezw) liczby
        result.b_negative = thisBigger ? b_negative : other.b_negative;
    }

    return result;
}


CNumber CNumber::operator-(const CNumber &other) const {
    CNumber tmp(other);
    tmp.b_negative = !other.b_negative;
    return (*this + tmp);
}

CNumber CNumber::operator*(const CNumber &other) const {
    CNumber result;

    for (int i = 0; i < i_lenght; i++) {
        int carry = 0;
        for (int j = 0; j + i < i_lenght; j++) {
            int prod = pi_number[i] * other.pi_number[j] + result.pi_number[i + j] + carry;
            result.pi_number[i + j] = prod % 10;
            carry = prod / 10;
        }
    }

    result.b_negative = (b_negative != other.b_negative);

    return result;
}

CNumber CNumber::operator/(const CNumber &other) const {
    CNumber zero;
    zero.vSet(0);
    CNumber result;
    result.vSet(0);

    bool isZero = true;
    for (int i = 0; i < other.i_lenght; i++) {
        if (other.pi_number[i] != 0) { 
            isZero = false; 
            break; 
        }
    }
    if (isZero) {
        cout << "Blad" << endl;
        return zero;
    }

    CNumber dividend = *this;
    CNumber divisor = other;
    dividend.b_negative = false;
    divisor.b_negative = false;

    while (true) {
        bool biggerOrEqual = false;
        for (int i = i_lenght - 1; i >= 0; i--) {
            if (dividend.pi_number[i] > divisor.pi_number[i]) { 
                biggerOrEqual = true; 
                break; 
            }
            if (dividend.pi_number[i] < divisor.pi_number[i]) { 
                biggerOrEqual = false; 
                break; 
            }
        }

        if (!biggerOrEqual && dividend.sToStr() != divisor.sToStr()) break;

        dividend = dividend - divisor;


        int carry = 1;
        for (int i = 0; i < i_lenght; i++) {
            int sum = result.pi_number[i] + carry;
            result.pi_number[i] = sum % 10;
            carry = sum / 10;
            if (carry == 0) break;
        }
    }

    result.b_negative = (b_negative != other.b_negative);

    return result;
}



int main() {
    // //zad1
    // CNumber c_num;
    // c_num.vSet(12345);

    // cout << c_num.sToStr() << endl;

    // c_num = 67890;
    // cout << c_num.sToStr() << endl;

    //zad4
    CNumber c_num_0, c_num_1;
    c_num_0 = 3683213;
    c_num_1 = 1567;
    c_num_0 = c_num_1;
    cout << c_num_0.sToStr() << endl;
    cout << c_num_0.fstToStr() << endl;

    //zad5
    CNumber c_num_2, c_num_3, c_num_4, c_num_5, c_num_6, c_num_7, c_num_8;
    c_num_2 = -9999;
    c_num_3 = 1;
    c_num_4 = -4;
    c_num_5 = 3;
    c_num_6 = 12;
    c_num_7 = 999999999;
    c_num_8 =0;

    cout << (c_num_2 + c_num_3).sToStr() << endl;
    cout << (c_num_3 - c_num_4).sToStr() << endl;
    cout << (c_num_3 + c_num_5).sToStr() << endl;
    cout << (c_num_2 - c_num_4).sToStr() << endl;
    cout << (c_num_4 - c_num_4).sToStr() << endl;
    cout << (c_num_5 + c_num_6+ c_num_3+c_num_3).sToStr() << endl;
    cout << (c_num_7 + c_num_7 +c_num_7 + c_num_7 +c_num_7 + c_num_7 +c_num_7 + c_num_7 +c_num_7 + c_num_7 + c_num_6 ).sToStr() << endl;
    cout << (c_num_4 * c_num_6).sToStr() << endl;
    cout<< (c_num_6 * c_num_6 * c_num_4).sToStr() << endl;
    cout<< (c_num_2 * c_num_4).sToStr() << endl;
    cout<< (c_num_6 / c_num_6).sToStr() << endl;
    cout<< (c_num_2 / c_num_3).sToStr() << endl;
    cout<< (c_num_7 / c_num_8).sToStr() << endl;
    cout<< (c_num_3 / c_num_5).sToStr() << endl;
    cout<< (c_num_3 / c_num_4).sToStr() << endl;
    cout<< (c_num_4 / c_num_3).sToStr() << endl;

    

    return 0;
}
