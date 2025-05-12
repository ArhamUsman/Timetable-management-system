#include "files.h"
#include "classes.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class FileHandler{
protected:
    bool downloadCSV(const string& url, const string& filename) {
        cout << "\nDownloading " << filename << "...\n";
        return system(("curl -L -o \"" + filename + "\" \"" + url + "\"").c_str()) == 0;
    }
private:
    bool download_all_files() {
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
        else {
            cout << "\nSome files failed to download. Using local copies where available...\n";
            return false;
        }
        return true;
    }
    bool read_all_files(){

    }
};