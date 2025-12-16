// #include <iostream>
// #include <string>
// using namespace std;

// const string DEFAULT_NAME = "default";
// const int DEFAULT_SIZE = 5;

// class CTable
// {
// private:
//     string s_name;
//     int* pi_table;
//     int i_tab_len;

// public:
//     // ---------- Konstruktor bezparametrowy ----------
//     CTable() // bezparametrowy
//     {
//         s_name = DEFAULT_NAME;
//         i_tab_len = DEFAULT_SIZE;
//         pi_table = new int[i_tab_len];
//         for (int i = 0; i < i_tab_len; i++) pi_table[i] = 0;
//         cout << "bezp: '" << s_name << "'" << endl;
//     }

//     CTable(string sName, int iTableLen) // parametryczny
//     {
//         s_name = sName;
//         i_tab_len = iTableLen > 0 ? iTableLen : DEFAULT_SIZE;
//         pi_table = new int[i_tab_len];
//         for (int i = 0; i < i_tab_len; i++) pi_table[i] = 0;
//         cout << "parametr: '" << s_name << "'" << endl;
//     }


//     // ---------- Konstruktor kopiujący ----------
//     CTable(CTable &pcOther)
//     {
//         s_name = pcOther.s_name + "_copy";
//         i_tab_len = pcOther.i_tab_len;
//         pi_table = new int[i_tab_len];
//         for (int i = 0; i < i_tab_len; i++)
//             pi_table[i] = pcOther.pi_table[i];
//         cout << "kopiuj: '" << s_name << "'" << endl;
//     }

//     // ---------- Destruktor ----------
//     ~CTable()
//     {
//         delete[] pi_table;
//         cout << "usuwam: '" << s_name << "'" << endl;
//     }
//     // Pobranie wartości elementu tablicy
//     int iGetValueAt(int idx) const
//     {
//         if (idx >= 0 && idx < i_tab_len)
//             return pi_table[idx];
//         return 0; // lub jakiś domyślny/error
//     }

//     // Ustawienie wartości elementu tablicy
//     void vSetValueAt(int idx, int val)
//     {
//         if (idx >= 0 && idx < i_tab_len)
//             pi_table[idx] = val;
//     }
//     // ---------- Metody ----------
//     void vSetName(string sName)
//     {
//         s_name = sName;
//     }

//     bool bSetNewSize(int iTableLen)
//     {
//         if (iTableLen <= 0) return false;

//         int* new_table = new int[iTableLen];
//         int min_len = i_tab_len < iTableLen ? i_tab_len : iTableLen;
//         for (int i = 0; i < min_len; i++)
//             new_table[i] = pi_table[i];

//         delete[] pi_table;
//         pi_table = new_table;
//         i_tab_len = iTableLen;

//         return true;
//     }

//     CTable* pcClone()
//     {
//         return new CTable(*this); // wykorzystanie konstruktora kopiującego
//     }
//     // Modyfikacja poprzez wskaźnik
//     // Metoda do testów
//     void vPrint()
//     {
//         cout << "Obiekt '" << s_name << "', rozmiar = " << i_tab_len << ": [";
//         for (int i = 0; i < i_tab_len; i++)
//         {
//             cout << iGetValueAt(i);
//             if (i < i_tab_len - 1)
//                 cout << ", ";
//         }
//         cout << "]" << endl;
//     }


   
//     CTable extractNegative()
//     {
//         // Liczenie ujemnych elementów w tablicy źródłowej
//         int negCount = 0;
//         for (int i = 0; i < i_tab_len; i++)
//             if (iGetValueAt(i) < 0) negCount++;

//         // Tworzenie obiektu wynikowego z minimalnym rozmiarem
//         CTable result("negatives", negCount);

//         int newSourceSize = i_tab_len - negCount;
//         int* newSource = new int[newSourceSize]; // tymczasowa tablica źródła
//         int idxNeg = 0;  // indeks w tablicy wynikowej
//         int idxSrc = 0;  // indeks w nowej tablicy źródła

//         for (int i = 0; i < i_tab_len; i++)
//         {
//             int val = iGetValueAt(i);
//             if (val < 0)
//             {
//                 result.vSetValueAt(idxNeg++, val); // przenosimy do wyniku
//             }
//             else
//             {
//                 newSource[idxSrc++] = val;        // pozostawiamy w źródle
//             }
//         }

//         // Zamiana starej tablicy źródłowej na nową
//         delete[] pi_table;
//         pi_table = newSource;
//         i_tab_len = newSourceSize;

//         return result;
//     }


// };
// // Modyfikacja poprzez wskaźnik
// void v_mod_tab(CTable *pcTab, int iNewSize)
// {
//     if (pcTab)
//         pcTab->bSetNewSize(iNewSize);
// }

// // Modyfikacja poprzez kopiowanie obiektu
// void v_mod_tab(CTable cTab, int iNewSize)
// {
//     cTab.bSetNewSize(iNewSize); // zmiana dotyczy tylko kopii
// }
// int main()
// {
//     cout << "--- Statyczna alokacja ---" << endl;
//     CTable tab1;                   // konstruktor bezparametrowy
//     CTable tab2("moja_tab", 10);   // konstruktor parametryczny
//     tab1.vPrint();
//     tab2.vPrint();

//     cout << "--- Kopiowanie ---" << endl;
//     CTable tab3(tab2);             // konstruktor kopiujący
//     tab3.vPrint();

//     cout << "--- Dynamiczna alokacja ---" << endl;
//     CTable *pTab = new CTable("dyn_tab", 7);
//     pTab->vPrint();
//     delete pTab;                   // wywołanie destruktora

//     cout << "--- pcClone ---" << endl;
//     CTable *pClone = tab1.pcClone();
//     pClone->vPrint();
//     delete pClone;

//     cout << "--- Test procedur ---" << endl;
//     tab1.vPrint();
//     v_mod_tab(&tab1, 12);          // zmienia oryginał
//     tab1.vPrint();
//     v_mod_tab(tab2, 20);           // działa na kopii
//     tab2.vPrint();                  // bez zmian

//     CTable tab("test", 6);
//     tab.vSetValueAt(0, -5);
//     tab.vSetValueAt(1, 3);
//     tab.vSetValueAt(2, -2);
//     tab.vSetValueAt(3, 7);
//     tab.vSetValueAt(4, -1);
//     tab.vSetValueAt(5, 10);
//     tab.vPrint();
//     CTable negTab = tab.extractNegative();
//     tab.vPrint();
//     negTab.vPrint();

//     return 0;
// }


// #include <iostream>
// #include <string>
// using namespace std;

// class Course; // wstępne zadeklarowanie klasy Course

// class Student {
// private:
//     int s_id;

// public:
//     Student() : s_id(0) {}
//     Student(int id) : s_id(id) {}

//     int getId() const { return s_id; }

//     // metoda zapisująca studenta na kurs
//     void enroll(Course &course);
    
//     ~Student(); // destruktor
// };

// class Course {
// private:
//     string c_name;
//     Student **students; // tablica wskaźników do Student
//     int i_table_len;
//     int student_count;

// public:
//     Course() : c_name(""), i_table_len(32), student_count(0) {
//         students = new Student*[i_table_len]();
//     }

//     Course(string name) : c_name(name), i_table_len(32), student_count(0) {
//         students = new Student*[i_table_len]();
//     }

//     string getName() const { return c_name; }

//     // metoda dodająca wskaźnik studenta do kursu
//     bool addStudent(Student *s) {
//         if (student_count >= i_table_len) {
//             cout << "Kurs " << c_name << " jest pełny!" << endl;
//             return false;
//         }
//         students[student_count++] = s;
//         return true;
//     }

//     // metoda usuwająca studenta (wykorzystywana w destruktorze Student)
//     void removeStudent(Student *s) {
//         for (int i = 0; i < student_count; i++) {
//             if (students[i] == s) {
//                 // przesuwamy pozostałych studentów w lewo
//                 for (int j = i; j < student_count - 1; j++) {
//                     students[j] = students[j + 1];
//                 }
//                 students[student_count - 1] = nullptr;
//                 student_count--;
//                 break;
//             }
//         }
//     }

//     void printStudents() {
//         cout << "Kurs " << c_name << " ma studentow: ";
//         for (int i = 0; i < student_count; i++) {
//             cout << students[i]->getId() << " ";
//         }
//         cout << endl;
//     }

//     ~Course() {
//         delete[] students;
//     }
// };

// // implementacja enroll
// void Student::enroll(Course &course) {
//     course.addStudent(this);
// }

// // destruktor Student
// Student::~Student() {
//     // potencjalnie należałoby usunąć studenta ze wszystkich kursów
//     // w tym przykładzie nie trzymamy listy kursów w studencie,
//     // więc zakładamy, że kursy same zarządzają swoimi wskaźnikami
// }

// int main() {
//     // Tworzenie kursu i studentów dynamicznie
//     Course *math = new Course("Matematyka");
//     Student *s1 = new Student(101);
//     Student *s2 = new Student(102);
//     Student *s3 = new Student(103);

//     s1->enroll(*math);
//     s2->enroll(*math);
//     s3->enroll(*math);

//     math->printStudents(); // powinno pokazać 101 102 103

//     // Zwolnienie pamięci
//     delete s2; // jeśli chcemy usuwać studenta z kursu, trzeba wywołać math->removeStudent(s2);
//     math->removeStudent(s2);

//     math->printStudents(); // powinno pokazać 101 103

//     delete s1;
//     delete s3;
//     delete math;

//     return 0;
// }





#include <iostream>
#include <string>
using namespace std;

class Course;

class Student {
private:
    int s_id;
public:
    Student() : s_id(0) {}
    Student(int id) : s_id(id) {}
    int getId() const { return s_id; }
    void enroll(Course &course);
    ~Student() {}
};

class Course {
private:
    string c_name;
    Student **students;
    int i_table_len;
    int student_count;
public:
    Course() : c_name(""), i_table_len(32), student_count(0) { students = new Student*[i_table_len](); }
    Course(string name) : c_name(name), i_table_len(32), student_count(0) { students = new Student*[i_table_len](); }
    bool addStudent(Student *s) {
        if (student_count >= i_table_len) return false;
        students[student_count++] = s;
        return true;
    }
    void removeStudent(Student *s) {
        for (int i = 0; i < student_count; i++) {
            if (students[i] == s) {
                for (int j = i; j < student_count - 1; j++) students[j] = students[j + 1];
                students[student_count - 1] = nullptr;
                student_count--;
                break;
            }
        }
    }
    void printStudents() {
        for (int i = 0; i < student_count; i++) cout << students[i]->getId() << " ";
        cout << endl;
    }
    ~Course() { delete[] students; }
};

void Student::enroll(Course &course) { course.addStudent(this); }

int main() {
    Course *math = new Course("Matematyka");
    Student *s1 = new Student(101);
    Student *s2 = new Student(102);
    Student *s3 = new Student(103);

    s1->enroll(*math);
    s2->enroll(*math);
    s3->enroll(*math);

    math->printStudents();

    delete s2;
    math->removeStudent(s2);

    math->printStudents();

    delete s1;
    delete s3;
    delete math;
}
