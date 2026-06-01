#pragma once
#include "clsBankUser.h"
#include "clsScreen.h"
#include "clsUserInput.h"

class clsFindUserScreen : protected clsScreen
{

private:
    static void _PrintUserCard(const clsBankUser& user) {
        cout << "\nUser Card :\n";
        cout << "-------------------------------------\n";
        cout << "First Name   : " << user.FirstName << endl;
        cout << "Last Name    : " << user.LastName << endl;
        cout << "User Name    : " << user.FullName() << endl;
        cout << "Phone Number : " << user.PhoneNumber << endl;
        cout << "Email        : " << user.Email << endl;
        cout << "User Name    : " << user.UserName << endl;
        cout << "Password     : " << user.Password << endl;
        cout << "Permission   : " << user.Permission << endl;
        cout << "-------------------------------------\n\n";
    }

public:

	static void    ShowFindUserScreen() {

		_DrawScreenHeader("\t\t     Find User Screen");

		string userName =clsUserInput::ReadExistUsername();
		clsBankUser c = clsBankUser::Find(userName);
		if (c.IsEmpty()) {
            cout << "User was not found :-(\n";
		}
		else {
			
            cout << "User is found :-)\n";
		}
		_PrintUserCard(c);
	}


};