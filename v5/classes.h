#ifndef TIMETABLE_H
#define TIMETABLE_H
#include <string>

class Person{                       //abstract class

};

class Student:public Person{        //inheritence

};

class Teacher:public Person{

};

class Section{

};

class Subject{

};

class Venue{

};

class Time{
    std::string time;
};

class slot{                         //composition
    int period_num;
    Time time;
    Venue venue;
    Subject subject;
    Section section;
    Teacher teacher;
};

class week_day{                     //composition
    slot* slots;
    int noOfSlots;
};

class program_control{             
    week_day* days[5];              //aggregation
};

#endif