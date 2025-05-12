#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Split a string by delimiter
vector<string> split(const string& str, char delim) {
    vector<string> tokens;
    stringstream ss(str);
    string temp;
    while (getline(ss, temp, delim)) {
        tokens.push_back(temp);
    }
    return tokens;
}

// Trim from end
string trimEnd(string s) {
    return s.erase(s.find_last_not_of(" \t\n\r\f\v") + 1);
}

int main() {
    ifstream file("data.csv");
    string line;
    vector<string> slotNumbers;
    vector<string> timeSlots;
    vector<string> classNames;
    vector<vector<string>> rawData;

    int rowCount = 0;
    while (getline(file, line)) {
        vector<string> row = split(line, ',');
        if (rowCount == 1) {
            slotNumbers = row; // Row 2 (index 1)
        } 
        else if (rowCount == 2) {
            timeSlots = row; // Row 3 (index 2)
        } 
        else if (rowCount >= 4) {
            classNames.push_back(row[0]); // Column A
            rawData.push_back(row);       // Full row
        }
        rowCount++;
    }

    // Process timetable data
    for (size_t i = 0; i < rawData.size(); ++i) {
        string className = classNames[i];
        for (size_t j = 1; j < rawData[i].size(); ++j) {
            string cell = rawData[i][j];
            if (cell.find('/') == string::npos) continue; // skip garbage

            // Split by newline
            vector<string> lines = split(cell, '\n');
            if (lines.size() < 2) continue;

            string subjectSection = lines[0];
            string teacher = trimEnd(lines[1]);

            size_t slashStart = subjectSection.find('/');
            size_t slashEnd = subjectSection.rfind('/');

            if (slashStart == string::npos || slashEnd == string::npos || slashEnd <= slashStart) continue;

            string subject = trimEnd(subjectSection.substr(0, slashStart));
            string section = trimEnd(subjectSection.substr(slashStart + 1, slashEnd - slashStart - 1));
            string time = timeSlots.size() > j ? timeSlots[j] : "Unknown";

            // Output clean result
            cout << "Class: " << className << "\n"
                 << "Subject: " << subject << "\n"
                 << "Section: " << section << "\n"
                 << "Teacher: " << teacher << "\n"
                 << "Time: " << time << "\n\n";
        }
    }

    return 0;
}
