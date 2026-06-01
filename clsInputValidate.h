#pragma once
#include <iostream>
#include <limits>
#include "DateLibrary.h"
#include "StringLibrary.h"
#include "PeriodLibrary.h"
#include <cctype>
using namespace std;

class clsInputValidate
{

private:
    static unsigned short NumberOfSeparotor(string date, string separator) {
        int position;
        unsigned short count = 0;
        while ((position = date.find(separator)) != string::npos) {
            count++;
            date.erase(0, position + separator.size());
        }
        return count;
    }
    static  bool DateStringNumbersOnly(string date, string separator) {
        int position;
        while ((position = date.find(separator)) != string::npos) {
            date.erase(position, separator.size());
        }
        for (unsigned short i = 0; i < date.size(); i++) {
            if (!isdigit(date[i])) {
                return false;
            }
        }
        return true;
    }

public:

    static bool IsNumberBetween(int number, int start, int end) {
        return (number >= start && number <= end);
    }

    static bool IsNumberBetween(double number, double start, double end) {
        return (number >= start && number <= end);
    }

    static bool IsValidDate(clsDate date) {
        return clsDate::ValideDate(date);
    }

    static bool IsDateBetween(const clsDate& date, const clsDate& start, const clsDate& end) {
        return clsPeriod::CheckDateWithinPeriod(date, clsPeriod(start, end));
    }

    static bool YesOrNo(const string& message) {
        string Answer;
        cout << message ;
        do {
            cin >> Answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Answer = clsString::LowerAllString(Answer);

            if (!(Answer == "yes" || Answer == "y" || Answer == "no" || Answer == "n"))
            {
                cout << "Please Enter yes or no : ";
            }
        } while (!(Answer == "yes" || Answer == "y" || Answer == "no" || Answer == "n"));
        return (Answer == "yes" || Answer == "y");
    }

    static double ReadDbleNumber(const string& message) {
        double number;
        while (true) {
            cout << message;
            if (cin >> number && isfinite(number)) {
                return number;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid number.\n";
        }
    }

    static double ReadPositiveDbleNumber(const string& message) {
        double number;
        while (true) {
            cout << message;
            if (cin >> number && isfinite(number) && number > 0) {
                return number;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a positive valid number.\n";
        }
    }

    static double ReadDbleNumberInRange(const string& message, const string& rangeErrorMessage = "Number is out of range, Please try again.\n", double from = numeric_limits<double>::lowest(), double to = numeric_limits<double>::max()) {
        double number;
        bool Repeat;
        while (true) {
            number = clsInputValidate::ReadDbleNumber(message);
            Repeat = !IsNumberBetween(number, from, to);
            if (Repeat) {
                cout << rangeErrorMessage;
            }
            else {
                return number;
            }
        }
    }

    static unsigned int ReadPositiveIntegerNumber(const string& message) {

        long long number;

        while (true) {
            cout << message;
            if (!(cin >> number)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a positive integer number.\n";
            }
            else if (number <= 0) {
                cout << "Please enter a positive number (> 0).\n";
            }
            else if (number > numeric_limits<unsigned int>::max()) {
                cout << "Number too large! Max allowed: "
                    << numeric_limits<unsigned int>::max() << ".\n";
            }
            else {
                return static_cast<unsigned int>(number);
            }
        }
    }

    static int ReadIntegerNumber(const string& message) {

        long long  number;
        while (true)

        {
            cout << message;
            if (!(cin >> number)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input , Please enter an integer number.\n";
            }
            else if (number > numeric_limits<int>::max() || number < numeric_limits<int>::min()) {
                cout << "Number out of range! Enter a number between "
                    << numeric_limits<int>::min() << " and "
                    << numeric_limits<int>::max() << "\n";
            }
            else {

                return static_cast<int>(number);

            }

        }

    }

    static int ReadIntNumberInRange(const string& message, const string& rangeErrorMessage = "Number is out of range, Please try again.\n", int from = numeric_limits<int>::min(), int to = numeric_limits<int>::max()) {
        int number;
        bool Repeat;
        while (true) {
            number = clsInputValidate::ReadIntegerNumber(message);
            Repeat = !IsNumberBetween(number, from, to);
            if (Repeat) {
                cout << rangeErrorMessage;
            }
            else {
                return number;
            }
        }
    }

    static unsigned int ReadPositiveUnsignedIntNumberInRange(const string& message, const string& stringErrorMessage = "Invalid input! Please enter a valid number.\n", unsigned  int from = 0, unsigned  int to = numeric_limits<unsigned int>::max()) {
        long long number;;
        do {
            cout << message;
            if (!(cin >> number))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << stringErrorMessage;
            }
            else if (number<from || number>to) {
                cout << "Unavailable number!!\n";
                cout << "Enter number in range from " << from << " to " << to << ".\n";
            }
            else {
                return static_cast<unsigned int>(number);;
            }
        } while (true);
    }

    static unsigned short ReadPositiveShortNumberInRange(const string& message, const string& stringErrorMessage = "Invalid input! Please enter a valid number.\n", unsigned  short from = 0, unsigned  short to = numeric_limits<unsigned short>::max()) {
        long long number;;
        do {
            cout << message;
            if (!(cin >> number))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << stringErrorMessage;
            }
            else if (number<from || number>to) {
                cout << "Unavailable number!!\n";
                cout << "Enter number in range from " << from << " to " << to << ".\n";
            }
            else {
                return static_cast<unsigned short>(number);;
            }
        } while (true);
    }

    static string ReadStringFromUser(const string& message) {
        string input;
        cout << message ;
        getline(cin >> ws, input);
        return input;
    }

    static char ReadCharFromUser(const string& message) {
        string input;
        do {
            cout << message;
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (input.size() > 1) {
                cout << "Invalid! Please enter one charcter Only.\n";
            }
        } while (input.size() != 1);

        return  input[0];
    }

    static string GetStringInSize(unsigned short from, unsigned short to, const string& message, const string& RangeErrorMessage = "Number of characters out of range, Please try again.\n") {
        string text;
        size_t size;

        do {
            cout << message;
            getline(cin >> ws, text);
            size = text.size();
            if (size > to || size < from) {
                cout << RangeErrorMessage;
            }
        } while (size > to || size < from);
        return text;
    }

    static clsDate ReadValideclsDate() {
        short year, month, day;
        clsDate date(1, 1, 1);
        bool valid;
        do {
            year = ReadPositiveShortNumberInRange("Enter the year : ", "Invalid input! Please enter a number of year.");
            month = ReadPositiveShortNumberInRange("Enter the number of the month : ", "Invalid input! Please enter a number of the month.");
            day = ReadPositiveShortNumberInRange("Enter the number of the day : ", "Invalid input! Please enter a number of the day.");
            date = clsDate(day, month, year);
            valid = date.ValideDate();
            if (!valid) {
                cout << "Invalid Date!!!,Please try again.\n";
            }
        } while (!valid);
        return date;

    }

    static string ReadStringDate() {

        string date;
        bool repeat;
        do {

            cout << "Please Enter Date In this Format (dd/mm/yyyy) : ";
            getline(cin >> ws, date);
            date = clsString::Trim(date);
            vector<string> parts = clsString::SplitString(date, "/");

            if (NumberOfSeparotor(date, "/") != 2) { repeat = true; }
            else if (!DateStringNumbersOnly(date, "/")) { repeat = true; }
            else if (date.length() < 8 || date.length() > 10) { repeat = true; }
            else if (parts.size() != 3) { repeat = true; }
            else { repeat = false; }

        } while (repeat);
        return date;

    }

    static clsDate ReadValidDateByString() {
        string stringDate;
        clsDate date(1, 1, 1);
        bool repeat = false;
        do {
            stringDate = ReadStringDate();
            date = clsDate(stringDate);
            if (!clsDate::ValideDate(date)) {
                cout << "Invalid Date !!!!!\n";
                repeat = true;
            }
            else {
                repeat = false;
            }
        } while (repeat);
        return date;
    }

    static clsDate ReadValideDateInPeriod(const clsPeriod& period) {
        clsDate date(1, 1, 1);
        bool Repeat;
        do {
            date = ReadValideclsDate();
            Repeat = !clsInputValidate::IsDateBetween(date, period.StartDate, period.EndDate);
            if (Repeat) {
                cout << "The Date is not between " << period.StartDate.DateToString() << " and " << period.EndDate.DateToString() << " , Please try again .\n";
            }
        } while (Repeat);
        return date;

    }
};