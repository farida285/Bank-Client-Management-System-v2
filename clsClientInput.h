#pragma once
#include "clsBankInputs.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
class clsClientInput : protected clsBankInputs
{
public:
    static double GetAmount(const string& message) {
        double amount;
        do {
            amount =clsInputValidate::ReadPositiveDbleNumber(message);
            if (amount == 0) {
                cout << "\nPlease enter a amount greater than zero.\n";
            }
        } while (amount == 0);
        return amount;
    }
    static void ReadClientInfo (clsBankClient &c1) {
        
       
        c1.FirstName = clsBankInputs::_GetName("Enter First Name: ");
        c1.LastName = clsBankInputs::_GetName("Enter Last Name: ");
        c1.PhoneNumber = _GetPhoneNumber("Enter Phone Number: ", 11);
        c1.Email = clsBankInputs::_GetEmail("Enter Email: ");
        c1.PinCode = to_string(clsInputValidate::ReadPositiveShortNumberInRange("Enter Pin Code: ", "Invalid input! Please enter a valid number.\n", 1000, 9999));
        c1.AccountBalance = clsInputValidate::ReadPositiveDbleNumber("Enter Account Balance: ");

      
    }

    static string ReadExistAccountNum() {
        while (true) {

            string accountNumber = clsInputValidate::GetStringInSize(1, 40, "Please enter Account Number:", " Writing this number of characters is not allowed. Please try entering the username again .\n");

            if (!clsBankClient::IsClientExist(accountNumber))
            {
                cout << "\nClient with Account Number [" << accountNumber << "] is Not Found.\n\n";
            }
            else {
                return accountNumber;
            }
        }
    }

    static string ReadNewAccountNumber() {
        string accountNumber;
        while(true) {
            accountNumber =clsInputValidate:: GetStringInSize( 1, 15, "Please enter Account Number:", "Please try again, as the maximum number of characters for the username is 15. \n");
            if ( clsBankClient::IsClientExist(accountNumber)) {
                cout << "\nClient with [" << accountNumber << "] is already exists.\n\n";
            }
            else {
                return accountNumber;
            }
        } 
    }
private:

    


};
