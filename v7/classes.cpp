#include "classes.h"
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
#include <string.h>
#include <cstring>
using namespace std;

// Person implementation
Person::Person(const std::string& name) : name(name) {}

std::string Person::get_name() const { return name; }

void Person::set_name(const std::string& new_name) { name = new_name; }

// Student implementation
Student::Student(const std::string& name, const std::string& sec) 
    : Person(name), section(Section(sec)) {}

void Student::display() const {
    std::cout << "Student Details:\nName: " << name << "\n";
    section.display();
}

void Student::add_subject(const Subject& new_subject, const Section& sec) {
    section = sec;
    if(section.subject_present(new_subject)) {
        auto it = std::find(subjects.begin(), subjects.end(), new_subject);
        if(it == subjects.end()) {
            subjects.push_back(new_subject);
        }
    }
}

std::vector<Subject> Student::get_all_subjects() const {
    return subjects;
}

// Teacher implementation
Teacher::Teacher(const std::string& name) : Person(name) {}

void Teacher::display() const {
    std::cout << "Teacher Details:\nName: " << name << "\n";
    if(!subjects.empty()) {
        std::cout << "Subjects:\n";
        for(const auto& sub : subjects) {
            sub.display();
        }
    }
}

void Teacher::add_subject(const Subject& new_subject, const Section& sec) {
    for(size_t i = 0; i < subjects.size(); ++i) {
        if(subjects[i] == new_subject && sections[i] == sec) return;
    }
    subjects.push_back(new_subject);
    sections.push_back(sec);
}

bool Teacher::operator==(const std::string& other_name) const {
    return name == other_name;
}

// Section implementation
Section::Section(const std::string& name) : section_name(name) {}

std::string Section::get_section() const { return section_name; }

void Section::set_section(const std::string& new_name) { section_name = new_name; }

void Section::display() const {
    std::cout << "Section: " << section_name << "\n";
}

void Section::add_subject(const Subject& new_subject) {
    if(std::find(subjects.begin(), subjects.end(), new_subject) == subjects.end()) {
        subjects.push_back(new_subject);
    }
}

bool Section::subject_present(const Subject& subject) const {
    return std::find(subjects.begin(), subjects.end(), subject) != subjects.end();
}

std::string Section::get_subject(int index) const {
    if(index < 0 || index >= static_cast<int>(subjects.size())) {
        throw CustomException("Invalid subject index");
    }
    return subjects[index].get_subject();
}

bool Section::operator==(const Section& other) const {
    return section_name == other.section_name;
}

bool Section::operator==(const std::string& other_name) const {
    return section_name == other_name;
}

// Subject implementation
Subject::Subject(const std::string& name) : subject_name(name) {}

std::string Subject::get_subject() const { return subject_name; }

void Subject::set_subject(const std::string& new_subject) { subject_name = new_subject; }

void Subject::display() const {
    std::cout << "Subject: " << subject_name << "\n";
}

bool Subject::operator==(const Subject& other) const {
    return subject_name == other.subject_name;
}

// Venue implementation
Venue::Venue(const std::string& name) : venue_name(name) {}

std::string Venue::get_venue() const { return venue_name; }

void Venue::set_venue(const std::string& new_venue) { venue_name = new_venue; }

void Venue::display() const {
    std::cout << "Venue: " << venue_name << "\n";
}

// Time implementation
Time::Time(const std::string& time) : time_str(time) {}

std::string Time::get_time() const { return time_str; }

void Time::set_time(const std::string& new_time) { time_str = new_time; }

void Time::display() const {
    std::cout << "Time: " << time_str << "\n";
}

// Operator overloads
std::ostream& operator<<(std::ostream& os, const Teacher& t) {
    os << t.get_name();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Subject& s) {
    os << s.get_subject();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Section& s) {
    os << s.get_section();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Venue& v) {
    os << v.get_venue();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Time& t) {
    os << t.get_time();
    return os;
}

// Slot implementation
Slot::Slot() : period_num(-1) {}

Slot::Slot(int period, Time t, Venue v, Subject s, Section sec, Teacher teach)
    : period_num(period), time(t), venue(v), subject(s), section(sec), teacher(teach) {}

bool Slot::is_included(const Section& my_section, const std::vector<Subject>& my_subjects) const {
    return section == my_section && 
           std::find(my_subjects.begin(), my_subjects.end(), subject) != my_subjects.end();
}

bool Slot::is_free() const {
    return subject == Subject();
}

void Slot::display() const {
    if(is_free()) return;
    std::cout << period_num << "|" << time << "|" << venue << "|"
              << subject << "|" << section << "|" << teacher << "\n";
}

// WeekDay implementation
WeekDay::WeekDay() = default;

WeekDay::WeekDay(const std::vector<Slot>& slots) : slots(slots) {}

WeekDay::WeekDay(const WeekDay& other) : slots(other.slots) {}

void WeekDay::add_slot(const Slot& new_slot) {
    slots.push_back(new_slot);
}

std::vector<Slot> WeekDay::get_slots(const Section& section, 
                                   const std::vector<Subject>& subjects) const {
    std::vector<Slot> result;
    for(const auto& slot : slots) {
        if(slot.is_included(section, subjects)) {
            result.push_back(slot);
        }
    }
    return result;
}

// CustomException implementation
CustomException::CustomException(const char* msg) {
    strncpy(message, msg, sizeof(message)-1);
    message[sizeof(message)-1] = '\0';
}

const char* CustomException::what() const noexcept {
    return message;
}

// ProgramControl implementation
ProgramControl::ProgramControl() {
    for(auto& day : days) day = new WeekDay();
}

ProgramControl::~ProgramControl() {
    for(auto& day : days) delete day;
}

void ProgramControl::add_slot(int day, int period, const std::string& time,
                            const std::string& venue, const std::string& subject,
                            const std::string& section, const std::string& teacher) {
    int x=find_or_add_teacher(teacher, Subject(subject), Section(section));
    int y=find_or_add_section(section, Subject(subject));
    slot s(period_num, Time(time), Venue(venue), Subject(subject), all_sections[y], all_teachers[x]);
    days[day]->addSlot(s);
}

void ProgramControl::initialize_student() {
    ofstream user;
    user.open("user.txt", ios::__noreplace);
    if (!user.good()){
        user.close();
        user.open("user.txt", ios::in|ios::out|ios::trunc);
        string s;
        cout<<"Enter user name: ";
        cin>>s;
        user<<s<<endl;
        s=input_section();
        user<<s<<endl;
        vector <string>sub=input_subjects(s);
        for (int i=0; i<sub.size(); i++){
            user<<sub[i]<<endl;
        }
    }
    user.close();
    ifstream read_from_file("user.txt");
    string name, temp, section; vector <Subject> subjects;
    read_from_file>>name;
    read_from_file>>section;
    myBoy=Student(name, section);
    int index=-1;
    for (int i=0; i<all_sections.size(); i++){
        if (all_sections[i]==section) {
            index=i; break;
        }
    }
    if (index==-1){
        cout<<"Fatal error! User.txt is corrupted. Delete it and try again.";
        exit(-1);
    }
    while (getline(read_from_file, temp)){
        myBoy.add_subject(Subject(temp), all_sections[index]);
    }
}

void ProgramControl::show_schedule(int day) const {
string section;
    int index=-1;
    for (int i=0; i<all_sections.size(); i++){
        if (all_sections[i]==section) {
            index=i; break;
        }
    }
    if (index==-1){
        cout<<"Fatal error! User.txt is corrupted. Delete it and try again.";
        exit(-1);
    }
    vector<Subject> subjects=myBoy.get_all_subjects();
    vector<slot> s= days[day]->get_slots(section, subjects);
    for (int i=0; i<s.size(); i++){
        s[i].display();
    }
}