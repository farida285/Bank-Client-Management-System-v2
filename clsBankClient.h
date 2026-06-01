#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "ClsPerson.h"
#include "StringLibrary.h"
using namespace std;
class clsBankClient : public clsPerson
{
private:

	enum enMode {EmptyMode,UpdateMode,AddNewMode};
	enMode _mode;
	double _accountBalance;
	string _accountNumber;
	string _pinCode;
	bool _markedForDelete = false;

	inline static string _separator = "#//#";
	inline static string _clientsFileName = "Clients.txt";
	inline static string _TransfersFileName = "Transfers.txt";


	static clsBankClient _ConvertLineToRecord(const string& s, const string& separator) {
		vector <string> split = clsString::SplitString(s, separator);
		return clsBankClient(enMode::UpdateMode, split[0], split[1], split[2], split[3], split[4], clsString::DecryptString(split[5],5), stod(split[6]));
	}
	 
	static string _ConverClientObjectToLine(const clsBankClient& c1) {
		string s1 = c1.FirstName + _separator;
		s1 += c1.LastName + _separator;
		s1 += c1.Email + _separator;
		s1 += c1.PhoneNumber + _separator;
		s1 += c1.AccountNumber + _separator;
		s1 += clsString::EncryptString(c1.PinCode,5) + _separator;
		s1 += to_string(c1.AccountBalance);
		return s1;
	}

	static vector <clsBankClient> _LoadclientsDataFromFile() {
		fstream file;
		string line;
		vector <clsBankClient> vClients;
		file.open(_clientsFileName, ios::in);
		if (file.is_open()) {
			while (getline(file, line))
			{
				vClients.push_back(_ConvertLineToRecord(line, _separator));
			}
			file.close();
		}
		return vClients;
	}

	static void _SaveUnMarkedVClientsInFile(const vector <clsBankClient>& vClients) {
		fstream file;
		file.open(_clientsFileName, ios::out);
		if (file.is_open()) {
			for (const clsBankClient & c1 : vClients) {		
				if (c1._markedForDelete == false) {
					file << _ConverClientObjectToLine(c1) << endl;
				}
					
			}
			file.close();
		}
	}
	
	static clsBankClient _GetEmptyClient() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsBankClient _FindClient(string accountNumber,bool withPinCode , string pinCode="") {

		fstream file;
		string line;
		file.open(_clientsFileName, ios::in);
		if (file.is_open()) {
			while (getline(file, line))
			{
				clsBankClient c = _ConvertLineToRecord(line, _separator);
				if ((c.AccountNumber == accountNumber)&&(!withPinCode||c.PinCode==pinCode)) {
					file.close();
					return c;
				}
			}
			file.close();
		}
		return  _GetEmptyClient();
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open(_clientsFileName, ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	void _Update() {
		vector <clsBankClient> clients = _LoadclientsDataFromFile();
		for (clsBankClient& c : clients) {
			if (c.AccountNumber == AccountNumber) {
				c = *this;
				break;
			}
		}
		_SaveUnMarkedVClientsInFile(clients);
	}

	
	void _AddNew()
	{

		_AddDataLineToFile(_ConverClientObjectToLine(*this));
	}
	struct stTransfer;

	static stTransfer _convertLintToStTransferRecord(const string& s) {
		vector <string> v = clsString::SplitString(s,_separator);

		stTransfer st;
		st.dateTime = v[0];
		st.fromAccountNumber = v[1];
		st.toAccountNumber = v[2];
		st.transferAmount = stod(v[3]);
		st.fromAccountBalance = stod(v[4]);
		st.toAccountBalance = stod(v[5]);
		st.userName = v[6];

		return st;
		

	}

	 string _prepareTransferRecordLine(double amount,const clsBankClient& to) {
		string s1 = clsDate::GetDateSystemTimeString() + _separator;
		s1 += _accountNumber + _separator;
		s1 += to.AccountNumber + _separator;
		s1 += to_string(amount) + _separator;
		s1 += to_string(_accountBalance) + _separator; 
		s1 += to_string(to.AccountBalance) + _separator; 
		s1 += currentUser.UserName; 

		return s1;

	}

public:

	struct stTransfer {
		string dateTime;
		string fromAccountNumber;
		string toAccountNumber;
		double transferAmount;
		double fromAccountBalance;
		double toAccountBalance;
		string userName;
	};

	clsBankClient(enMode mode,string firstName, string lastName, string email, string phoneNumber, string accountNumber, string pinCode, double balance)
		: clsPerson(firstName, lastName, email, phoneNumber) {

		_mode=mode;
		 _accountBalance=balance;
		 _accountNumber=accountNumber;
		 _pinCode=pinCode;
		 

	}

	void SetAccountBalance(double balance) {
		_accountBalance = balance;
	}

	double GetAccountBalance()const {
		return _accountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;


	string GetAccountNumber()const {
		return _accountNumber;
	}

	__declspec(property(get = GetAccountNumber)) string AccountNumber;

	void SetPinCode(string pinCode) {
		_pinCode = pinCode;
	}

	string GetPinCode()const {
		return _pinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	bool IsEmpty() {
		return (_mode == enMode::EmptyMode);
	}

	static clsBankClient GetAddNewClient (string accountNumber) {

		return clsBankClient(AddNewMode, "", "", "", "", accountNumber, "", 0);
	}
	static clsBankClient Find(string accountNumber) {
		return _FindClient(accountNumber, 0);
	}

	static clsBankClient Find(string accountNumber, string pinCode) {
		return _FindClient(accountNumber, 1, pinCode);
	}


	static bool IsClientExist(string accountNumber) {
		return !(Find(accountNumber).IsEmpty());
	}

	enum enSaveResult { svFaildEmptyObject , svFaildAccountNumberExist, svSucceeded};

	enSaveResult Save() {
		switch (_mode) {
		case EmptyMode :
			return svFaildEmptyObject;

		case UpdateMode :
			_Update();
			return svSucceeded;

		case AddNewMode :
			if (clsBankClient::IsClientExist(AccountNumber)) {
				return svFaildAccountNumberExist;
			}
			else {
				_AddNew();
				_mode = enMode::UpdateMode;
				return svSucceeded;
			}

		}
	}
	bool Delete() {
		if (_mode == EmptyMode || _mode == AddNewMode) {
			return false;
		}

		vector <clsBankClient> vClients = _LoadclientsDataFromFile();
		for (clsBankClient& c1 : vClients) {
			if (c1.AccountNumber == this->AccountNumber) {
				c1._markedForDelete = true;
				_SaveUnMarkedVClientsInFile(vClients);
				*this = _GetEmptyClient();
				return true;
			}
		}
		return false;

		
	} 

	bool Deposit( double amount) {

		if (amount > 0 && _mode != enMode::EmptyMode && _mode != enMode::AddNewMode) {
			_accountBalance += amount;
			if (Save() == enSaveResult::svSucceeded) {
				return 1;
			}
			else {
				_accountBalance -= amount;
				return 0;
			}
		}
		else {
			return 0;
		}

	}

	bool Withdraw (double amount) {

		if (amount < 0 || amount > _accountBalance|| _mode == enMode::EmptyMode || _mode == enMode::AddNewMode)  {

			return 0;
		}
		else {
			_accountBalance -= amount;
			if (Save() == enSaveResult::svSucceeded) {
				return 1;
			}
			else {
				_accountBalance += amount;
				return 0;
			}
		}

	}

	bool Transfer(double amount, clsBankClient & to) {

		if (amount > AccountBalance || _mode == enMode::EmptyMode || _mode == enMode::AddNewMode||AccountNumber==to.AccountNumber) {
			return 0;
		} 

		if(Withdraw(amount)) {

			if (to.Deposit(amount)) {
				TransferLog(amount, to);
				return 1;
			}
			else {
				Deposit(amount);
				return 0;
			}


		}
		else {
			return 0;
		}


	}

	static vector<clsBankClient> GetClientsList() {
		return _LoadclientsDataFromFile();
	}
	static double GetTotalBalances() {
		double total=0;
		vector <clsBankClient> vClients = _LoadclientsDataFromFile();
		for (const clsBankClient& c1 : vClients) {
			
			total += c1.AccountBalance;
		}
		return total;

	}

	void TransferLog(double amount,const clsBankClient& to) {

		fstream file;
		
		file.open(_TransfersFileName, ios::app | ios::out);
		if (file.is_open()) {
			file << _prepareTransferRecordLine(amount, to) << endl;
			file.close();
		}

	}

	static vector <stTransfer> GetTransferList() {

		vector<stTransfer> vtrans;
		string line;

		fstream file;
		file.open(_TransfersFileName, ios::in);

		if (file.is_open()) {
			while (getline(file, line)) {
				vtrans.push_back(_convertLintToStTransferRecord(line));
			}

			file.close();
			
		}
		return vtrans;

	}


};

