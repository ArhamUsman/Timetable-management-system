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
        }
        else if (choice=="2"){
            cout<<"Displaying Thursday Schedule: \n";
        }
        else if (choice=="3"){
            cout<<"Displaying Wednesday Schedule: \n";
        }
        else if (choice=="4"){
            cout<<"Displaying Thursday Schedule: \n";
        }
        else if (choice=="5"){
            cout<<"Displaying Friday Schedule: \n";
        }
        else if (choice=="6"){
            cout<<"Displaying Monday Schedule: \n";
        }
        else{
            cout<<"Wrong Choice! Try Again\n";
        }
        cout<<"\n\nPress any key to continue...\n";
        _getwch();
    }
}