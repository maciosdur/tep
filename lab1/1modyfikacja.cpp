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
    Course *tep = new Course("tep");
    Student *s1 = new Student(101);
    Student *s2 = new Student(102);
    Student *s3 = new Student(103);

    s1->enroll(*tep);
    s2->enroll(*tep);
    s3->enroll(*tep);

    tep->printStudents();

    delete s2;
    tep->removeStudent(s2);

    tep->printStudents();

    delete s1;
    delete s3;
    delete tep;
}