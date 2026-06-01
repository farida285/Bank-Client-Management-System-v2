#pragma once
#include "clsScreen.h"
#include "clsCurrencyExchange.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
{

private:
    static void _AskAndUpdate(clsCurrencyExchange& c) {

        if (clsInputValidate::YesOrNo("Are you sure you want to update the rate of this Currency y/n?  ")) {

            if (c.UpdateRate(_ReadNewRate())) {
                cout << "\nCurrency rate updated successfully :-)\n\n";
                _PrintCurrencyCard(c);

            }
            else {
                cout << "\nError : Currency was not updated because it's Empty :-(\n\n";
            }
        }
    }
    static bool _ShowSearchResult(clsCurrencyExchange& c) {

        if (c.IsEmpty()) {

            cout << "\nCurrency Not Found :-(\n\n";
            return false;
        }
        else {
         
            _PrintCurrencyCard(c);
            return true;
        }

    }

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

    static double _ReadNewRate() {
        cout << "\nUpdate Currency Rate :\n";
        cout << "________________________\n";
        return (clsInputValidate::ReadPositiveDbleNumber("Enter New Rate : "));
    }
public:

    static void  ShowUpdateCurrencyRate() {

        _DrawScreenHeader("\t\t     Update Currency Screen");

        short userChoice = clsInputValidate::ReadPositiveShortNumberInRange("Find By: [1] Code or [2] Country ? ", "Invalid input! Please enter a valid number.\n", 1, 2);
        string search;

        if (userChoice == 1) {
            search = clsInputValidate::ReadStringFromUser("Please enter CurrencyCode : ");
            clsCurrencyExchange c = clsCurrencyExchange::FindByCode(search);
           if( _ShowSearchResult(c))
            _AskAndUpdate(c);
        }
        else if (userChoice == 2) {

            search = clsInputValidate::ReadStringFromUser("Please enter Country : ");
            clsCurrencyExchange c = clsCurrencyExchange::FindByCountry(search);
            if (_ShowSearchResult(c))
            _AskAndUpdate(c);
        }
       

    }




};