#pragma once
#include "clsScreen.h"
#include "clsCurrencyExchange.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
{

private:

    static void _PrintCurrencyCard(const clsCurrencyExchange& c) {

        cout << "\nCurrency Card:\n";
        cout << "_____________________________________\n";
        cout << "Country  : " << c.Country << endl;
        cout << "Code     : " << c.Code << endl;
        cout << "Name     : " << c.Name << endl;
        cout << "Rate(1$) : " << c.Rate << endl;
        cout << "_____________________________________\n";
        cout << endl;

    }

    static void _ShowResult(clsCurrencyExchange& c) {

        if (c.IsEmpty()) {

            cout << "\nCurrency Not Found :-(\n\n";
        }
        else {
            cout << "\nCurrency Found :-)\n";

            _PrintCurrencyCard(c);
        }

    }
public:

    static void  ShowFindCurrencyScreen() {

        _DrawScreenHeader("\t\t     Find Currency Screen");

        short userChoice =clsInputValidate::ReadPositiveShortNumberInRange("Find By: [1] Code or [2] Country ? ", "Invalid input! Please enter a valid number.\n", 1, 2);
        string search;

        if (userChoice == 1) {
            search = clsInputValidate::ReadStringFromUser("Please enter CurrencyCode : ");
            clsCurrencyExchange c = clsCurrencyExchange::FindByCode(search);
             _ShowResult(c);
        }
        else if (userChoice == 2) {

            search = clsInputValidate::ReadStringFromUser("Please enter Country : ");
            clsCurrencyExchange c = clsCurrencyExchange::FindByCountry(search);
            _ShowResult(c);
        }

   
        

    }




};