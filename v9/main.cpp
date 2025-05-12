#include "classes.h"        //abstraction
#include "files.h"
#include <iostream>
#include <cstdlib>
using namespace std;

/*
Actions when menu is displayed:
    1. Retrieve user data and store in myBoy
    2. If not present, prompt user to enter their section and subjects and save it
*/

int main(){
    FileHandler fileHandler;
    program_control programControl;
    //fileHandler.download_all_files();
    vector<week_day> days(5);
    fileHandler.read_all_files(days);
    programControl.intialise_slots(days);
    programControl.initialise_myBoy();
    while (1){
        system("cls");
        cout<<"1. Monday Schedule\n";
        cout<<"2. Tuesday Schedule\n";
        cout<<"3. Wednesday Schedule\n";
        cout<<"4. Thursday Schedule\n";
        cout<<"5. Friday Schedule\n";
        cout<<"6. Teacher Schedule\n";
        cout<<"\nEnter your choice: ";
        string choice;
        getline(cin, choice);
        system("cls");
        if (choice=="1"){
            cout<<"Displaying Monday Schedule: \n";
            programControl.display_schedule(0);
        }
        else if (choice=="2"){
            cout<<"Displaying Thursday Schedule: \n";
            programControl.display_schedule(1);
        }
        else if (choice=="3"){
            cout<<"Displaying Wednesday Schedule: \n";
            programControl.display_schedule(2);
        }
        else if (choice=="4"){
            cout<<"Displaying Thursday Schedule: \n";
            programControl.display_schedule(3);
        }
        else if (choice=="5"){
            cout<<"Displaying Friday Schedule: \n";
            programControl.display_schedule(4);
        }
        else if (choice=="6"){
            cout<<"Displaying Monday Schedule: \n";
            programControl.display_schedule(5);
        }
        else{
            cout<<"Wrong Choice! Try Again\n";
        }
        cout<<"\n\nPress any key to continue...\n";
        _getwch();
    }
}