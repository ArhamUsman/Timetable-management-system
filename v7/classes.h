#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <string>
#include <vector>
#include <exception>
using namespace std;

class Subject {
    std::string subject_name;
public:
    explicit Subject(const std::string& name = "");
    
    std::string get_subject() const;
    void set_subject(const std::string& new_subject);
    void display() const;
    bool operator==(const Subject& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Subject& s);
};

class Section {
    std::string section_name;
    std::vector<Subject> subjects;
public:
    explicit Section(const std::string& name = "");
    
    std::string get_section() const;
    void set_section(const std::string& new_section);
    void display() const;
    void add_subject(const Subject& new_subject);
    bool subject_present(const Subject& subject) const;
    std::string get_subject(int index) const;
    
    bool operator==(const Section& other) const;
    bool operator==(const std::string& other_name) const;
    friend std::ostream& operator<<(std::ostream& os, const Section& s);
};

class Person {
protected:
    std::string name;
    std::vector<Subject> subjects;
public:
    Person(const std::string& name = "");
    virtual ~Person() = default;
    
    std::string get_name() const;
    void set_name(const std::string& new_name);
    
    virtual void display() const = 0;
    virtual void add_subject(const Subject& new_subject, const Section& section) = 0;
};

class Student : public Person {
    Section section;
public:
    Student(const std::string& name = "", const std::string& section = "");
    void display() const override;
    void add_subject(const Subject& new_subject, const Section& section) override;
    std::vector<Subject> get_all_subjects() const;
};

class Teacher : public Person {
    std::vector<Section> sections;
public:
    explicit Teacher(const std::string& name = "");
    void display() const override;
    void add_subject(const Subject& new_subject, const Section& section) override;
    bool operator==(const std::string& other_name) const;
    friend std::ostream& operator<<(std::ostream& os, const Teacher& t);
};


class Venue {
    std::string venue_name;
public:
    explicit Venue(const std::string& name = "");
    
    std::string get_venue() const;
    void set_venue(const std::string& new_venue);
    void display() const;
    friend std::ostream& operator<<(std::ostream& os, const Venue& v);
};

class Time {
    std::string time_str;
public:
    explicit Time(const std::string& time = "");
    
    std::string get_time() const;
    void set_time(const std::string& new_time);
    void display() const;
    friend std::ostream& operator<<(std::ostream& os, const Time& t);
};

class Slot {
    int period_num;
    Time time;
    Venue venue;
    Subject subject;
    Section section;
    Teacher teacher;
public:
    Slot();
    Slot(int period, Time t, Venue v, Subject s, Section sec, Teacher teach);
    
    bool is_included(const Section& my_section, const std::vector<Subject>& my_subjects) const;
    bool is_free() const;
    void display() const;
};

class WeekDay {
    std::vector<Slot> slots;
public:
    WeekDay();
    explicit WeekDay(const std::vector<Slot>& slots);
    WeekDay(const WeekDay& other);
    
    void add_slot(const Slot& new_slot);
    std::vector<Slot> get_slots(const Section& section, 
                              const std::vector<Subject>& subjects) const;
};

class CustomException : public std::exception {
    char message[100];
public:
    explicit CustomException(const char* msg = "Error");
    const char* what() const noexcept override;
};

class ProgramControl {
    WeekDay* days[5];
    std::vector<Teacher> teachers;
    Student current_student;
    std::vector<Section> sections;
    
    int find_or_add_teacher(const std::string& name, 
                          const Subject& subject, 
                          const Section& section);
    int find_or_add_section(const std::string& name, 
                           const Subject& subject);
    int string_to_int(const std::string& s) const;
    
public:
    ProgramControl();
    ~ProgramControl();
    
    void add_slot(int day, int period, const std::string& time,
                const std::string& venue, const std::string& subject,
                const std::string& section, const std::string& teacher);
    void initialize_student();
    void show_schedule(int day) const;
};

#endif // CLASSES_H