#pragma once
#include "clsScreen.h"
#include "clsUserListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
class clsManageUsersScreen : protected clsScreen {
private:
    enum class enManageUsers { usersList = 1, addusers, deleteuser, updateuser, finduser, mainMenu };

    static enManageUsers _ReadManageUsersOption(const string& message, unsigned  short from = 0, unsigned  short to = numeric_limits<unsigned short>::max())
    {
        long long number;
        do {
            cout << "\t\t\t\t\t" << message;
            if (!(cin >> number))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\t\t\t\t\tInvalid input! Please enter a valid number.\n";
            }
            else if (number<from || number>to) {
                cout << "\t\t\t\t\tUnavailable number!!\n";
                cout << "\t\t\t\t\tEnter number in range from " << from << " to " << to << ".\n";
            }
            else {
                unsigned short n = static_cast<unsigned short>(number);

                return ((enManageUsers)n);
            }
        } while (true);

    }
    static void _ExecuteManageUsersOperation(enManageUsers operation) {
        system("cls");
        switch (operation)
        {
        case enManageUsers::usersList:
            _ShowUserList();
            break;
        case enManageUsers::addusers:
            _ShowAddNewUser();
            break;
        case enManageUsers::deleteuser:
            _ShowDeleteUser();
            break;
        case enManageUsers::updateuser:
            _ShowUpdateUser();
            break;
        case enManageUsers::finduser:
            _ShowFindUser();
            break;
        default:
            break;
        }
        cout << "Press any key to go back to Manage Users Screen...";
        system("pause > nul");

    }
    static void _ShowUserList() {
        clsUserListScreen::ShowUserListScreen();
    }
    static void _ShowAddNewUser() {

        clsAddNewUserScreen::ShowAddNewUserScreen();
    }
    static void _ShowUpdateUser() {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }
    static void  _ShowDeleteUser() {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }
    static void _ShowFindUser() {
        clsFindUserScreen::ShowFindUserScreen();
    }
 
public:
    static void ShowManageUsersScreen() {
        enManageUsers operation;
        do {
            system("cls");
            _DrawScreenHeader("                Manage Users Screen");
            cout << setw(37) << left << "" << "=================================================\n";
            cout << setw(37) << left << "" << "             Manage Users Menu Screen\n";
            cout << setw(37) << left << "" << "=================================================\n";
            cout << setw(37) << left << "" << "         [1] List Users.\n";
            cout << setw(37) << left << "" << "         [2] Add New Users.\n";
            cout << setw(37) << left << "" << "         [3] Delete User.\n";
            cout << setw(37) << left << "" << "         [4] Update User.\n";
            cout << setw(37) << left << "" << "         [5] Find User.\n";
            cout << setw(37) << left << "" << "         [6] Main Menu.\n";
            cout << setw(37) << left << "" << "=================================================\n";
        
            operation = _ReadManageUsersOption("Choose what do you want to do? [1 to 6]?  ", 1, 6);
            if (operation != enManageUsers::mainMenu)
                _ExecuteManageUsersOperation(operation);
        } while (operation != enManageUsers::mainMenu);
    }
};