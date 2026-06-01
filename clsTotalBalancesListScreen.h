#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "UtilityLibrary.h"

class clsTotalBalancesListScreen : protected clsScreen
{

private:

    static void _PrintOneClientRecordLineInBalanceList(const clsBankClient& client) {
        cout << "\t\t\t| " << left << setw(16) << client.AccountNumber;
        cout << "| " << left << setw(49) << client.FullName();
        cout << "| " << left << setw(27) << fixed << setprecision(2) << client.AccountBalance;

    }

public:

	static void ShowTotalBalancesListScreen() {

        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        string subtitle = "\t\t       (" + to_string(vClients.size()) + ") Client(s)";
        _DrawScreenHeader("\t\t     Balances List Screen", subtitle);
        cout << "\t\t   _________________________________________________________________________________________\n";
        cout << "\t\t\t| " << left << setw(16) << "Account Number";
        cout << "| " << left << setw(49) << "Client Name";
        cout << "| " << left << setw(27) << "Balance ";
        cout << endl;
        cout << "\t\t   _________________________________________________________________________________________\n";
        cout << endl;
        if (vClients.size() == 0) {
            cout << "\t\t\t\tNo Clients Avalibale In The System!!!!!";
        }
        else {
            for (const clsBankClient& client : vClients) {
                _PrintOneClientRecordLineInBalanceList(client);
                cout << endl;
            }
        }

        cout << endl;
        cout << "\t\t   _________________________________________________________________________________________\n";
        double t = clsBankClient::GetTotalBalances();
        cout << "\t\t                                   Total Balances = " << t << endl;
        cout << "\t\t         " + clsUtil::ReturnTextNumber(t)<<endl;



	}


};

