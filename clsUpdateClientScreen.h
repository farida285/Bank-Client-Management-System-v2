#pragma once
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsClientInput.h"

class clsUpdateClientScreen : protected clsScreen {
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
    static void ShowUpdateClientScreen() {

        _DrawScreenHeader("\t            Update Client Screen");

        clsBankClient c1 = clsBankClient::Find(clsClientInput::ReadExistAccountNum());

        _PrintClientCard(c1);

        if (clsInputValidate::YesOrNo("Are you sure you want Update this client ? Yes/No ?")) {
            cout << endl;
            clsClientInput::ReadClientInfo(c1);
            clsBankClient::enSaveResult result = c1.Save();
            switch (result) {
            case clsBankClient::enSaveResult::svFaildEmptyObject:
                cout << "\nError account was not saved because it's Empty";
                break;
            case clsBankClient::enSaveResult::svSucceeded:
                cout << "\nThe client has been Updated successfully.\n\n";
                _PrintClientCard(c1);
                break;
            }
        }
    }
};