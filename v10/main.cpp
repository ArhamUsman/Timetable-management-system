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
    cout<<"Creating file handler\n";
    FileHandler fileHandler;
    cout<<"File handler created successfully\n";
    cout<<"Creating program control\n";
    program_control programControl;
    cout<<"program control created successfully\n";
    //fileHandler.download_all_files();
    cout<<"Creating days\n";
    vector<week_day> days;
    days.reserve(5);
    for (int i=0; i<5;i++){
        days.emplace_back();
    }
    cout<<"days created successfully\n";
    cout<<"Reading files\n";
    fileHandler.read_all_files(days);
    cout<<"All files read successfully\n";
    cout<<"Initialising slots\n";
    programControl.intialise_slots(days);
    cout<<"Slots initialized successfully\n";
    cout<<"Initialising my boy\n";
    programControl.initialise_myBoy();
    cout<<"My boy initialised successfully\n";
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
            cout<<"Displaying Tuesday Schedule: \n";
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