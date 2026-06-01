#pragma once
#include <iostream>
#include <iomanip>
#include "DateLibrary.h"
#include"Global.h"
using namespace std;
class clsScreen
{
protected :
    static void _DrawDeniedAccessScreen() {
        system("cls");
        
        cout << endl << endl << endl;
        cout << setw(37) << left << "" << "---------------------------------------------------\n";
        cout << setw(37) << left << "" << "      Access Denied,\n";
        cout << setw(37) << left << "" << "      You donot have permission to do this,\n";
        cout << setw(37) << left << "" << "      Please contact your admin .\n";
        cout << setw(37) << left << "" << "---------------------------------------------------\n\n";
    }
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << setw(37) << left << "" << "_________________________________________________\n\n";
        cout << setw(37) << left << ""  << Title<<endl;
        if (SubTitle != "")
        {
            cout << setw(37) << left << ""  << SubTitle << endl;
        }
        cout <<endl<< setw(37) << left << "" << "_________________________________________________\n\n";
        cout << endl << setw(37) << left << "" << "User: " << currentUser.UserName << endl;
        cout << endl << setw(37) << left << "" << "Date: " << clsDate().DateToString() << endl<<endl;
    }


};

