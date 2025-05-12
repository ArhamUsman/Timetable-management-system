#include "classes.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

void print(vector<string>& s);
int string_to_num(string s);
vector<string> split(const string &s, char delimiter);

string trimEnd(string s);

class FileHandler{
protected:
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

    bool downloadCSV(const string& url, const string& filename);
public:
    bool download_all_files();
    vector<week_day> read_all_files();
    void read_all_files(vector<week_day>& weekdays);
};