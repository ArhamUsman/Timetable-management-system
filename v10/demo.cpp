#include <iostream>
#include <vector>
using namespace std;

class Subject {
    string subject;
};

class Section {
    string section;
    vector<Subject> subjects;
};

class Person {
protected:
    string name;
    vector<Subject> subjects;
};

class Student : public Person {
    Section section;
};

class Teacher : public Person {
    vector<Section> sections;
};

class Venue {
    string venue;
};

class Time {
    string time;
};

class slot {
    int period_num;
    Time time;
    Venue venue;
    Subject subject;
    Section section;
    Teacher teacher;
};

class week_day {
    vector<slot> slots;
};

class program_control {
    vector <week_day> days;
    vector<Teacher> all_teachers;
    Student myBoy;
    vector<Section> all_sections;
    public:
    void display(){
        cout<<"yippee";
    }
};

int main(){
    program_control as;
    as.display();
}