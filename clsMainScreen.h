#pragma once
#include "clsScreen.h"
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegistersScreen.h"
#include "clsCurrencyExchangeScreen.h"



class clsMainScreen : protected  clsScreen
{
private:

    enum class  enOperation { nothing, clientsList, addClients, deleteClient, updateClient, findClient, transaction, manageUsers, loginRegisterlist, currencyExchange,logout };

    static enOperation _ReadMainMenueOption(const string& message, unsigned  short from = 0, unsigned  short to = numeric_limits<unsigned short>::max())
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
                  
                    return ((enOperation)n);
                }
            } while (true);
        
    }

    static void _ShowConfirmLogoutScreen(enOperation& oper) {
        if (clsInputValidate::YesOrNo("Are you sure to logout ? Y/N ?   ")) {
            currentUser = clsBankUser::Find("", "");
        }
        else {
            oper = enOperation::nothing;
        }
    }

    static void _ShowClientListScreen() {
        clsClientsListScreen::ShowClientListScreen();
    }

    static void _ShowAddNewClientsScreen() {

        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen() {

     clsDeleteClientScreen::ShowDeleteClientScreen() ;
    }
    
    static void _ShowUpdateClientInfoScreen() {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void  _ShowFindClientScreen() {
        clsFindClientScreen::ShowFindClientScreen() ;
    }

    static void _ShowTransactionScreen() {
        clsTransactionScreen::ShowTransactionScreen();

    }

    static void _ShowManageUsersScreen() {
        clsManageUsersScreen::ShowManageUsersScreen();
    }

    static void _ShowLoginRegisterScreen() {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeScreen() {
        clsCurrencyExchangeScreen::ShowCurrencyExchangeScreen();
    }

    static void _ExecuteOperation(enOperation& oper) {


        system("cls");

        switch (oper)
        {
        case enOperation::logout:
            _ShowConfirmLogoutScreen(oper);
            break;
        case enOperation::loginRegisterlist:
            if (currentUser.CheckAccessPermission(clsBankUser::enPermission::loginRegisterlist)) {
                _ShowLoginRegisterScreen();
            }
            else {
                _DrawDeniedAccessScreen();
            }

            break;
        case  enOperation::clientsList:
            if (currentUser.CheckAccessPermission(clsBankUser::enPermission::clientsList)) {
                _ShowClientListScreen();
            }
            else {
                _DrawDeniedAccessScreen();
            }

            break;
        case enOperation::addClients:
            
            if (currentUser.CheckAccessPermission(clsBankUser::enPermission::addClients)) {
                _ShowAddNewClientsScreen();
            }
            else {
                _DrawDeniedAccessScreen();
            }
            break;
        case enOperation::deleteClient:

            if (currentUser.CheckAccessPermission(clsBankUser::enPermission::deleteClient)) {
                _ShowDeleteClientScreen();
            }
            else {
                _DrawDeniedAccessScreen();
            }

            break;
        case enOperation::updateClient:
            if (currentUser.CheckAccessPermission(clsBankUser::enPermission::updateClient)) {
                _ShowUpdateClientInfoScreen();
            }
            else {
                _DrawDeniedAccessScreen();
            }

            break;
        case enOperation::findClient:
            if (currentUser.CheckAccessPermission(clsBankUser::enPermission::findClient)) {
                _ShowFindClientScreen();
            }
            else {
                _DrawDeniedAccessScreen();
            }

            break;
        case enOperation::transaction:
            if (currentUser.CheckAccessPermission(clsBankUser::enPermission::transaction)) {
                _ShowTransactionScreen();
            }
            else {
                _DrawDeniedAccessScreen();
                cout << "\nPress any key to go back to main menu...";
                system("pause > nul");
            }

            break;
        case enOperation::manageUsers:
            if (currentUser.CheckAccessPermission(clsBankUser::enPermission::manageUsers)) {
                _ShowManageUsersScreen();
            }
            else {
                _DrawDeniedAccessScreen();
                cout << "\nPress any key to go back to main menu...";
                system("pause > nul");
            }


            break;
        case enOperation::currencyExchange :
            _ShowCurrencyExchangeScreen();
            
        default:
            break;
        }
        if (oper != enOperation::logout && oper != enOperation::transaction && oper != enOperation::manageUsers && oper!=enOperation::currencyExchange) {
            cout << "\nPress any key to go back to main menu...";
            system("pause > nul");
        }

    };



public:


	static void ShowMainMenu() {
        enOperation operationNumber;
        do {
            system("cls");
            _DrawScreenHeader("                    Main Screen");
            cout << setw(37) << left << "" << "=================================================\n";
            cout << setw(37) << left << "" << "                 Main Menu Screen\n";
            cout << setw(37) << left << "" << "=================================================\n";
            cout << setw(37) << left << "" << "         [1] Show Clients List.\n";
            cout << setw(37) << left << "" << "         [2] Add New Client.\n";
            cout << setw(37) << left << "" << "         [3] Delete Client.\n";
            cout << setw(37) << left << "" << "         [4] Update Client Info.\n";
            cout << setw(37) << left << "" << "         [5] Find Client.\n";
            cout << setw(37) << left << "" << "         [6] Transaction.\n";
            cout << setw(37) << left << "" << "         [7] Manage Users Menu.\n";
            cout << setw(37) << left << "" << "         [8] Show Login Register List.\n";
            cout << setw(37) << left << "" << "         [9] Currency Exchange.\n";
            cout << setw(37) << left << "" << "         [10] Logout.\n";
            cout << setw(37) << left << "" << "=================================================\n";
           
       
            operationNumber = _ReadMainMenueOption("Choose what do you want to do? [1 to 10]?  ",1, 10);
            _ExecuteOperation(operationNumber);
        } while (operationNumber != enOperation::logout);
	}

};

