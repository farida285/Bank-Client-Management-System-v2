#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "ClsPerson.h"
#include "StringLibrary.h"
using namespace std;
class clsBankUser : public clsPerson
{
private:

	enum enMode { EmptyMode, UpdateMode, AddNewMode,LoginRegister };
	enMode _mode;
	string _userName;
	string _password;
	short _permission;
	bool _markedForDelete = false;

	inline static string _separator = "#//#";
	inline static string _UsersFileName = "Users.txt";
	inline static string _LoginRegisterFileName = "LoginRegister.txt";

	static clsBankUser _ConvertLineToRecord(const string& s, const string& separator) {
		vector <string> split = clsString::SplitString(s, separator);

		return clsBankUser(enMode::UpdateMode, split[0], split[1], split[2], split[3], split[4], clsString::DecryptString(split[5],5), (short)stoi(split[6]));
	}

	static string _ConverUserObjectToLine(const clsBankUser& c1) {
		string s1 = c1.FirstName + _separator;
		s1 += c1.LastName + _separator;
		s1 += c1.Email + _separator;
		s1 += c1.PhoneNumber + _separator;
		s1 += c1.UserName + _separator;
		s1 += clsString::EncryptString(c1.Password,5) + _separator;
		s1 += to_string(c1.Permission);
		return s1;
	}

	 static clsBankUser _GetDefaultAdmin() {
		return clsBankUser(enMode::UpdateMode, "-", "-", "-@gmailcom", "00000000000", "Admin", "1111", -1);
	}
		
	static bool _IsAdminInUsersList (const vector <clsBankUser>& users) {
		if (users.size() > 0) {
			for (const clsBankUser& user : users) {
				if (user.UserName == "Admin") {
					return true;
				}
			}
		}
		return false;
	}

	static vector <clsBankUser> _LoadUsersDataFromFile() {
		fstream file;
		string line;
		vector <clsBankUser> vUsers;
		file.open(_UsersFileName, ios::in);
		if (file.is_open()) {
			while (getline(file, line))
			{
				vUsers.push_back(_ConvertLineToRecord(line, _separator));
			}
			file.close();
		}
		return vUsers;
	}

	static void _SaveUnMarkedVUsersInFile(const vector <clsBankUser>& vUsers) {
		fstream file;
		file.open(_UsersFileName, ios::out);
		if (file.is_open()) {
			for (const clsBankUser& c1 : vUsers) {
				if (c1._markedForDelete == false) {
					file << _ConverUserObjectToLine(c1) << endl;
				}

			}
			file.close();
		}
	}


	 string _PrepareloginRecord() {
	
	    string s1 = clsDate::GetDateSystemTimeString() + _separator;
		s1 += _userName + _separator;
		s1 += clsString::EncryptString(_password,5)+_separator;
		s1 += to_string(_permission);
		return s1;
	}

	struct stLoginRegisterRecord;
	static stLoginRegisterRecord   _ConvertLineTostRegisterRecord(const string &line) {
		vector<string> user = clsString::SplitString(line, _separator);
		clsBankUser::stLoginRegisterRecord u ;

		u.RegisterTime = user[0];
		u.UserName = user[1];
		u.Password =clsString::DecryptString(user[2] ,5);
		u.Permission = stoi(user[3]);

		return u;
	}




	static clsBankUser _GetEmptyUser() {
		return clsBankUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsBankUser _FindUser(string UserName, bool withPassword, string pinCode = "") {

		fstream file;
		string line;
		file.open(_UsersFileName, ios::in);
		if (file.is_open()) {
			while (getline(file, line))
			{
				clsBankUser c = _ConvertLineToRecord(line, _separator);
				if ((c.UserName == UserName) && (!withPassword || c.Password == pinCode)) {
					file.close();
					return c;
				}
			}
			file.close();
		}
		return  _GetEmptyUser();
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open(_UsersFileName, ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	void _Update() {
		vector <clsBankUser> Users = _LoadUsersDataFromFile();
		for (clsBankUser& c : Users) {
			if (c.UserName == UserName) {
				c = *this;
				break;
			}
		}
		_SaveUnMarkedVUsersInFile(Users);
	}


	void _AddNew()
	{

		_AddDataLineToFile(_ConverUserObjectToLine(*this));
	}


public:

	clsBankUser(enMode mode, string firstName, string lastName, string email, string phoneNumber, string UserName, string password,int permission)
		: clsPerson(firstName, lastName, email, phoneNumber) {

		_mode = mode;
		_userName = UserName;
		_password = password;
		_permission = permission;


	}

	void SetPermission(short permission) {
		_permission = permission;
	}

	short GetPermission()const {
		return _permission;
	}

	__declspec(property(get = GetPermission, put = SetPermission)) short Permission;


	string GetUserName()const {
		return _userName;
	}

	__declspec(property(get = GetUserName)) string UserName;

	void SetPassword(string password) {
		_password = password;
	}

	string GetPassword()const {
		return _password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	 struct stLoginRegisterRecord {
		string UserName;
		string Password;
		short  Permission;
		string RegisterTime;
	};

	bool IsEmpty() {
		return (_mode == enMode::EmptyMode);
	}

	static clsBankUser GetAddNewUser(string UserName) {

		return clsBankUser(AddNewMode, "", "", "", "", UserName, "", 0);
	}
	static clsBankUser Find(string UserName) {
		return _FindUser(UserName, 0);
	}

	static clsBankUser Find(string UserName, string password) {
		return _FindUser(UserName, 1, password);
	}


	static bool IsUserExist(string UserName) {
		return !(Find(UserName).IsEmpty());
	}

	enum enSaveResult { svFaildEmptyObject, svFaildUserNameExist, svSucceeded };

	enSaveResult Save() {
		switch (_mode) {
		case EmptyMode:
			return svFaildEmptyObject;

		case UpdateMode:
			_Update();
			return svSucceeded;

		case AddNewMode:
			if (clsBankUser::IsUserExist(UserName)) {
				return svFaildUserNameExist;
			}
			else {
				_AddNew();
				_mode = enMode::UpdateMode;
				return svSucceeded;
			}

		}
	}
	bool Delete() {
		if (_mode == EmptyMode || _mode == AddNewMode||_userName=="Admin") {
			return false;
		}

		vector <clsBankUser> vUsers = _LoadUsersDataFromFile();
		for (clsBankUser& c1 : vUsers) {
			if (c1.UserName == this->UserName) {
				c1._markedForDelete = true;
				_SaveUnMarkedVUsersInFile(vUsers);
				*this = _GetEmptyUser();
				return true;
			}
		}
		return false;


	}

	static vector<clsBankUser> GetUsersList() {
		return _LoadUsersDataFromFile();
	}
	
	

	static void EnsureAdminExistAndSetup() {
		vector<clsBankUser> users = _LoadUsersDataFromFile();
		if (!_IsAdminInUsersList(users)) {
			users.insert(users.begin(), _GetDefaultAdmin());
			_SaveUnMarkedVUsersInFile(users);
		}

	}

	enum class enPermission { all=-1,clientsList = 1, addClients = 2, deleteClient = 4, updateClient = 8, findClient = 16, transaction = 32, manageUsers = 64, loginRegisterlist=128};

	bool CheckAccessPermission(enPermission permission) {
		if (_permission == -1) {
			return true;
		}
		if ((_permission & ((short)permission)) == ((short)permission)) {
			return true;
		}
		else {
			return false;
		}
	}

	 void RegisterLogin() {

		fstream file;
		file.open(_LoginRegisterFileName, ios::app | ios::out);

		if (file.is_open()) {
			file << _PrepareloginRecord() << endl;
			file.close();
		}
		

	}
	
	 static vector <stLoginRegisterRecord> GetLoginRegistersList() {
		 fstream file;
		 string line;
		 vector <stLoginRegisterRecord> vUsers;
		 file.open(_LoginRegisterFileName, ios::in);
		 if (file.is_open()) {
			 while (getline(file, line))
			 {
				 vUsers.push_back(_ConvertLineTostRegisterRecord(line));
			 }
			 file.close();
		 }
		 return vUsers;
	 }



};

