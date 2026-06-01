#pragma once
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "Global.h"


class clsLoginScreen : protected clsScreen {

private:

    static bool _LoadCurrentUser() {
        string userName;
        string Password;
        bool LoginFailed = false;
        short trials =  3;

             do {
                if (LoginFailed) {
                    trials--;
                    system("cls");

                    _DrawScreenHeader("                   Login Screen");
                    cout << "\t\t\t\t     Invalid Username/Password !!!\n";
                    cout << "\t\t\t\t     You have " << trials << " trial(s) to login.\n\n";
                    if (trials==0) {
                        cout << "\t\t\t\t     You are Locked after 3 failed trials.\n";
                    }
                }
                if (trials >= 1) {
                    userName = clsInputValidate::GetStringInSize(1, 40, "\t\t\t\t     Enter UserName : ", "\t\t\t\t     Writing this number of characters is not allowed. Please try entering the username again . \n");
                    Password = clsInputValidate::GetStringInSize(1, 40, "\t\t\t\t     Enter Password : ", "\t\t\t\t     Writing this number of characters is not allowed. Please try entering the password again .\n ");
                    currentUser = clsBankUser::Find(userName, Password);
                    if (currentUser.IsEmpty()) {
                        LoginFailed = true;
                    }
                    else {
                        return true;
                    }
               
                }

            } while (trials >= 1 && LoginFailed);
            return false;

    }

public:

	static bool ShowLoginScreen() {

        clsBankUser::EnsureAdminExistAndSetup();

        system("cls");
        _DrawScreenHeader("                   Login Screen");
        if (_LoadCurrentUser()) {
            currentUser.RegisterLogin();
            clsMainScreen::ShowMainMenu();
            return true;
        }
        else {
            return false;
        }
    
    }
};
