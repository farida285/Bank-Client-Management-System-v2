#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsTotalBalancesListScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogListScreen.h"

class clsTransactionScreen: protected clsScreen
{

private:
    enum class enTransactionOption { Deposit = 1, Withdraw=2, TotalBalancesList=3,Transfer=4, TransferLogList =5 , MainMenu=6 };
    static void _ExecuteTransactionOperation(const enTransactionOption& oper) {
        system("cls");
        switch (oper)
        {
        case  enTransactionOption::MainMenu:

            return;

        case enTransactionOption::Deposit:
            _ShowDepositScreen();
            break;
        case enTransactionOption::Withdraw:
            _ShowWithdrawScreen();
            break;
        case enTransactionOption::TotalBalancesList:
            _ShowTotalBalancesListScreen();
            break;

        case enTransactionOption::Transfer :
            _ShowTransferScreen();
            break;
        case enTransactionOption::TransferLogList:
            _ShowTransferLogListScreen();
            break;

        default:
            break;
        }
        cout << "Press any key to go back to Transaction Screen...";
        system("pause > nul");
    }
    static void _ShowDepositScreen() {
 
        clsDepositScreen::ShowDepositScreen();
  }
    static void _ShowWithdrawScreen() {
        clsWithdrawScreen::ShowWithdrawScreen();
    }
    static void _ShowTotalBalancesListScreen() {
        clsTotalBalancesListScreen::ShowTotalBalancesListScreen();
    }
    static void _ShowTransferScreen() {
        clsTransferScreen::ShowTransferScreen();

    }
    static void  _ShowTransferLogListScreen() {
        clsTransferLogListScreen::ShowTransferLogListScreen();

    }

    static enTransactionOption _ReadTransactionOption(const string& message, unsigned  short from = 0, unsigned  short to = numeric_limits<unsigned short>::max())
    {
        long long number;
        do {
            cout <<"\t\t\t\t\t" << message;
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

                return ((enTransactionOption)n);
            }
        } while (true);

    }

public:

	static void ShowTransactionScreen()
    {
        
        enTransactionOption operationNumber;
        do {
            system("cls");
            _DrawScreenHeader("             Transaction Menu Screen");
            cout << setw(37) << left << "" << "=================================================\n";
            cout << setw(37) << left << "" << "             Transaction Menu Screen\n";
            cout << setw(37) << left << "" << "=================================================\n";
            cout << setw(37) << left << "" << "         [1] Deposit.\n";
            cout << setw(37) << left << "" << "         [2] Withdraw.\n";
            cout << setw(37) << left << "" << "         [3] Total Balances.\n";
            cout << setw(37) << left << "" << "         [4] Transfer.\n";
            cout << setw(37) << left << "" << "         [5] Transfer Log List.\n";
            cout << setw(37) << left << "" << "         [6] Main Menu.\n";
            cout << setw(37) << left << "" << "=================================================\n";
            operationNumber = _ReadTransactionOption("Choose what do you want to do? [1 to 6]?",  1, 6);
            if (operationNumber != enTransactionOption::MainMenu) {
                _ExecuteTransactionOperation(operationNumber);
            }
        } while (operationNumber != enTransactionOption::MainMenu);

	}



};

