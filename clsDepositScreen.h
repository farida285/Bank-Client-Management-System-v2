#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsClientInput.h"


class clsDepositScreen : protected clsScreen {
private :
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
	
 static void ShowDepositScreen() {
     _DrawScreenHeader("                   Deposite Screen");


 string accountNumber;
     accountNumber = clsClientInput::ReadExistAccountNum();
     clsBankClient c = clsBankClient::Find(accountNumber);
     _PrintClientCard(c);

     double amount = _GetAmount("Please enter deposit amount : ");

     if (clsInputValidate:: YesOrNo("Are you sure you want to perform this transaction? (Yes/No)?    ")) {

         if (c.Deposit(amount)) {
             cout << "\nThe amount has been successfully added to the account.\n";
             cout << "New Balance is : " << c.AccountBalance<<endl;
         }
         else {
             cout << "\nError : The amount was not added to the account.\n";
         }
    
     }
     else {
         cout << "\nOperation was cancelled .\n\n";
     }
 
 }
};