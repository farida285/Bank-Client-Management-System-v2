#pragma once
#include "clsScreen.h"
#include "clsCurrencyExchange.h"

class clsCurrenciesListScreen : protected clsScreen
{
public:

	static void  ShowCurrenciesListScreen() {

		vector <clsCurrencyExchange> v = clsCurrencyExchange::GetCurrenciesList() ;
		string subtitle = "\t\t       (" + to_string(v.size()) + ") Currency(ies)";
		_DrawScreenHeader("\t\t     Currencies List Screen", subtitle);
		
        cout << "\t______________________________________________________________________________________________________________\n";
        cout << "\t| " << left << setw(37) << "Country";
        cout << "| " << left << setw(5) << "Code";
        cout << "| " << left << setw(47) << "Name";
        cout << "| " << left << setw(15) << "Rate/(1$)";
        cout << endl;
        cout << "\t______________________________________________________________________________________________________________\n";
        cout << endl;
        if (v.size() == 0) {
            cout << "\t\t\t\tNo Currencies Avalibale In The System!!!!!";
        }
        else {
            for (const clsCurrencyExchange &c : v) {
                _PrintOneCurrencyRecordLineInList(c);
                cout << endl;
            }
        }

        cout << endl;
        cout << "\t______________________________________________________________________________________________________________\n";

	}


private:

    static void _PrintOneCurrencyRecordLineInList (const clsCurrencyExchange& c) {

        cout << "\t| " << left << setw(37) << c.Country;
        cout << "| " << left << setw(5) << c.Code;
        cout << "| " << left << setw(47) << c.Name;
        cout << "| " << left << setw(15) <<fixed<<setprecision(3)<< c.Rate;
        cout << endl;

    }

};
