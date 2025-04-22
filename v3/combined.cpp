#include <iostream>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

//Abstracted
class Identity{                       //abstract class
protected:
    string name;
    string id;
public:
    Identity(string name, string id){
        
    }


};

class Time{
protected:
    string time;
public:
    Time(string time){

    }
};


//Encapsulated
class Teacher:public Identity{        //inheritence
protected:
    string* course_section;
    int noOfCourses;
public:
    Teacher(string name, string id, string *course_section=nullptr, int noOfCourses=0):noOfCourses(noOfCourses), Identity(name, id){
        if (noOfCourses!=0){
            this->course_section=new string[noOfCourses];
            for (int i=0; i<noOfCourses; i++){
                this->course_section[i]=course_section[i];
            }
        }
    }
};

class Course:public Identity{
protected:
    int creditHours;
public:


};

class Period{
protected:
    Time starting_time, ending_time;
    string course_id, teacher_id, venue;
public:


};

class Timetable{
    Period** schedule;  //[day x noOfPeriods]
protected:
    Course* all_courses;
    Teacher* all_teachers;  
public:


};

bool downloadCSV(const string& url, const string& filename) {
    cout << "\nDownloading " << filename << "...\n";
    return system(("curl -L -o \"" + filename + "\" \"" + url + "\"").c_str()) == 0;
}


int main() {
    string url_monday = "https://docs.google.com/spreadsheets/d/1yKior3niRgcgbfeVyALAoJnf3E6dfAOx73_cDYTf4Kw/export?format=csv&gid=1909094994";
    string url_tuesday = "https://docs.google.com/spreadsheets/d/1yKior3niRgcgbfeVyALAoJnf3E6dfAOx73_cDYTf4Kw/export?format=csv&gid=200565107";
    string url_wednesday = "https://docs.google.com/spreadsheets/d/1yKior3niRgcgbfeVyALAoJnf3E6dfAOx73_cDYTf4Kw/export?format=csv&gid=1099672198";
    string url_thursday = "https://docs.google.com/spreadsheets/d/1yKior3niRgcgbfeVyALAoJnf3E6dfAOx73_cDYTf4Kw/export?format=csv&gid=1170001538";
    string url_friday = "https://docs.google.com/spreadsheets/d/1yKior3niRgcgbfeVyALAoJnf3E6dfAOx73_cDYTf4Kw/export?format=csv&gid=690531197";

    string file_monday = "monday.csv";
    string file_tuesday="tuesday.csv";
    string file_wednesday="wednesday.csv";
    string file_thursday="thursday.csv";
    string file_friday="friday.csv";

    bool check = true;
    check &= downloadCSV(url_monday, file_monday);
    check &= downloadCSV(url_tuesday, file_tuesday);
    check &= downloadCSV(url_wednesday, file_wednesday);
    check &= downloadCSV(url_thursday, file_thursday);
    check &= downloadCSV(url_friday, file_friday);

    if (check) cout << "\nAll files updated successfully!\n";
    else cout << "\nSome files failed to download. Using local copies where available...\n";

    ifstream file(file_monday);
    string line;
    while (getline(file, line)) {
        cout << "Line: " << line << "\n"; 
    }

    return 0;
}
