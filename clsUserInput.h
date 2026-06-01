#pragma once
#include "clsBankInputs.h"
#include "clsInputValidate.h"
#include "clsBankUser.h"
class clsUserInput :protected clsBankInputs {


private:
    static short _ReadPermission() {
        short calcpermission = 0;
        if (clsInputValidate::YesOrNo("Do you want to give full access ? ")) {
            calcpermission = (short)clsBankUser::enPermission::all;
        }
        else {
            cout << "Do you Want to give access to :\n";
            calcpermission += (clsInputValidate::YesOrNo("Show Client List ? ")) ? (short) clsBankUser::enPermission::clientsList : 0;
            calcpermission += (clsInputValidate::YesOrNo("Add New Clients ? ")) ? (short)clsBankUser::enPermission::addClients : 0;
            calcpermission += (clsInputValidate::YesOrNo("Delete Client ? ")) ? (short)clsBankUser::enPermission::deleteClient : 0;
            calcpermission += (clsInputValidate::YesOrNo("Update Client ? ")) ? (short)clsBankUser::enPermission::updateClient : 0;
            calcpermission += (clsInputValidate::YesOrNo("Find Client ? ")) ? (short)clsBankUser::enPermission::findClient : 0;
            calcpermission += (clsInputValidate::YesOrNo("Transactions ? ")) ? (short)clsBankUser::enPermission::transaction : 0;
            calcpermission += (clsInputValidate::YesOrNo("Manage Users ? ")) ? (short)clsBankUser::enPermission::manageUsers : 0;
            calcpermission += (clsInputValidate::YesOrNo("Login Register List ? ")) ? (short)clsBankUser::enPermission::loginRegisterlist : 0;
        }
        return calcpermission;

    }
public:

    static string ReadNewUsername() {

        string userName;

       while(true) {
            userName= clsInputValidate::GetStringInSize(1, 10, "Please enter UserName:", "Enter from 1 to 10 Charcter maximum :");
            if (clsBankUser::IsUserExist(userName)) {
                cout << "User with [" << userName << "] already exist, Try again with another.\n";
            }
            else {
                return userName;
            }
        }
    }

    static string ReadExistUsername() {
        string userName;

        while (true) {
            userName = clsInputValidate::GetStringInSize(1, 40, "Please enter UserName:", "Writing this number of characters is not allowed. Please try entering the username again . \n");
            if (clsBankUser::IsUserExist(userName)) {
                return userName;
            }
            else {
                cout << "\nUser with Account Number [" << userName << "] is Not Found.\n\n";
            }
        }
    }

    static void ReadUserInfo(clsBankUser & u) {
        u.FirstName = clsBankInputs::_GetName("Enter First Name: ");
        u.LastName = clsBankInputs::_GetName("Enter Last Name: ");
        u.PhoneNumber = _GetPhoneNumber("Enter Phone Number: ", 11);
        u.Email = _GetEmail("Enter Email: ");
        u.Password = to_string(clsInputValidate::ReadPositiveShortNumberInRange("Enter Password: ", "Invalid input! Please enter a valid number.\n", 1000, 9999));
        u.Permission = _ReadPermission();


    }

};