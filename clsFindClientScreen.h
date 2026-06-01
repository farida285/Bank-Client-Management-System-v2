#pragma once
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsFindClientScreen : protected clsScreen
{

private:

	static string _ReadExistAccountNum() {
		while (true) {

			string accountNumber = clsInputValidate::GetStringInSize(1, 4, "Please enter Account Number:", "Enter from 1 to 4 Charcter:");

			if (!clsBankClient::IsClientExist(accountNumber))
			{
				cout << "\nClient with Account Number [" << accountNumber << "] is Not Found.\n\n";
			}
			else {
				return accountNumber;
			}
		}
	}
	static 	void _PrintClientCard(const clsBankClient& c) {
		cout << endl;
		cout << "The following are the client details :\n";
		cout << "First Name      :" << c.FirstName << endl;
		cout << "Last Name       :" << c.LastName << endl;
		cout << "Client Name     :" << c.FullName() << endl;
		cout << "Phone Number    :" << c.PhoneNumber << endl;
		cout << "Email           :" << c.Email << endl;
		cout << "Account Number  :" << c.AccountNumber << endl;
		cout << "PinCode         :" << c.PinCode << endl;
		cout << "Account Balance :" << fixed << setprecision(2) << c.AccountBalance << endl << endl;;

	}

public:

	static void    ShowFindClientScreen() {

		_DrawScreenHeader("\t\t     Find Client Screen");

		string accountNumber = _ReadExistAccountNum();
		clsBankClient c = clsBankClient::Find(accountNumber);
		if (!c.IsEmpty()) {
			cout << "Client is found :-)\n";
		}
		else {
			cout << "Client was not found :-(\n";
		}
		_PrintClientCard(c);
	}


};

