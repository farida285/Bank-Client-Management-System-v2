#pragma once
#include "clsBankUser.h"
#include "clsUserInput.h"
#include "clsScreen.h"

class clsAddNewUserScreen : protected clsScreen
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

	static void ShowAddNewUserScreen() {

		_DrawScreenHeader("                Add New User Screen");

		string userName = clsUserInput::ReadNewUsername();

		clsBankUser u = clsBankUser::GetAddNewUser(userName);
		clsUserInput::ReadUserInfo(u);

		clsBankUser::enSaveResult result = u.Save();

		switch (result) {

		case clsBankUser::enSaveResult::svFaildEmptyObject :

			cout << "\nError User was not saved because it's Empty!!\n";
			break;

		case clsBankUser::enSaveResult::svFaildUserNameExist:

			cout << "\nError User was not saved because UserName is used!!\n";
			break;

		case clsBankUser::enSaveResult::svSucceeded:
			cout << "\nUser Addeded Successfully :-)\n\n";
			_PrintUserCard(u);
			break;

		}
	}



};

