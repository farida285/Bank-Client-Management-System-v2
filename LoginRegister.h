#pragma once
#include "clsBankUser.h"
#include "DateLibrary.h"

class LoginRegister {
private:

	inline static string _LoginRegisterFileName = "LoginRegister.txt";
	inline static string _separator = "#//#";

	static string _ConverUserloginToLine(const clsBankUser& c1) {
		string s1 = clsDate().DateToString() + _separator;
		s1 += clsDate::NowTimeString() + _separator;
		s1 += c1.UserName + _separator;
		s1 += c1.Password + _separator;
		s1 += to_string(c1.Permission);
		return s1;
	}

	
	
public:

	static void Save(const clsBankUser& c1) {

		fstream file;
		file.open(_LoginRegisterFileName, ios::app | ios::out);

		if (file.is_open()) {
			file << _ConverUserloginToLine(c1) << endl;
		}
		file.close();

	}


};