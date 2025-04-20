#include <iostream>
using namespace std;

//Abstracted
class Identity{                       //abstract class
    string name;
    string id;
};

class Time{
    int hour;
    int minute;
};


//Encapsulated
class Teacher:public Identity{        //inheritence
    string** course_section;
    int noOfCourses;
};


class Course:public Identity{
    int creditHours;
};

class Period{
    Time starting_time, ending_time;
    string course_id, teacher_id, venue;
};

class Timetable{
    Period** schedule;  //[day x noOfPeriods]
    Course* all_courses;
    Teacher* all_teachers;    
};

int main(){
    cout<<"Hello World";
}