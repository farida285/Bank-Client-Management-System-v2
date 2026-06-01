#pragma once
#include "clsScreen.h"
#include "clsCurrencyExchange.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"


class clsCurrencyExchangeScreen : protected clsScreen
{

private:

    enum enCurrencyOptions { CurrenciesList =1 , FindCurrency=2, UpdateCurrencyRate=3, CurrencyCalculator=4,MainMenu=5};

    static enCurrencyOptions _ReadCurrencyOption(const string& message, unsigned  short from = 0, unsigned  short to = numeric_limits<unsigned short>::max())
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

                return ((enCurrencyOptions)n);
            }
        } while (true);

    }

    static void _ExecuteCurrencyOperation(enCurrencyOptions option) {
        system("cls");

        switch (option) {

        case enCurrencyOptions::MainMenu:

            return;

        case enCurrencyOptions::CurrenciesList:
            _ShowCurrenciesListScreen();
            break;

        case enCurrencyOptions::FindCurrency:
            _ShowFindCurrencyScreen();
              break;


        case enCurrencyOptions::UpdateCurrencyRate:
            _ShowUpdateCurrencyRateScreen();
                break;


        case enCurrencyOptions::CurrencyCalculator:
            _ShowCurrencyCalculatorScreen();
                break;

        default :

            break;


        }

        cout << "\nPress any key to go back to currency exchange menu...";
        system("pause > nul");




    }

    static void _ShowCurrenciesListScreen() {

        clsCurrenciesListScreen::ShowCurrenciesListScreen();

    }

    static void _ShowFindCurrencyScreen() {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }
    static void _ShowUpdateCurrencyRateScreen() {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRate();

    }
    static void _ShowCurrencyCalculatorScreen() {
        clsCurrencyCalculatorScreen::showCurrencyCalculator();

    }

public:

	static void ShowCurrencyExchangeScreen() {
        enCurrencyOptions option;
	do{
        system("cls");

		 _DrawScreenHeader("          Currency Exchange Menu Screen");
         cout << setw(37) << left << "" << "=================================================\n";
         cout << setw(37) << left << "" << "                 Currency Exchange Menu\n";
         cout << setw(37) << left << "" << "=================================================\n";
         cout << setw(37) << left << "" << "         [1] Currencies List.\n";
         cout << setw(37) << left << "" << "         [2] Find Currency.\n";
         cout << setw(37) << left << "" << "         [3] Update Currency Rate.\n";
         cout << setw(37) << left << "" << "         [4] Currency Calculator.\n"; 
         cout << setw(37) << left << "" << "         [5] Main Menu.\n"; 
         cout << setw(37) << left << "" << "=================================================\n";

         option = _ReadCurrencyOption("Choose what do you want to do? [1 to 5]?  ", 1, 5);
         if (option != enCurrencyOptions::MainMenu) {

             _ExecuteCurrencyOperation(option);
             
         }
    } while (option != enCurrencyOptions::MainMenu);

	}

};