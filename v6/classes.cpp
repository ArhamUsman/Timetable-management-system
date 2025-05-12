#include "classes.h"                //Encapsulation
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <fstream>                  //store user data
#include <cstdlib>
using namespace std;

class Person{                       //abstract class
    string name;
    protected:
    vector <Subject> subjects;
    public:
    Person(string name=""):name(name){}
    string get_name(){
        return name;
    }
    void set_name(string new_name){
        name=new_name;
    }
    virtual void display()=0;       //pure virtual function
    virtual void add_subject(Subject new_subject, Section section)=0;
};

class Section;

class Student:public Person{        //inheritence
    Section section;                //composition
    
    public:
    Student(string name="", string section):Person(name), section(section){}
    void display() override{
        cout<<"Displaying student details:\n";
        cout<<"Name:"<<get_name()<<endl;
        section.display();
    }
    void add_subject(Subject new_subject, Section section) override{
        this->section=section;
        if (section.subject_present(new_subject)){
            for (int i=0; i<subjects.size(); i++){
                if (subjects[i]==new_subject) return;
            }
            subjects.push_back(new_subject);    
        }
    }
    vector<Subject> get_all_subjects(){
        return subjects;
    }
};

class Subject;

class Teacher:public Person{
    vector<Section> sections;
    public:
    Teacher(string name=""):Person(name){}
    void display() override{
        cout<<"Displaying teacher details:\n";
        cout<<"Name:"<<get_name()<<endl;
        if (!subjects.empty()){
            cout<<"Subjects taught:\n";
        }
        for (int i=0; i<subjects.size(); i++){
            subjects[i].display();
        }
    }
    void add_subject(Subject new_subject, Section section) override{
        for (int i=0; i<subjects.size(); i++){
            if (subjects[i]==new_subject&&sections[i]==section) return;
        }
        subjects.push_back(new_subject);
    }
    bool operator==(string new_name){
        return get_name()==new_name;
    }
    friend ostream& operator<<(ostream& os, const Teacher& t);         //friend function
};

class Section{
    string section;
    vector <Subject> subjects;
    public:
    Section(string section=""):section(section){}
    string get_section(){
        return section;
    }
    void set_section(string new_section){
        section=new_section;
    }
    void display(){
        cout<<"Section: "<<section<<endl;
    }
    void add_subject(Subject new_subject){
        for (int i=0; i<subjects.size(); i++){
            if (subjects[i]==new_subject) return;
        }
        subjects.push_back(new_subject);
    }
    void get_all_subjects(){
        cout<<"List of all Subjects: \n";
        for (int i=0; i<subjects.size(); i++){
            cout<<i<<" : "<<subjects[i].get_subject()<<endl;
        }
        cout<<"----------\n";
    }
    bool subject_present(Subject &subject){
        for (int i=0; i<subjects.size(); i++){
            if (subject==subjects[i]) return true;
        }
        return false;
    }
    string get_subject(int index){
        if (index==-1) 
            throw custom_exception("Error! Index should be a positive integer!");
        if (index>=subjects.size()) 
            throw custom_exception("Error! Kindly ensure that you choose a valid index!");
        return subjects[index].get_subject();
    }
    bool operator==(const Section& s) const{    //operator overloading
        return (s.section==section);
    }
    bool operator==(const string s){
        return section==s;
    }
    friend ostream& operator<<(const ostream os, const Section& t);
};

class Subject{
    string subject;
    public:
    Subject(string subject=""):subject(subject){}
    string get_subject(){
        return subject;
    }
    void set_subject(string new_subject){
        subject=new_subject;
    }
    void display(){
        cout<<"Subject: "<<subject<<endl;
    }
    bool operator==(Subject& new_subject){      //operator overloading
        return subject==new_subject.subject;
    }
    friend ostream& operator<<(const ostream os, const Subject& t);
};

class Venue{
    string venue;
    public:
    Venue(string venue=""):venue(venue){}
    string get_venue(){
        return venue;
    }
    void set_venue(string new_venue){
        venue=new_venue;
    }
    void display(){
        cout<<"Venue: "<<venue<<endl;
    }
    friend ostream& operator<<(const ostream os, const Venue& t);
};

class Time{
    string time;
    public:
    Time(string time=""):time(time){}
    string get_time(){
        return time;
    }
    void set_time(string new_time){
        time=new_time;
    }
    void display(){
        cout<<"Time: "<<time<<endl;
    }
    friend ostream& operator<<(const ostream os, const Time& t);
};

ostream& operator<<(ostream& os, const Teacher& t){
    os<<t.get_name();
    return os;
}
ostream& operator<<(const ostream os, const Subject& t){
    
}
ostream& operator<<(const ostream os, const Section& t){
    
}
ostream& operator<<(const ostream os, const Venue& t){
    
}
ostream& operator<<(const ostream os, const Time& t){
    
}
class slot{                         //composition
    int period_num;
    Time time;
    Venue venue;
    Subject subject;
    Section section;
    Teacher teacher;
    public:
    slot(){}
    slot(int period_num, Time time, Venue venue, Subject subject, Section section, Teacher teacher):teacher(teacher), section(section), subject(subject),venue(venue),time(time),period_num(period_num){}
    bool is_included(Section mySection,vector <Subject> mySubjects){
        if (section==mySection){
            for (int i=0; i<mySubjects.size(); i++){
                if (mySubjects[i]==subject){
                    return true;
                }
            }
        }
        return false;
    }
    bool is_free(){
        Subject empty;
        return subject==empty;
    }
    void display(){
        if (is_free){
            return;
        }
        cout<<period_num<<"|"<<time<<"|"<<venue<<"|";
        cout<<subject<<"|"<<section<<"|"<<teacher<<endl;
    }
};

class week_day{                     //composition
    vector <slot> slots;
    public:
    week_day(){
        slots.clear(); 
    }
    week_day(vector <slot> slots){
        this->slots=slots;
    }
    week_day(const week_day& day){
        this->slots=day.slots;
    }
    void addSlot(slot new_slot){
        slots.push_back(new_slot);
    }
    vector<slot> get_slots(Section section, vector <Subject> subjects){
        vector<slot> yourSlots;
        for (int i=0; i<slots.size(); i++){
            if (slots[i].is_included(section, subjects)){
                yourSlots.push_back(slots[i]);
            }
            else {
                yourSlots.push_back(slot());
            }
        }
    }
};

class custom_exception:public exception{
    char s[50];
    public:
    custom_exception(char* message="Error"){
        strcpy(s, message);
    }
    const char* what() const noexcept override{
        return s;
    }
};

class program_control{             
    week_day* days[5];              //aggregation
    vector <Teacher> all_teachers;  //store data of all teachers
    Student myBoy;                  //store user info
    vector <Section> all_sections;  //store data of all sections;
    int add_teacher(string name, Subject subject, Section section){
        for (int i=0; i<all_teachers.size(); i++){
            if (all_teachers[i]==name){
                all_teachers[i].add_subject(subject, section);
                return i;
            }
        }
        int x=all_teachers.size();
        Teacher t(name);
        t.add_subject(subject, section);
        all_teachers.push_back(t);
        return x;
    }    
    int add_section(string name, Subject subject){
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
    int string_to_num(string s){
        int x,y;
        x=0;
        for (int i=0; i<s.length(); i++){
            y=s[i]-'0';
            if (y<0||y>9) return -1;
            x=x*10+y;
        }
        return x;
    }
    string input_section(){
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
    vector<string> input_subjects(Section section){
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
                int i=string_to_num(s);
                string z=section.get_subject(i);
                for (int a=0; a<subjects.size(); a++){
                    if (subjects[a]==z) continue;
                }
                subjects.push_back(z);
            }            
            catch(custom_exception& c){
                cout<<c.what()<<endl;
            }
            cout<<"\nPress any key to continue...";
            _getwch();
        }
    }
    public:
    //initialise the entire structure
    void add_slot(int day, int period_num, string time, string venue, string subject, string section, string teacher){
        int x=add_teacher(teacher, Subject(subject), Section(section));
        int y=add_section(section, Subject(subject));
        slot s(period_num, Time(time), Venue(venue), Subject(subject), all_sections[y], all_teachers[x]);
        days[day]->addSlot(s);
    }
    void initialise_myBoy(){
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
    void display_schedule(int day){
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
};


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
