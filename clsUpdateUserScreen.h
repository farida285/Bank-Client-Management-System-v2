#pragma once
#include "clsBankUser.h"
#include "clsUserInput.h"
#include "clsScreen.h"

class clsUpdateUserScreen : protected clsScreen {
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
public :
    static void ShowUpdateUserScreen() {

        _DrawScreenHeader("\t             Update User Screen");

        clsBankUser c1 = clsBankUser::Find(clsUserInput::ReadExistUsername());

        _PrintUserCard(c1);

        if (clsInputValidate::YesOrNo("Are you sure you want Update this User ? Yes/No ?")) {
            cout << endl;
            clsUserInput::ReadUserInfo(c1);
            clsBankUser::enSaveResult result = c1.Save();
            switch (result) {
            case clsBankUser::enSaveResult::svFaildEmptyObject:
                cout << "\nError account was not saved because it's Empty";
                break;
            case clsBankUser::enSaveResult::svSucceeded:
                cout << "\nThe User has been Updated successfully.\n\n";
                _PrintUserCard(c1);
                break;
            }
        }
    }
};