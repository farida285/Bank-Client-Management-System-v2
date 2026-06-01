#pragma once
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsClientInput.h"

class clsDeleteClientScreen : clsScreen {
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
    static void ShowDeleteClientScreen() {

        _DrawScreenHeader("\t             Delete Client Screen");

        string accountNumber = clsClientInput::ReadExistAccountNum();

        clsBankClient c = clsBankClient::Find(accountNumber);

        _PrintClientCard(c);

        if (clsInputValidate::YesOrNo("Are you sure you want delete this client ? Yes/No ?")) {
            if (c.Delete()) {
                cout << "\n+++The client has been deleted successfully.+++\n\n";
                _PrintClientCard(c);

            }
            else {
                cout << "\nError: Client wan't deleted.\n\n";
            }

        }

    }

};