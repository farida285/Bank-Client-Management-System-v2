#pragma once
#include "clsScreen.h"
#include "clsBankUser.h"
class clsUserListScreen : protected clsScreen
{

private:

    static void _PrintOneUserRecordLineInList(const  clsBankUser& client) {
        cout << "\t| " << left << setw(15) << client.UserName;
        cout << "| " << left << setw(30) << client.FullName();
        cout << "| " << left << setw(13) << client.PhoneNumber;
        cout << "| " << left << setw(20) << client.Email;
        cout << "| " << left << setw(9) << client.Password;
        cout << "| " << left << setw(10)  << client.Permission;

    }

public:

    static void ShowUserListScreen() {
        vector <clsBankUser> vUsers = clsBankUser::GetUsersList();

        string subtitle = "\t\t       (" + to_string(vUsers.size()) + ") Users(s)";

        _DrawScreenHeader("\t\t     Users List Screen", subtitle);

        cout << "\t_______________________________________________________________________________________________________________\n\n";
        cout << "\t| " << left << setw(15) << "UserName";
        cout << "| " << left << setw(30) << "FullName";
        cout << "| " << left << setw(13) << "Phone Number";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(9) << "Password";
        cout << "| " << left << setw(10) << "Permission";
        cout << endl;
        cout << "\t_______________________________________________________________________________________________________________\n";
        cout << endl;
        if (vUsers.size() == 0) {
            cout << "\t\t\t\t\tNo Users Avalibale In The System!!!!!";
        }
        else {
            for (const clsBankUser& User : vUsers) {
                _PrintOneUserRecordLineInList(User);
                cout << endl;
            }
        }
        cout << endl;
        cout << "\t_______________________________________________________________________________________________________________\n";


    }




};

