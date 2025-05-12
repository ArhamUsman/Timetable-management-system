#include "classes.h"                //Encapsulation
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <fstream>                  //store user data
#include <cstdlib>
#include <time.h>
#include <filesystem>
using namespace std;

//Subject implementation
Subject::Subject(const string& name):subject(name){}
string Subject::get_subject(){
    return subject;
}
void Subject::set_subject(const string& new_subject){
    subject=new_subject;
}
void Subject::display(){
    cout<<"Subject: "<<subject<<endl;
}
bool Subject::operator==(Subject other){      //operator overloading
    return subject==other.subject;
}

//Section implementation
Section::Section(const string& name):section(name){}
string Section::get_section(){
    return section;
}
void Section::set_section(const string& new_section){
    section=new_section;
}
void Section::display(){
    cout<<"Section: "<<section<<endl;
}
void Section::add_subject(const Subject& new_subject){
    for (int i=0; i<subjects.size(); i++){
        if (subjects[i]==new_subject) return;
    }
    subjects.push_back(new_subject);
}
void Section::get_all_subjects(){
    cout<<"List of all Subjects: \n";
    for (int i=0; i<subjects.size(); i++){
        cout<<i<<" : "<<subjects[i].get_subject()<<endl;
    }
    cout<<"----------\n";
}
bool Section::subject_present(Subject subject){
    for (int i=0; i<subjects.size(); i++){
        if (subject==subjects[i]) return true;
    }
    return false;
}
string Section::get_subject(int index){
    if (index==-1) 
        throw custom_exception("Error! Index should be a positive integer!");
    if (index>=subjects.size()) 
        throw custom_exception("Error! Kindly ensure that you choose a valid index!");
    return subjects[index].get_subject();
}
bool Section::operator==(const Section& other){    //operator overloading
    return (other.section==section);
}
bool Section::operator==(const string& other_name){
    return section==other_name;
}

//Person Implementation
Person::Person(const string& name):name(name){}
string Person::get_name(){
    return name;
}
void Person::set_name(const string& new_name){
    name=new_name;
}

//Student Implementation
Student::Student(const string& name, const string& section):Person(name), section(section){}
void Student::display(){
    cout<<"Displaying student details:\n";
    cout<<"Name:"<<get_name()<<endl;
    section.display();
}
void Student::add_subject(Subject new_subject, Section section){
    this->section = section;
    if (section.subject_present(new_subject)) {
        // Check if subject already exists
        for (auto& sub : subjects) {
            if (sub == new_subject) return;
        }
        subjects.push_back(new_subject);
    }
}
string Student::get_section(){
    return section.get_section();
}
vector<Subject> Student::get_all_subjects(){
    return subjects;
}

//Teacher implementation
Teacher::Teacher(const string& name):Person(name){}
void Teacher::display(){
    cout<<"Displaying teacher details:\n";
    cout<<"Name:"<<get_name()<<endl;
    if (!subjects.empty()){
        cout<<"Subjects taught:\n";
    }
    for (int i=0; i<subjects.size(); i++){
        subjects[i].display();
    }
}
void Teacher::add_subject(Subject new_subject, Section section){
    cout<<"Entering loop\n";
    for (int i=0; i<subjects.size(); i++){
        cout<<"Inside loop: "<<i<<endl;
        cout<<"Subject i: "<<subjects[i]<<"  Section i: "<<sections[i]<<endl;
        if (subjects[i]==new_subject&&sections[i]==section){
            cout<<"Already present\n";
            return;
        }
    }
    cout<<"Adding a new one\n";
    subjects.push_back(new_subject);
    sections.push_back(section);
}
bool Teacher::operator==(const string& other_name){
    return get_name()==other_name;
}

//Venue Implementation
Venue::Venue(const string& name):venue(name){}
string Venue::get_venue(){
    return venue;
}
void Venue::set_venue(const string& new_venue){
    venue=new_venue;
}
void Venue::display(){
    cout<<"Venue: "<<venue<<endl;
}

//Time implementation
Time::Time(const string& time):time(time){}
string Time::get_time(){
    return time;
}
void Time::set_time(const string& new_time){
    time=new_time;
}
void Time::display(){
    cout<<"Time: "<<time<<endl;
}

//Operator overloading
ostream& operator<<(ostream& os, Teacher t){
    os<<t.get_name();
    return os;
}
ostream& operator<<(ostream& os, const Subject& t){
    os<<t.subject;
    return os;    
}
ostream& operator<<(ostream& os, Section t){
    os<<t.get_section();
    return os;
}
ostream& operator<<(ostream& os, const Venue& t){
    os<<t.venue;
    return os;
}
ostream& operator<<(ostream& os, const Time& t){
    os<<t.time;
    return os;
}

//slot implementation
slot::slot(){}
slot::slot(int period_num, Time time, Venue venue, Subject subject, Section section, Teacher teacher):teacher(teacher), section(section), subject(subject),venue(venue),time(time),period_num(period_num){}
bool slot::is_included(Section mySection,vector <Subject> mySubjects){
    if (section==mySection){
        for (int i=0; i<mySubjects.size(); i++){
            if (mySubjects[i]==subject){
                return true;
            }
        }
    }
    return false;
}
bool slot::is_free(){
    Subject empty;
    return subject==empty;
}
void slot::display(){
    if (is_free()){
        return;
    }
    cout<<period_num<<"|"<<time<<"|"<<venue<<"|";
    cout<<subject<<"|"<<section<<"|"<<teacher<<endl;
}
void slot::operator=(slot s){
    cout<<"here in  =\n";
    period_num=s.period_num;
    time=s.time;
    venue=s.venue;
    subject=s.subject;
    section=s.section;
    teacher=s.teacher;  
}


//week_day implementation
week_day::week_day(){
        cout<<"week day created successfully\n";
     
}
week_day::week_day(const vector<slot>& slots){
    this->slots=slots;
}
week_day::week_day(const week_day& day){
    this->slots=day.slots;
}
void week_day::addSlot(slot& new_slot){
    // cout << "DEBUG: Entering addSlot" << endl;  // Track if we reach here
    // cout << "DEBUG: Entering addSlot. Current size: " << slots.size() 
    //      << ", capacity: " << slots.capacity() << endl;
    
    // try {
        slots.push_back(new_slot);
    //     cout << "DEBUG: Push successful. New size: " << slots.size() << endl;
    // } catch (const exception& e) {
    //     cerr << "EXCEPTION in addSlot: " << e.what() << endl;
    // }
}
vector<slot> week_day::get_slots(const Section& section, const vector<Subject>& subjects){
    vector<slot> yourSlots;
    for (int i=0; i<slots.size(); i++){
        if (slots[i].is_included(section, subjects)){
            yourSlots.push_back(slots[i]);
        }
        else {
            yourSlots.push_back(slot());
        }
    }
    return yourSlots;
}

week_day& week_day::operator=(const week_day& other){
    if (this!= &other){
        slots=other.slots;
    }
    return *this;
}

week_day& week_day::operator=(week_day&& other) noexcept{
    if (this!= &other){
        slots=move(other.slots);
    }
    return *this;
}

vector<slot> week_day::get_all_slots(){
    return slots;
}
//Exception handling
custom_exception::custom_exception(const char* message){
    strcpy(s, message);
}
const char* custom_exception::what() const noexcept{
    return s;
}

//Program control implementation
int program_control::add_teacher(const string& name, const Subject& subject, const Section& section){
    for (int i=0; i<all_teachers.size(); i++){
        if (all_teachers[i]==name){
            cout<<"adding subject\n";
            all_teachers[i].add_subject(subject, section);
            cout<<"subject added\n";
            return i;
        }
    }
    int x=all_teachers.size();
    Teacher t(name);
    t.add_subject(subject, section);
    all_teachers.push_back(t);
    return x;
}    
int program_control::add_section(const string& name, const Subject& subject){
    for (int i=0; i<all_sections.size(); i++){
        if (all_sections[i]==name){
            all_sections[i].add_subject(subject);
            return i;
        }
    }
    int x=all_sections.size();
    Section s(name);
    s.add_subject(subject);
    all_sections.push_back(s);
    return x;
}
int program_control::string_to_num(const string& s){
    int x,y;
    x=0;
    for (int i=0; i<s.length(); i++){
        y=s[i]-'0';
        if (y<0||y>9) return -1;
        x=x*10+y;
    }
    return x;
}

string program_control::input_section(){
    while (1){
        system("cls");
        cout<<"List of available sections: \n";
        for (int i=0; i<all_sections.size(); i++){
            cout<<i<<". "<<all_sections[i].get_section()<<endl;
        }
        cout<<"\nEnter your section index: ";
        string s;
        cin>>s;
        try{
            int i=string_to_num(s);
            if (i==-1) 
                throw custom_exception("Error! Index should be a positive integer!");
            if (i>=all_sections.size()) 
                throw custom_exception("Error! Kindly ensure that you choose a valid index!");
            return all_sections[i].get_section();
        }            
        catch(custom_exception& c){
            cout<<c.what()<<endl;
        }
    }
}

Section program_control::input_section(int x){
    while (1){
        system("cls");
        cout<<"List of available sections: \n";
        for (int i=0; i<all_sections.size(); i++){
            cout<<i<<". "<<all_sections[i].get_section()<<endl;
        }
        cout<<"\nEnter your section index: ";
        string s;
        cin>>s;
        try{
            int i=string_to_num(s);
            if (i==-1) 
                throw custom_exception("Error! Index should be a positive integer!");
            if (i>=all_sections.size()) 
                throw custom_exception("Error! Kindly ensure that you choose a valid index!");
            return all_sections[i];
        }            
        catch(custom_exception& c){
            cout<<c.what()<<endl;
        }
    }
}

vector<string> program_control::input_subjects(Section& section){
    vector <string> subjects;
    while (1){
        system("cls");
        section.get_all_subjects();
        cout<<"Enter your subject index(-1 to exit): \n";
        string s;
        cin>>s;
        if (s=="-1"){
            return subjects;
        }
        try{
            int i=string_to_num(s), flag =0;
            string z=section.get_subject(i);
            for (int a=0; a<subjects.size(); a++){
                if (subjects[a]==z) {
                    flag=1;break;
                }
            }
            if (flag==1) continue;
            subjects.push_back(z);
        }            
        catch(custom_exception& c){
            cout<<c.what()<<endl;
        }
        cout<<"\nPress any key to continue...";
        _getwch();
    }
}
void program_control::add_slot(int day, int period, const string& time,
                const string& venue, const string& subject,
                const string& section, const string& teacher){
    cout<<"Adding teacher\n";
    int x=add_teacher(teacher, Subject(subject), Section(section));
    cout<<"Adding section\n";
    int y=add_section(section, Subject(subject));
    slot s(period, Time(time), Venue(venue), Subject(subject), all_sections[y], all_teachers[x]);
    cout<<"adding slot";
    days[day].addSlot(s);
}
void program_control::add_slot(int day, slot& s){
    cout<<"Adding teacher:"<<s.teacher.get_name()<<"\n";
    int x=add_teacher(s.teacher.get_name(), s.subject, s.section);
    cout<<"Adding section\n";
    int y=add_section(s.section.get_section(), s.subject);
    
    cout<<"Adding slot\n";

    days[day].addSlot(s);
}
void program_control::intialise_slots(vector<week_day>& dayz){
    
    for (int i=0; i<dayz.size(); i++){
        days.push_back(week_day());
        vector <slot> slots = dayz[i].get_all_slots();
        for (int j=0; j<slots.size(); j++){     
            if (slots[j].is_free()) continue;       
            add_slot(i, slots[j]);
        }   
    }
} 
void program_control::initialise_myBoy(){
    if (!filesystem::exists("user.txt")){
        fstream user;
        user.open("user.txt", ios::in|ios::out|ios::trunc);
        string s;
        cout<<"Enter user name: ";
        getline(cin, s);
        user<<s<<endl;
        Section sec=input_section(1);
        user<<sec.get_section()<<endl;
        vector <string>sub=input_subjects(sec);
        for (int i=0; i<sub.size(); i++){
            user<<sub[i]<<endl;
        }
        user.close();
    }
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
void program_control::display_schedule(int day){
    string section;
    section=myBoy.get_section();
    int index=-1;
    for (int i=0; i<all_sections.size(); i++){
        if (all_sections[i].get_section()==section) {
            index=i; break;
        }
    }
    if (index==-1){
        cout<<"Fatal error! User.txt is corrupted. Delete it and try again.";
        cout<<"Inside display schedule\n";
    }
    vector<Subject> subjects=myBoy.get_all_subjects();
    vector<slot> s= days[day].get_slots(section, subjects);
    for (int i=0; i<s.size(); i++){
        s[i].display();
    }
}


/*
Hierarchial Structure:
    1. weekdays -> slots -> info of timetable
    2. all_teachers -> slots
    3. myBoy -> section -> subjects -> slots
    4. all_sections -> subjects(in each section) -> for myBoy

Action when you read csv file:
    1. initialise slot
    2. update teacher (add if not present): add subject
    3. update section (add if not present): add subject

Actions when menu is displayed:
    1. Retrieve user data and store in myBoy
    2. If not present, prompt user to enter their section and subjects and save it
    3. Display menu of showing
        i.   Monday Schedule
        ii.  Tuesday Schedule
        iii. Wednesday Schedule
        iv.  Thursday Schedule
        v.   Friday Schedule
        vi.  Show teacher timetable (in future updates)
*/
