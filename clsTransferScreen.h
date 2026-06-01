#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsClientInput.h"


class clsTransferScreen : protected clsScreen {
private:
    static double _GetAmount(const string& message) {
        return clsClientInput::GetAmount(message);
    }
    static 	void _PrintClientCard(const clsBankClient& c) {
        cout << endl;
        cout << "The following are the client details :\n";
        cout << "----------------------------------------------------\n";
        cout << "Client Name     :" << c.FullName() << endl;
        cout << "Account Number  :" << c.AccountNumber << endl;
        cout << "Account Balance :" << fixed << setprecision(2) << c.AccountBalance << endl;
        cout << "----------------------------------------------------\n\n";

    }

public:

    static void ShowTransferScreen() {
        _DrawScreenHeader("                   Transfer Screen");
    
        string fromAccountNumber;
        string toAccountNumber;
        double amount;

        cout << "Please Enter Account Number to transfer from :\n";
        fromAccountNumber = clsClientInput::ReadExistAccountNum();
        clsBankClient from = clsBankClient::Find(fromAccountNumber);
        _PrintClientCard(from);
        
        do {
            cout << "Please Enter Account Number to transfer to :\n";
            toAccountNumber = clsClientInput::ReadExistAccountNum();
            if ((fromAccountNumber == toAccountNumber)) {
                cout << "\nIt's the same account number, Please try again.\n\n";
            }
        } while (fromAccountNumber == toAccountNumber);
        clsBankClient to = clsBankClient::Find(toAccountNumber);
        _PrintClientCard(to);
        

       
        do {
            amount = _GetAmount("Please enter transfer amount : ");
            if (amount > from.AccountBalance) {
                cout << "\nThis transfer amount is greater than the balance in this account, you can transfer up to : " << from.AccountBalance << endl;
            }
        } while (amount > from.AccountBalance);


        if (clsInputValidate::YesOrNo("Are you sure you want to perform this operation? (Yes/No)?    ")) {

            if (from.Transfer(amount,to))
            {
                    cout << "\nThe amount has been successfully transferred from "<<from.AccountNumber<<" to "<<to.AccountNumber<<" .\n";

            }
            else {
                cout << "\nError: The amount was not transferred from the account.\n";

            }
            _PrintClientCard(from);
            _PrintClientCard(to);

        }
        else {
            cout << "\nOperation was cancelled .\n\n";
        }
     

    }
};