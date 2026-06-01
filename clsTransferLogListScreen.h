#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTransferLogListScreen :protected clsScreen {


private:
    static void _PrintOneClientRecordLineInList(const clsBankClient::stTransfer & t ) {
        cout << "\t| " << left << setw(20) << t.dateTime;
        cout << "| " << left << setw(15) << t.fromAccountNumber;
        cout << "| " << left << setw(15) << t.toAccountNumber;
        cout << "| " << left << setw(16) << fixed << setprecision(2) << t.transferAmount;
        cout << "| " << left << setw(16) << fixed << setprecision(2) << t.fromAccountBalance;
        cout << "| " << left << setw(16) << fixed << setprecision(2) << t.toAccountBalance;
        cout << "| " << left << setw(15) << t.userName;

    }
public:
	static void ShowTransferLogListScreen() {
        vector <clsBankClient::stTransfer> vTrans = clsBankClient::GetTransferList() ;

        string subtitle = "\t\t       (" + to_string(vTrans.size()) + ") Record(s)";

        _DrawScreenHeader("\t\t     Transfer Log Screen", subtitle);

        cout << "\t_________________________________________________________________________________________________________________________________\n\n";
        cout << "\t| " << left << setw(20) << "Date/Time";
        cout << "| " << left << setw(15) << "S.Acct";
        cout << "| " << left << setw(15) << "D.Acct";
        cout << "| " << left << setw(16) << "Amount";
        cout << "| " << left << setw(16) << "S.Balance";
        cout << "| " << left << setw(16) << "D.Balance";
        cout << "| " << left << setw(15) << "User";
        cout << endl;
        cout << "\t_________________________________________________________________________________________________________________________________\n";
        cout << endl;
        if (vTrans.size() == 0) {
            cout << "\t\t\t\t\tNo Transfers Avalibale In The System!!!!!";
        }
        else {
            for (const clsBankClient::stTransfer& t : vTrans) {
                _PrintOneClientRecordLineInList(t);
                cout << endl;
            }
        }
        cout << endl;
        cout << "\t_________________________________________________________________________________________________________________________________\n";

	}
};