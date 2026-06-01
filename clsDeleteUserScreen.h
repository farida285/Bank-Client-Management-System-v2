#pragma once
#include "clsBankUser.h"
#include "clsUserInput.h"
#include "clsScreen.h"

class clsDeleteUserScreen : protected clsScreen
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

	static void ShowDeleteUserScreen() {

		_DrawScreenHeader("               Delete User Screen");

		string userName = clsUserInput::ReadExistUsername();
		if (userName == "Admin") {
			cout << "Sorry, You can not delete Admin .\n\n";
		}
		else {
			clsBankUser u = clsBankUser::Find(userName);

			_PrintUserCard(u);

			if (clsInputValidate::YesOrNo("Are you sure you want delete this user ? Yes/No? ")) {
				if (u.Delete()) {
					_PrintUserCard(u);
					cout << "\n+++The User has been deleted successfully.+++\n\n";
				}
				else {
					cout << "\nError: User wan't deleted.\n\n";
				}
			}
		}


	}



};