#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"


class clsClientsListScreen : protected clsScreen
{

private:

    static void _PrintOneClientRecordLineInList(const  clsBankClient& client) {
        cout << "\t| " << left << setw(15) << client.AccountNumber;
        cout << "| " << left << setw(30) << client.FullName();
        cout << "| " << left << setw(13) << client.PhoneNumber;
        cout << "| " << left << setw(20) << client.Email;
        cout << "| " << left << setw(8) << client.PinCode;
        cout << "| " << left << setw(13) << fixed << setprecision(2) << client.AccountBalance;

    }

public:
    
    static void ShowClientListScreen() {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        string subtitle = "\t\t       (" + to_string(vClients.size()) + ") Client(s)";

        _DrawScreenHeader("\t\t     Clients List Screen", subtitle);
        
        cout << "\t_______________________________________________________________________________________________________________\n\n";
        cout << "\t| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(30) << "Client Name";
        cout << "| " << left << setw(13) << "Phone Number";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(8) << "Pin Code";
        cout << "| " << left << setw(13) << "Balance ";
        cout << endl;
        cout << "\t_______________________________________________________________________________________________________________\n";
        cout << endl;
        if (vClients.size() == 0) {
            cout << "\t\t\t\t\tNo Clients Avalibale In The System!!!!!";
        }
        else {
            for (const clsBankClient& client : vClients) {
                _PrintOneClientRecordLineInList(client);
                cout << endl;
            }
        }
        cout << endl;
        cout << "\t_______________________________________________________________________________________________________________\n";


    }





};


