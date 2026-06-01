#pragma once
#include "clsScreen.h"
#include "clsCurrencyExchange.h"
#include "clsInputValidate.h"

class clsCurrencyCalculatorScreen : protected clsScreen {
private:
    static void _PrintCurrencyCard(const clsCurrencyExchange& c) {

        cout << "\n";
        cout << "_____________________________________\n";
        cout << "Country  : " << c.Country << endl;
        cout << "Code     : " << c.Code << endl;
        cout << "Name     : " << c.Name << endl;
        cout << "Rate(1$) : " << c.Rate << endl;
        cout << "_____________________________________\n";
        cout << endl;

    }


    static double _GetAmount(const string& message) {
        double amount;
        do {
            amount = clsInputValidate::ReadPositiveDbleNumber(message);
            if (amount == 0) {
                cout << "\nPlease enter a amount greater than zero.\n";
            }
        } while (amount == 0);
        return amount;
    }

public:
	 

	static void showCurrencyCalculator() {

        string code1, code2;
        do{
            system("cls");

            _DrawScreenHeader("\t\tCurrency Calculator Screen");

            code1 = clsInputValidate::ReadStringFromUser("Enter the currency code you want to convert from :  ");
            clsCurrencyExchange c1 = clsCurrencyExchange::FindByCode(code1);

            code2 = clsInputValidate::ReadStringFromUser("Enter the currency code you want to convert to :  ");
            clsCurrencyExchange c2 = clsCurrencyExchange::FindByCode(code2);

            double amount = _GetAmount("Enter Amount to exchange : ");

            if (c1.IsEmpty() || c2.IsEmpty()) {

                if (c1.IsEmpty())
                    cout << "\nCurrency you want to convert from Not Found :-(\n\n";
                if (c2.IsEmpty())
                    cout << "\nCurrency you want to convert to Not Found :-(\n\n";

            }
            else {

                cout << "\nConvert From :\n";
                _PrintCurrencyCard(c1);

                cout << "Convert To :\n";
                _PrintCurrencyCard(c2);

                cout << amount << " " + c1.Code + " = " << c1.ConvertAmountToOtherCurrency(c2, amount) << " " << c2.Code << endl << endl;



            }
        } while (clsInputValidate::YesOrNo("Do you want to perform another calculation ? Y/N ? "));
            
	}
};