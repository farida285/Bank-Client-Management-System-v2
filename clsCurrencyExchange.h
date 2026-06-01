#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "StringLibrary.h"


class clsCurrencyExchange {


private:


	enum enMode { EmptyMode, UpdateMode };

	string _country;
	string _code;
	string _name;
	double _rate;

	enMode _mode;


	inline static string  _separator = "#//#";
	inline static string _CurrenciesFileName = "Currencies.txt";

	static clsCurrencyExchange _GetEmptyOpject() {
		return clsCurrencyExchange(enMode::EmptyMode, "", "", "", 0);
	}

	static clsCurrencyExchange _ConvertLineToObject(const string& line) {

		vector<string> v = clsString::SplitString(line, _separator);
		return clsCurrencyExchange(enMode::UpdateMode, v[0], v[1], v[2], stod(v[3]));

	}

	static string _ConvertObjectToLineRecord(clsCurrencyExchange c) {

		string s = c.Country + _separator;
		s += c.Code + _separator;
		s += c.Name + _separator;
		s += to_string(c.Rate);
		return s;


	}

	static void _SaveCurrenciesVectorInFile(const vector<clsCurrencyExchange>& v) {

		fstream file;

		file.open(_CurrenciesFileName, ios::out);
		if (file.is_open()) {
			for (const clsCurrencyExchange& c : v) {
				file << _ConvertObjectToLineRecord(c) << endl;
			}

			file.close();
		}

	}

	static vector<clsCurrencyExchange> _LoadCurrenciesVector() {

		fstream file;
		string line;
		vector<clsCurrencyExchange> v;

		file.open(_CurrenciesFileName, ios::in);
		if (file.is_open()) {

			while (getline(file, line)) {
				v.push_back(_ConvertLineToObject(line));
			}

			file.close();
		}

		return v;
	}

	void _Update() {
		vector<clsCurrencyExchange> v = _LoadCurrenciesVector();
		for (clsCurrencyExchange& c : v) {
			if (c.Country == _country) {
				c = *this;
				break;
			}
		}
		_SaveCurrenciesVectorInFile(v);
	}


	clsCurrencyExchange(enMode mode, string country, string code, string name, double rate) {
		_country = country;
		_code = code;
		_name = name;
		_rate = rate;
		_mode = mode;
	}

public:



	double GetRate() const {
		return _rate;
	}

	bool UpdateRate(double rate) {
		if(_mode==enMode::UpdateMode){
			_rate = rate;
			_Update();
			return true;
		}
		else {
			return false;
		}
	}

	__declspec(property(get = GetRate)) double Rate;

	string GetCountry() const {
		return _country;
	}
	__declspec(property(get = GetCountry)) string Country;


	string GetCode() const {
		return _code;
	}

	__declspec(property(get = GetCode)) string Code;

	string GetName() const {
		return _name;
	}
	__declspec(property(get = GetName)) string Name;


	static clsCurrencyExchange FindByCountry(string coun) {
		fstream file;
		string line;
		coun = clsString::LowerAllString(coun);

		file.open(_CurrenciesFileName, ios::in);
		if (file.is_open()) {

			while (getline(file, line)) {
				clsCurrencyExchange c = _ConvertLineToObject(line);

				if (clsString::LowerAllString(c.Country) == coun) {

					file.close();
					return c;
				}
			}

			file.close();
		}
		return _GetEmptyOpject();
	}

	static clsCurrencyExchange FindByCode(string code) {

		fstream file;
		string line;
		code = clsString::LowerAllString(code);

		file.open(_CurrenciesFileName, ios::in);
		if (file.is_open()) {

			while (getline(file, line)) {
				clsCurrencyExchange c = _ConvertLineToObject(line);

				if (clsString::LowerAllString(c.Code) == code) {

					file.close();
					return c;
				}
			}

			file.close();
		}
		return _GetEmptyOpject();
	}

	static vector<clsCurrencyExchange> GetCurrenciesList() {
		return _LoadCurrenciesVector();
	}

	bool IsEmpty() {
		return (_mode == enMode::EmptyMode);
	}

	static bool IsCurrencyExistByCountry(string country) {
		return (!FindByCountry(country).IsEmpty());
	}
	static bool IsCurrencyExistByCode(string code) {
		return (!FindByCode(code).IsEmpty());
	}
	
	double ConvertAmountToUSD( double amount) {
		if (this->IsEmpty() ) {
			return 0;
		}
		else {
			return (amount / _rate);
		}

	}
	double ConvertAmountToOtherCurrency( clsCurrencyExchange & to , double amount ) {
		if (this->IsEmpty() || to.IsEmpty()) {
			return 0;
		}
		else {
			return (ConvertAmountToUSD(amount) * to.Rate);
		}

	}


};