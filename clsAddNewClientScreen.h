#pragma once
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientInput.h"


class clsAddNewClientScreen : protected clsScreen
{
private:
  
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
        cout << "Account Balance :" << fixed << setprecision(2) << c.AccountBalance << endl << endl;

    }

public:

	static void ShowAddNewClientScreen() {
    
        _DrawScreenHeader("\t           Add New Client Screen\n");
        string newAccountNumber = clsClientInput::ReadNewAccountNumber();

        clsBankClient c = clsBankClient::GetAddNewClient(newAccountNumber);

        clsClientInput::ReadClientInfo(c); 

        clsBankClient::enSaveResult saveResult = c.Save();

        switch (saveResult)
        {
        case  clsBankClient::enSaveResult::svSucceeded:
        {
            cout << "\nAccount Addeded Successfully :-)\n";
            _PrintClientCard(c);
            break;
        }
        case clsBankClient::enSaveResult::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty\n";
            break;

        }
        case clsBankClient::enSaveResult::svFaildAccountNumberExist:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;

        }
        }



	}

};