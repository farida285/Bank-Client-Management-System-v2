#pragma once

#include "clsScreen.h"
#include "clsBankUser.h"

class clsLoginRegisterScreen : protected clsScreen {

private :

    static void _PrintOneLoginRegisterLineInList(const clsBankUser::stLoginRegisterRecord& user) {
        cout << "\t\t| " << left << setw(30) << user.RegisterTime;
        cout << "| " << left << setw(15) << user.UserName;
        cout << "| " << left << setw(10) << user.Password;
        cout << "| " << left << setw(9) << user.Permission;
    }


public :

	static void ShowLoginRegisterScreen() {
        vector <clsBankUser::stLoginRegisterRecord> vUsers = clsBankUser::GetLoginRegistersList();

        string subtitle = "\t\t       (" + to_string(vUsers.size()) + ") Users(s)";

        _DrawScreenHeader("\t\tLogin Registers List Screen", subtitle);

        cout << "\t\t_____________________________________________________________________________________________\n\n";
        cout << "\t\t| " << left << setw(30) << "Date/Time";
        cout << "| " << left << setw(15) << "UserName";
        cout << "| " << left << setw(9) << "Password";
        cout << "| " << left << setw(10) << "Permission";
        cout << endl;
        cout << "\t\t______________________________________________________________________________________________\n";
        cout << endl;
        if (vUsers.size() == 0) {
            cout << "\t\t\t\t\tNo Users Avalibale In The System!!!!!";
        }
        else {
            for (const clsBankUser::stLoginRegisterRecord& User : vUsers) {
                _PrintOneLoginRegisterLineInList(User);
                cout << endl;
            }
        }
        cout << endl;
        cout << "\t\t______________________________________________________________________________________________\n";


	}
};