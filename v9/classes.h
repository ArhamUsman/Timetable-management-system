#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <fstream>                  //store user data
#include <cstdlib>
using namespace std;

class Subject {
    string subject;
public:
    Subject(const string& name = "");
    string get_subject() ;
    void set_subject(const string& new_subject);
    void display();
    bool operator==(Subject other);
    friend ostream& operator<<(ostream& os, const Subject& s);
};

class Section {
    string section;
    vector<Subject> subjects;
public:
    Section(const string& name = "");
    
    string get_section() ;
    void set_section(const string& new_section);
    void display() ;
    void add_subject(const Subject& new_subject);
    void get_all_subjects();
    bool subject_present(Subject subject) ;
    string get_subject(int index) ;
    
    bool operator==(const Section& other) ;
    bool operator==(const string& other_name) ;
    friend ostream& operator<<(std::ostream& os, Section s);
};

class Person {
protected:
    string name;
    vector<Subject> subjects;
public:
    Person(const string& name = "");
    virtual ~Person() = default;
    
    string get_name() ;
    void set_name(const string& new_name);
    
    virtual void display()  = 0;
    virtual void add_subject(Subject new_subject, Section section) = 0;
};

class Student : public Person {
    Section section;
public:
    Student(const string& name = "", const string& section = "");
    void display()  override;
    void add_subject(Subject new_subject, Section section) override;
    vector<Subject> get_all_subjects();
};

class Teacher : public Person {
    vector<Section> sections;
public:
    Teacher(const string& name = "");
    void display()  override;
    void add_subject(Subject new_subject, Section section) override;
    bool operator==(const string& other_name) ;
    friend ostream& operator<<(ostream& os, Teacher t);
};

class Venue {
    string venue;
public:
    Venue(const string& name = "");
    string get_venue() ;
    void set_venue(const string& new_venue);
    void display() ;
    friend ostream& operator<<(ostream& os, const Venue& v);
};

class Time {
    string time;
public:
    Time(const string& time = "");
    
    string get_time() ;
    void set_time(const string& new_time);
    void display() ;
    friend ostream& operator<<(ostream& os, const Time& t);
};

class slot {
    int period_num;
    Time time;
    Venue venue;
    Subject subject;
    Section section;
    Teacher teacher;
public:
    slot();
    slot(int period_num, Time time, Venue venue, Subject subject, Section section, Teacher teacher);
    
    bool is_included(Section mySection,vector <Subject> mySubjects);
    bool is_free() ;
    void display() ;

    void operator=(slot s);
};

class week_day {
    vector<slot> slots;
public:
    week_day();
    week_day(const vector<slot>& slots);
    week_day(const week_day& other);
    
    void addSlot(const slot& new_slot);
    vector<slot> get_slots(const Section& section, 
                              const vector<Subject>& subjects);
};

class custom_exception : public exception {
    char* s;
public:
    custom_exception(const char* message = "Error");
    const char* what() const noexcept override;
};

class program_control {
    vector <week_day> days;
    vector<Teacher> all_teachers;
    Student myBoy;
    vector<Section> all_sections;
    
    int add_teacher(const string& name, 
                          const Subject& subject, 
                          const Section& section);
    int add_section(const string& name, 
                           const Subject& subject);
    int string_to_num(const string& s) ;
    string input_section();
    vector<string> input_subjects(Section section);
public:    
    void add_slot(int day, int period, const string& time,
                const string& venue, const string& subject,
                const string& section, const string& teacher);
    void intialise_slots(vector <week_day> dayz);
    void initialise_myBoy();
    void display_schedule(int day) ;
};

#endif // CLASSES_H