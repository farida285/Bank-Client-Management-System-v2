#pragma once 
#pragma warning(disable : 4996)
#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>
#include <string>
#include "StringLibrary.h"
using namespace std;
class clsDate
{
private:
    short _year;
    short _month;
    short _day;

protected:
    enum enDays { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

public:
    clsDate() {
        time_t t = time(0); // get time now
        tm* now = localtime(&t);// converting now to tm struct for UTC date/time
        _year = now->tm_year + 1900;
        _month = now->tm_mon + 1;
        _day = now->tm_mday;
    };
    clsDate(short day, short month, short year) {
        _year = year;
        _month = month;
        _day = day;
    };
    clsDate(short year, short dateOrderInYear) {
        *this = TakeOrderDayInYearAndconvertToDate(year, dateOrderInYear);
    }
    clsDate(string date) {


        vector<string> Vdate = clsString::SplitString(date, "/");

        *this = clsDate((short)stoi(Vdate.at(0)), (short)stoi(Vdate.at(1)), (short)stoi(Vdate.at(2)));

    };


    void SetDay(short day) {
        _day = day;
    }
    short GetDay()const {
        return _day;
    }
    __declspec(property(get = GetDay, put = SetDay)) short Day;

    void SetMonth(short month) {
        _month = month;
    }
    short GetMonth() const {
        return _month;
    }
    __declspec(property(get = GetMonth, put = SetMonth)) short Month;

    void SetYear(short year) {
        _year = year;
    }
    short GetYear() const {
        return _year;
    }
    __declspec(property(get = GetYear, put = SetYear)) short Year;


    static string DateToString(const clsDate& date) {

        return(to_string(date.Day) + "/" + to_string(date.Month) + "/" + to_string(date.Year));
    }

    string DateToString() const {
        return DateToString(*this);
    }

    static void PrintDate(const clsDate& date) {
        cout << DateToString(date);
    }

    void PrintDate() {
        PrintDate(*this);
    }

    static bool IsLeapYear(short year) {
        return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));
    }

    bool IsLeapYear() {
        return IsLeapYear(_year);
    }

    static unsigned short NumberOfDaysInYear(unsigned short year) {
        return((IsLeapYear(year)) ? 366 : 365);
    }

    unsigned short NumberOfDaysInYear() {
        return   NumberOfDaysInYear(_year);
    }

    static unsigned short NumberOfHoursInYear(unsigned short year) {
        return(NumberOfDaysInYear(year) * 24);
    }

    unsigned short NumberOfHoursInYear() {
        return  NumberOfHoursInYear(_year);
    }

    static unsigned int NumberOfMinutesInYear(unsigned short year) {
        return(NumberOfHoursInYear(year) * 60);
    }

    unsigned int NumberOfMinutesInYear() {
        return NumberOfMinutesInYear(_year);
    }

    static unsigned int NumberOfSecondsInYear(unsigned short year) {
        return(NumberOfMinutesInYear(year) * 60);
    }

    unsigned int NumberOfSecondsInYear() {
        return  NumberOfSecondsInYear(_year);
    }

    static unsigned short NumberOfDaysInMonth(unsigned short year, unsigned short month) {
        if (month < 1 || month>12) {
            return 0;
        }
        unsigned short arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        return((month == 2) ? ((IsLeapYear(year)) ? 29 : 28) : (arr[month - 1]));
    }

    unsigned short NumberOfDaysInMonth() {
        return  NumberOfDaysInMonth(_year, _month);
    }

    static unsigned short NumberOfHoursInMonth(unsigned short year, unsigned short month) {
        return(NumberOfDaysInMonth(year, month) * 24);
    }

    unsigned short NumberOfHoursInMonth() {
        return   NumberOfHoursInMonth(_year, _month);
    }

    static unsigned int NumberOfMinutesInMonth(unsigned short year, unsigned short month) {
        return(NumberOfHoursInMonth(year, month) * 60);
    }

    unsigned int NumberOfMinutesInMonth() {
        return  NumberOfMinutesInMonth(_year, _month);
    }

    static unsigned int NumberOfSecondsInMonth(unsigned short year, unsigned short month) {
        return(NumberOfMinutesInMonth(year, month) * 60);
    }

    unsigned int NumberOfSecondsInMonth() {
        return  NumberOfSecondsInMonth(_year, _month);
    }

    static unsigned short DayOrder(clsDate date) {
        unsigned short a = (14 - date.Month) / 12;
        unsigned short y = date.Year - a;
        unsigned short m = date.Month + (12 * a) - 2;
        unsigned short d = ((date.Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7);
        return d;
    }

    unsigned short DayOrder() {
        return(DayOrder(*this));
    }

    static string DayName(clsDate date) {
        string arr[7] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };
        return(arr[DayOrder(date)]);
    }

    string DayName() {
        return  DayName(*this);
    }

    static string MonthName(short month) {
        if (month < 1 || month>12) {
            return "";
        }
        string months[12] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December" };
        return(months[month - 1]);
    }

    string MonthName() {
        return MonthName(_month);
    }

    static void PrintMonthCelender(unsigned short year, unsigned short month) {
        unsigned short count = 0;
        unsigned short numberOfDays = NumberOfDaysInMonth(year, month);
        cout << "___________________________________________________" << MonthName(month) << "___________________________________________________\n\n";
        cout << setw(12) << "Sunday\t" << setw(12) << "Monday\t" << setw(12) << "Tuesday\t" << setw(12) << "Wednesday\t" << setw(12) << "Thursday\t" << setw(12) << "Friday\t" << setw(12) << "Saturday\n";
        unsigned short i;
        for (i = 0; i < DayOrder(clsDate(1, month, year)); i++) {
            cout << "\t\t";
        };
        for (unsigned short j = 1; j <= numberOfDays; j++) {
            cout << setw(8) << j;
            i++;
            if (i == 7) {
                i = 0;
                cout << endl;
            }
            else {
                cout << "\t";
            }
        }
        cout << "\n____________________________________________________________________________________________________________\n";
    }

    void PrintMonthCelender() {
        PrintMonthCelender(_year, _month);
    }

    static void PrintYearCelender(short year) {
        cout << "\n____________________________________________________________________________________________________________\n";
        cout << "                                            Celender . " << year << endl;
        cout << "\n____________________________________________________________________________________________________________\n\n";
        for (unsigned short month = 1; month <= 12; month++) {
            PrintMonthCelender(year, month);
            cout << endl;
        }
    }

    void PrintYearCelender() {
        PrintYearCelender(_year);
    }

    static unsigned short NumberOfDaysFromTheBeginningOfYear(clsDate date) {
        unsigned short totalDays = date.Day;
        for (unsigned short i = 1; i < date.Month; i++) {
            totalDays += NumberOfDaysInMonth(date.Year, i);
        }
        return totalDays;
    }

    unsigned short NumberOfDaysFromTheBeginningOfYear() {
        return NumberOfDaysFromTheBeginningOfYear(*this);
    }

    static clsDate TakeOrderDayInYearAndconvertToDate(short year, short dateOrderInYear) {


        short remainingDays = dateOrderInYear;

        for (short month = 1; month <= 12; month++) {
            short daysInMonth = NumberOfDaysInMonth(year, month);

            if (remainingDays > daysInMonth) {
                remainingDays -= daysInMonth;
            }
            else {
                return clsDate(remainingDays, month, year);
            }
        }
        return clsDate(1, 1, year); // fallback
    }

    static bool CheckDate1LessThanDate2(const clsDate& date1, const clsDate& date2) {
        if (date1.Year < date2.Year)  return true;
        if (date1.Year > date2.Year)  return false;
        if (date1.Month < date2.Month) return true;
        if (date1.Month > date2.Month) return false;
        return date1.Day < date2.Day;
    }

    bool CheckDateLessThanThisDate(const clsDate& date) {
        return CheckDate1LessThanDate2(*this, date);

    }

    static bool CheckDate1EqualThanDate2(const clsDate& date1, const clsDate& date2) {

        return (date1.Year == date2.Year && date1.Month == date2.Month && date1.Day == date2.Day);
    }

    bool CheckDateEqualThanThisDate(const clsDate& date) {
        return  CheckDate1EqualThanDate2(*this, date);
    }

    static bool CheckDate1AfterDate2(const clsDate& date1, const clsDate& date2) {
        return(!CheckDate1EqualThanDate2(date1, date2) && !CheckDate1LessThanDate2(date1, date2));
    }

    bool CheckDateAfterThisDate(const clsDate& date) {
        return CheckDate1AfterDate2(*this, date);
    }

    enum enDateCompareResult { Before = -1, Equal, After };

    static enDateCompareResult CompareDate1WithDate2(const clsDate& date1, const clsDate& date2) {
        return (CheckDate1LessThanDate2(date1, date2) ? enDateCompareResult::Before : (CheckDate1EqualThanDate2(date1, date2)) ? enDateCompareResult::Equal : enDateCompareResult::After);
    }

    enDateCompareResult CompareDateWithThisDate(const clsDate& date) {
        return CompareDate1WithDate2(*this, date);
    }

    static bool ValideDate(clsDate date) {
        return((date.Month >= 1 && date.Month <= 12) && (date.Day >= 1 && date.Day <= NumberOfDaysInMonth(date.Year, date.Month)));
    }

    bool ValideDate() {
        return  ValideDate(*this);
    }

    static clsDate GetSystemDate() {

        time_t t = time(0); // get time now
        tm* now = localtime(&t);// converting now to tm struct for UTC date/time

        clsDate nowDate;

        nowDate.Year = now->tm_year + 1900;
        nowDate.Month = now->tm_mon + 1;
        nowDate.Day = now->tm_mday;

        return nowDate;
    }

    static bool IsLastMonthInYear(short month) {
        return(month == 12);
    }

    bool IsLastMonthInYear() {
        return IsLastMonthInYear(_month);
    }

    static bool IsLastDayInMonth(clsDate date) {
        return(date.Day == NumberOfDaysInMonth(date.Year, date.Month));
    }

    bool IsLastDayInMonth() {
        return IsLastDayInMonth(*this);
    }

    static bool IsFirstMonthInYear(short month) {
        return(month == 1);
    }

    bool IsFirstMonthInYear() {
        return IsFirstMonthInYear(_month);
    }

    static bool IsFirstDayInmonth(short day) {
        return(day == 1);
    }

    bool IsFirstDayInmonth() {
        return IsFirstDayInmonth(_day);
    }

    static clsDate IncreaseDateByOneDay(clsDate date) {
        if (IsLastDayInMonth(date))
        {
            if (IsLastMonthInYear(date.Month)) {
                date.Year++;
                date.Month = 1;
                date.Day = 1;
            }
            else {
                date.Month++;
                date.Day = 1;
            }
        }
        else {
            date.Day++;
        }
        return date;
    }
    void IncreaseDateByOneDay() {
        *this = IncreaseDateByOneDay(*this);
    }
    static clsDate IncreaseDateByXDaysForMediumNumbers(clsDate date, unsigned short addDays) {
        if (addDays == 0) {
            return date;
        }
        unsigned short totalDays = NumberOfDaysFromTheBeginningOfYear(date) + addDays;
        unsigned short daysOfMonth;
        date.Month = 1;
        date.Day = 1;
        while (true) {
            daysOfMonth = NumberOfDaysInMonth(date.Year, date.Month);
            if (totalDays > daysOfMonth) {
                totalDays -= daysOfMonth;
                date.Month++;
                date.Day = 1;
                if (date.Month > 12) {
                    date.Month = 1;
                    date.Year++;
                }
            }
            else {
                date.Day = totalDays;
                return date;
            }
        }
    }

    void IncreaseDateByXDaysForMediumNumbers(unsigned short addDays) {
        *this = IncreaseDateByXDaysForMediumNumbers(*this, addDays);
    }

    static clsDate IncreaseDateByXDaysFasterForHugeNumbers(clsDate date, unsigned int addDays) {
        if (addDays == 0) return date;
        unsigned short totalDaysInYear;
        unsigned short orderDateInYear = NumberOfDaysFromTheBeginningOfYear(date);
        while (true)
        {
            totalDaysInYear = (IsLeapYear(date.Year)) ? 366 : 365;
            if ((totalDaysInYear - orderDateInYear) < addDays) {
                addDays -= (totalDaysInYear - orderDateInYear + 1);
                orderDateInYear = 1;
                date.Year++;
            }
            else {
                orderDateInYear += addDays;
                return(TakeOrderDayInYearAndconvertToDate(date.Year, orderDateInYear));

            }

        }

    }

    void  IncreaseDateByXDaysFasterForHugeNumbers(unsigned int addDays) {
        *this = IncreaseDateByXDaysFasterForHugeNumbers(*this, addDays);
    }

    static clsDate IncreaseDateByXDaysForSmallNumbers(clsDate Date, unsigned short Days)
    {
        for (short i = 1; i <= Days; i++)
        {
            Date = IncreaseDateByOneDay(Date);
        }
        return Date;
    }

    void IncreaseDateByXDaysForSmallNumbers(unsigned short Days) {
        *this = IncreaseDateByXDaysForSmallNumbers(*this, Days);
    }

    static clsDate IncreaseDateByOneWeek(clsDate  date) {
        return IncreaseDateByXDaysForSmallNumbers(date, 7);
    }

    void IncreaseDateByOneWeek() {
        *this = IncreaseDateByOneWeek(*this);
    }

    static clsDate IncreaseDateByXWeeks(clsDate date, unsigned short numberOfWeeks) {
        return IncreaseDateByXDaysForMediumNumbers(date, 7 * numberOfWeeks);
    }

    void IncreaseDateByXWeeks(unsigned short numberOfWeeks) {
        *this = IncreaseDateByXWeeks(*this, numberOfWeeks);
    }

    static clsDate IncreaseDateByOneMonth(clsDate date) {
        if (IsLastMonthInYear(date.Month)) {
            date.Month = 1;
            date.Year++;
        }
        else {
            date.Month++;
        }
        //last check day in date should not exceed max days in the current month
      // example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should
      // be 28/2/2022
        if (NumberOfDaysInMonth(date.Year, date.Month) < date.Day) {
            date.Day = NumberOfDaysInMonth(date.Year, date.Month);
        }
        return date;

    }

    void IncreaseDateByOneMonth() {
        *this = IncreaseDateByOneMonth(*this);
    }

    static clsDate IncreaseDateByXMonths(clsDate date, unsigned short numberOfMonths) {
        for (unsigned short i = 0; i < numberOfMonths; i++) {
            if (IsLastMonthInYear(date.Month)) {
                date.Month = 1;
                date.Year++;
            }
            else {
                date.Month++;
            }
        }
        if (NumberOfDaysInMonth(date.Year, date.Month) < date.Day) {
            date.Day = NumberOfDaysInMonth(date.Year, date.Month);
        }
        return date;

    }
    void IncreaseDateByXMonths(unsigned short numberOfMonths) {
        *this = IncreaseDateByXMonths(*this, numberOfMonths);
    }

    static clsDate FixLeapDayIfNeeded(clsDate date) {
        if (date.Month == 2 && date.Day == 29 && !IsLeapYear(date.Year))
            date.Day = 28;
        return date;
    }

    void FixLeapDayIfNeeded() {
        *this = FixLeapDayIfNeeded(*this);
    }

    static clsDate IncreaseDateByOneYear(clsDate date) {

        date.Year++;
        return FixLeapDayIfNeeded(date);

    }

    void IncreaseDateByOneYear() {
        *this = IncreaseDateByOneYear(*this);
    }

    static clsDate IncreaseDateByXYears(clsDate date, unsigned short numberOfYears) {
        bool wasLeapDay = (date.Month == 2 && date.Day == 29 && IsLeapYear(date.Year));
        for (unsigned short i = 0; i < numberOfYears; i++) {
            date = IncreaseDateByOneYear(date);
        }
        if (wasLeapDay && IsLeapYear(date.Year)) {
            date.Day = 29;
        }

        return date;

    }

    void IncreaseDateByXYears(unsigned short numberOfYears) {
        *this = IncreaseDateByXYears(*this, numberOfYears);
    }

    static clsDate IncreaseDateByXYearsFaster(clsDate date, unsigned short numberOfYears) {
        date.Year += numberOfYears;
        return FixLeapDayIfNeeded(date);
    }

    void IncreaseDateByXYearsFaster(unsigned short numberOfYears) {
        *this = IncreaseDateByXYearsFaster(*this, numberOfYears);
    }

    static clsDate IncreaseDateByOneDecade(clsDate date) {
        date.Year += 10;
        return FixLeapDayIfNeeded(date);

    }

    void IncreaseDateByOneDecade() {
        *this = IncreaseDateByOneDecade(*this);
    }

    static clsDate IncreaseDateByXDecades(clsDate date, unsigned short numberOfDecade) {
        bool wasLeapDay = (date.Month == 2 && date.Day == 29 && IsLeapYear(date.Year));
        for (unsigned short i = 0; i < numberOfDecade; i++) {
            date = IncreaseDateByOneDecade(date);
        }
        if (wasLeapDay && IsLeapYear(date.Year)) {
            date.Day = 29;
        }
        return date;
    }

    void IncreaseDateByXDecades(unsigned short numberOfDecade) {
        *this = IncreaseDateByXDecades(*this, numberOfDecade);
    }

    static clsDate IncreaseDateByXDecadesFaster(clsDate date, unsigned short numberOfDecade) {
        date.Year += (numberOfDecade * 10);
        return FixLeapDayIfNeeded(date);

    }

    void IncreaseDateByXDecadesFaster(unsigned short numberOfDecade) {
        *this = IncreaseDateByXDecadesFaster(*this, numberOfDecade);
    }

    static clsDate IncreaseDateByOneCentury(clsDate date) {
        date.Year += (100);
        return FixLeapDayIfNeeded(date);

    }

    void IncreaseDateByOneCentury() {
        *this = IncreaseDateByOneCentury(*this);
    }

    static clsDate IncreaseDateByOneMillennium(clsDate date) {
        date.Year += (1000);
        return FixLeapDayIfNeeded(date);

    }

    void IncreaseDateByOneMillennium() {
        *this = IncreaseDateByOneMillennium(*this);
    }

    static void SwapDates(clsDate& date1, clsDate& date2) {
        clsDate temp;
        temp.Year = date1.Year;
        temp.Month = date1.Month;
        temp.Day = date1.Day;
        date1.Year = date2.Year;
        date1.Month = date2.Month;
        date1.Day = date2.Day;
        date2.Year = temp.Year;
        date2.Month = temp.Month;
        date2.Day = temp.Day;

    }

    static int GetDifferenceInDays(clsDate date1, clsDate date2, bool includeEndDay = false) {

        int  days = 0;
        short swapFlag = 1;
        if (CheckDate1LessThanDate2(date2, date1)) {
            SwapDates(date1, date2);
            swapFlag = -1;
        }
        if (CheckDate1LessThanDate2(date1, date2)) {

            while (date2.Year > date1.Year)
            {
                unsigned short noOfDaysInYear = (IsLeapYear(date1.Year)) ? 366 : 365;
                days += (noOfDaysInYear - NumberOfDaysFromTheBeginningOfYear(date1) + 1);
                date1.Year++;
                date1.Month = 1;
                date1.Day = 1;
            }
            days += NumberOfDaysFromTheBeginningOfYear(date2)
                - NumberOfDaysFromTheBeginningOfYear(date1);
            return ((includeEndDay) ? ++days * swapFlag : days * swapFlag);

        }
        return (days);
    }
    int GetDifferenceInDays(clsDate date) {
        return GetDifferenceInDays(*this, date);
    }

    static short CalculateMyAgeInDays(clsDate DateOfBirth) {
        return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
    }

    static clsDate DecreaseDateByOneDay(clsDate date) {
        if (IsFirstDayInmonth(date.Day)) {
            if (IsFirstMonthInYear(date.Month)) {
                date.Year--;
                date.Month = 12;
                date.Day = 31;
            }
            else {
                date.Month--;
                date.Day = NumberOfDaysInMonth(date.Year, date.Month);
            }
        }
        else {
            date.Day--;
        }
        return date;
    }

    void DecreaseDateByOneDay() {
        *this = DecreaseDateByOneDay(*this);
    }

    static clsDate DecreaseDateByXDaysForMediumNumbers(clsDate date, unsigned short subDays) {
        if (subDays == 0) {
            return date;
        }

        while (subDays >= date.Day) {
            unsigned short remainingDaysInCurrentMonth = date.Day;
            subDays -= remainingDaysInCurrentMonth;
            date.Month--;
            if (date.Month == 0)
            {
                date.Month = 12;
                date.Year--;
            }
            date.Day = NumberOfDaysInMonth(date.Year, date.Month);
        }

        date.Day -= subDays;
        return date;

    }

    void DecreaseDateByXDaysForMediumNumbers(unsigned short subDays) {
        *this = DecreaseDateByXDaysForMediumNumbers(*this, subDays);
    }

    static clsDate DecreaseDateByXDaysFasterForHugeNumbers(clsDate date, unsigned int subDays) {
        if (subDays == 0) return date;
        unsigned short dayOfYear = NumberOfDaysFromTheBeginningOfYear(date);

        while (dayOfYear <= subDays) {
            subDays -= dayOfYear;
            date.Year--;
            dayOfYear = (IsLeapYear(date.Year) ? 366 : 365);
        }
        dayOfYear -= subDays;
        return (TakeOrderDayInYearAndconvertToDate(date.Year, dayOfYear));
    }

    void DecreaseDateByXDaysFasterForHugeNumbers(unsigned int subDays) {
        *this = DecreaseDateByXDaysFasterForHugeNumbers(*this, subDays);
    }

    static clsDate DecreaseDateByXDaysForSmallNumbers(clsDate Date, unsigned short Days)
    {
        for (short i = 0; i < Days; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }

    void DecreaseDateByXDaysForSmallNumbers(unsigned short Days) {
        *this = DecreaseDateByXDaysForSmallNumbers(*this, Days);
    }

    static clsDate DecreaseDateByOneWeek(clsDate date) {
        return DecreaseDateByXDaysForSmallNumbers(date, 7);
    }

    void DecreaseDateByOneWeek() {
        *this = DecreaseDateByOneWeek(*this);
    }

    static clsDate DecreaseDateByXWeeks(clsDate date, unsigned short numberOfWeeks) {
        return DecreaseDateByXDaysForMediumNumbers(date, 7 * numberOfWeeks);
    }

    void DecreaseDateByXWeeks(unsigned short numberOfWeeks) {
        *this = DecreaseDateByXWeeks(*this, numberOfWeeks);
    }

    static clsDate DecreaseDateByOneMonth(clsDate date) {
        if (IsFirstDayInmonth(date.Month)) {
            date.Month = 12;
            date.Year--;

        }
        else {
            date.Month--;
        }
        if (date.Day > NumberOfDaysInMonth(date.Year, date.Month)) {
            date.Day = NumberOfDaysInMonth(date.Year, date.Month);
        }
        return date;
    }

    void  DecreaseDateByOneMonth() {
        *this = DecreaseDateByOneMonth(*this);
    }

    static clsDate DecreaseDateByXMonths(clsDate date, unsigned short numberOfMonths) {
        for (unsigned short i = 0; i < numberOfMonths; i++) {
            if (IsFirstDayInmonth(date.Month)) {
                date.Month = 12;
                date.Year--;

            }
            else {
                date.Month--;
            }
        }
        if (date.Day > NumberOfDaysInMonth(date.Year, date.Month)) {
            date.Day = NumberOfDaysInMonth(date.Year, date.Month);
        }
        return date;
    }

    void  DecreaseDateByXMonths(unsigned short numberOfMonths) {
        *this = DecreaseDateByXMonths(*this, numberOfMonths);
    }

    static clsDate DecreaseDateByOneYear(clsDate date) {

        date.Year--;
        return FixLeapDayIfNeeded(date);

    }

    void DecreaseDateByOneYear() {
        *this = DecreaseDateByOneYear(*this);
    }

    static clsDate DecreaseDateByXYears(clsDate date, unsigned short numberOfYears) {
        bool wasLeapDay = (date.Month == 2 && date.Day == 29 && IsLeapYear(date.Year));
        for (unsigned short i = 0; i < numberOfYears; i++) {
            date = DecreaseDateByOneYear(date);
        }
        if (wasLeapDay && IsLeapYear(date.Year)) {
            date.Day = 29;
        }

        return date;

    }

    void DecreaseDateByXYears(unsigned short numberOfYears) {
        *this = DecreaseDateByXYears(*this, numberOfYears);
    }

    static clsDate DecreaseDateByXYearsFaster(clsDate date, unsigned short numberOfYears) {
        date.Year -= numberOfYears;
        return FixLeapDayIfNeeded(date);

    }

    void DecreaseDateByXYearsFaster(unsigned short numberOfYears) {
        *this = DecreaseDateByXYearsFaster(*this, numberOfYears);
    }

    static clsDate DecreaseDateByOneDecade(clsDate date) {
        date.Year -= 10;
        return FixLeapDayIfNeeded(date);


    }

    void  DecreaseDateByOneDecade() {
        *this = DecreaseDateByOneDecade(*this);
    }

    static clsDate DecreaseDateByXDecades(clsDate date, unsigned short numberOfDecade) {
        bool wasLeapDay = (date.Month == 2 && date.Day == 29 && IsLeapYear(date.Year));
        for (unsigned short i = 0; i < numberOfDecade; i++) {
            date = DecreaseDateByOneDecade(date);
        }
        if (wasLeapDay && IsLeapYear(date.Year)) {
            date.Day = 29;
        }
        return date;
    }

    void DecreaseDateByXDecades(unsigned short numberOfDecade) {
        *this = DecreaseDateByXDecades(*this, numberOfDecade);
    }

    static clsDate DecreaseDateByXDecadesFaster(clsDate date, unsigned short numberOfDecade) {
        date.Year -= (numberOfDecade * 10);
        return FixLeapDayIfNeeded(date);

    }

    void DecreaseDateByXDecadesFaster(unsigned short numberOfDecade) {
        *this = DecreaseDateByXDecadesFaster(*this, numberOfDecade);
    }

    static clsDate DecreaseDateByOneCentury(clsDate date) {
        date.Year -= (100);
        return FixLeapDayIfNeeded(date);

    }

    void DecreaseDateByOneCentury() {
        *this = DecreaseDateByOneCentury(*this);
    }

    static clsDate DecreaseDateByOneMillennium(clsDate date) {
        date.Year -= (1000);
        return FixLeapDayIfNeeded(date);

    }

    void DecreaseDateByOneMillennium() {
        *this = DecreaseDateByOneMillennium(*this);
    }



    static bool IsEndOfWeek(clsDate date) {
        return(DayOrder(date) == enDays::Saturday);
    }

    bool IsEndOfWeek() {
        return IsEndOfWeek(*this);
    }

    static bool IsWeekEndDay(clsDate date) {
        enDays day = (enDays)DayOrder(date);
        return(day == enDays::Friday || day == enDays::Saturday);
    }

    bool IsWeekEndDay() {
        return IsWeekEndDay(*this);
    }

    static bool IsBusinessDay(clsDate date) {
        return(!IsWeekEndDay(date));
    }

    bool IsBusinessDay() {
        return IsBusinessDay(*this);
    }

    static unsigned short DaysUntilEndOftheWeek(clsDate date) {
        return (6 - (unsigned short)DayOrder(date));
    }

    unsigned short DaysUntilEndOftheWeek() {
        return DaysUntilEndOftheWeek(*this);
    }

    static unsigned short DaysUntilEndOftheMonth(clsDate date) {
        return (NumberOfDaysInMonth(date.Year, date.Month) - date.Day);
    }

    unsigned short DaysUntilEndOftheMonth() {
        return DaysUntilEndOftheMonth(*this);
    }

    static unsigned short DaysUntilEndOftheYear(clsDate date) {

        return ((IsLeapYear(date.Year) ? (366 - NumberOfDaysFromTheBeginningOfYear(date)) : (365 - NumberOfDaysFromTheBeginningOfYear(date))));
    }

    unsigned short DaysUntilEndOftheYear() {
        return  DaysUntilEndOftheYear(*this);
    }

    static unsigned short ActualVactionDays(clsDate startDate, clsDate endDate) {
        unsigned vactionDaysCount = (IsBusinessDay(endDate) ? 1 : 0);
        while (CheckDate1LessThanDate2(startDate, endDate)) {
            if (IsBusinessDay(startDate)) {
                vactionDaysCount++;
            }
            startDate = IncreaseDateByOneDay(startDate);
        }
        return vactionDaysCount;
    }

    static bool CheckDateWithinPeriod(clsDate date, clsDate start, clsDate end) {
        return ((CompareDate1WithDate2(date, start) != enDateCompareResult::Before) && (CompareDate1WithDate2(date, end) != enDateCompareResult::After));
    }

    static string GetDateSystemTimeString() {
        time_t t = time(0); // get time now
        tm* now = localtime(&t);// converting now to tm struct for UTC date/time
        
        string time = to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);
        return (clsDate().DateToString() + "-" + time);


    }

};
