#include "files.h"
#include "classes.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

void print(vector<string>& s){
    for (int i=0; i<s.size(); i++){
        cout<<s[i]<<" , ";
    }
    cout<<endl;
}

int string_to_num(string s){
    int x=0, y;
    for (int i=0; i<s.length(); i++){
        y=s[i]-'0';
        x=x*10+y;
    }
    return x;
}

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

string trimEnd(string s) {
    return s.erase(s.find_last_not_of(" \t\n\r\f\v") + 1);
}

bool FileHandler::downloadCSV(const string& url, const string& filename) {
    cout << "\nDownloading " << filename << "...\n";
    return system(("curl -L -o \"" + filename + "\" \"" + url + "\"").c_str()) == 0;
}

bool FileHandler::download_all_files() {
    bool check = true;
    check &= downloadCSV(url_monday, file_monday);
    check &= downloadCSV(url_tuesday, file_tuesday);
    check &= downloadCSV(url_wednesday, file_wednesday);
    check &= downloadCSV(url_thursday, file_thursday);
    check &= downloadCSV(url_friday, file_friday);

    if (check) cout << "\nAll files updated successfully!\n";
    else {
        cout << "\nSome files failed to download. Using local copies where available...\n";
        return false;
    }
    return true;
}
vector <week_day> FileHandler::read_all_files(){
    vector <week_day> weekdays;
    slot s;
    int period_num;
    string time,venue, subject,section,teacher; 
    ifstream file;
    for (int i=0; i<5; i++){
        file.close();
        if (i==0) {
            cout<<"reading monday data\n";
            file.open(file_monday);
        }
        else if (i==1){
            cout<<"reading tuesday data\n";
            file.open(file_tuesday);
        } 
        else if (i==2) {
            cout<<"reading wednesday data\n";
            file.open(file_wednesday);
        }
        else if (i==3) {
            file.open(file_thursday);
            cout<<"reading thursday data\n";
        }
        else {
            file.open(file_friday);
            cout<<"reading friday data\n";
        }
         
        if (!file.is_open()) {
            cerr << "Failed to open file.\n";
            exit(-1);
        }

        string line;
        
        while (getline(file, line)) {
            vector<string> cells = split(line, ',');
            for (const string &cell : cells) {
                if (cell.empty()) { // Empty cell
                    continue;
                }

                vector<string> parts = split(cell, '/');
                print(parts);
                if (parts.size() == 6) {
                    period_num =string_to_num(parts[0]); // Day
                    time=parts[1];      // Time
                    venue=parts[2];     // Location
                    subject=parts[3];   // Subject
                    section=parts[4];   // Class
                    teacher=parts[5];   // Teacher
                    cout<<"start choking\n";
                    s=slot(period_num, Time(time), Venue(venue), Subject(subject), Section(section), Teacher(teacher));
                    cout<<"choked\n";
                    weekdays[i].addSlot(s);
                    cout<<"success\n";
                } else {
                    cerr << "Malformed cell: " << cell << "\n";
                }
            }
        }
    }
    return weekdays;
}
void FileHandler::read_all_files(vector <week_day>& weekdays){
    slot s;
    int period_num;
    string time,venue, subject,section,teacher; 
    ifstream file;
    for (int i=0; i<5; i++){
        file.close();
        if (i==0) {
            cout<<"reading monday data\n";
            file.open(file_monday);
        }
        else if (i==1){
            cout<<"reading tuesday data\n";
            file.open(file_tuesday);
        } 
        else if (i==2) {
            cout<<"reading wednesday data\n";
            file.open(file_wednesday);
        }
        else if (i==3) {
            file.open(file_thursday);
            cout<<"reading thursday data\n";
        }
        else {
            file.open(file_friday);
            cout<<"reading friday data\n";
        }
         
        if (!file.is_open()) {
            cerr << "Failed to open file.\n";
            exit(-1);
        }

        string line;
        
        while (getline(file, line)) {
            vector<string> cells = split(line, ',');
            for (const string &cell : cells) {
                if (cell.empty()) { // Empty cell
                    continue;
                }

                vector<string> parts = split(cell, '/');
                print(parts);
                if (parts.size() == 6) {
                    period_num =string_to_num(parts[0]); // Day
                    time=parts[1];      // Time
                    venue=parts[2];     // Location
                    subject=parts[3];   // Subject
                    section=parts[4];   // Class
                    teacher=parts[5];   // Teacher
                    cout<<"start choking\n";
                    s=slot(period_num, Time(time), Venue(venue), Subject(subject), Section(section), Teacher(teacher));
                    cout<<"choked\n";
                    weekdays[i].addSlot(s);
                    cout<<"success\n";
                } else {
                    cerr << "Malformed cell: " << cell << "\n";
                }
            }
        }
        cout<<"Starting next iteration\n";
    }
}