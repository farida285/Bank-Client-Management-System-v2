#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsClientInput.h"


class clsWithdrawScreen : protected clsScreen {
private:
    static double _GetAmount(const string& message) {
        return clsClientInput::GetAmount(message);
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
        cout << "Account Balance :" << fixed << setprecision(2) << c.AccountBalance << endl << endl;

    }

public:

    static void ShowWithdrawScreen() {
        _DrawScreenHeader("                   Withdraw Screen");
        string accountNumber;
        accountNumber = clsClientInput::ReadExistAccountNum();
        clsBankClient c = clsBankClient::Find(accountNumber);
        _PrintClientCard(c);

        double amount;
        do {
            amount = _GetAmount("Please enter withdraw amount : ");
            if (amount > c.AccountBalance) {
                cout << "\nThis withdrawal amount is greater than the balance in this account, you can withdraw up to : " << c.AccountBalance << endl;
            }
        } while (amount > c.AccountBalance);
        if (clsInputValidate::YesOrNo("Are you sure you want to perform this transaction? (Yes/No)?    ")) {

            if (c.Withdraw(amount)) {
                cout << "\nThe amount has been successfully withdrawn from the account.\n";
                cout << "New Balance is : " << c.AccountBalance << endl;
            }
            else {
                cout << "\nError: The amount was not withdrawn from the account.\n";
                cout << "Your Balance is : " << c.AccountBalance << endl;
            }

        }
        else {
            cout << "\nOperation was cancelled .\n\n";
        }

    }
};