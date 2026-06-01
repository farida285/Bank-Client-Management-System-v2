#pragma once
#include "DateLibrary.h"

class clsPeriod
{
public:

    clsDate StartDate;
    clsDate EndDate;

    clsPeriod(clsDate StartDate, clsDate DateTo)
    {
        if (clsDate::CheckDate1AfterDate2(StartDate, DateTo)) {
            clsDate::SwapDates(StartDate, DateTo);
        }
        this->StartDate = StartDate;
        this->EndDate = DateTo;

    }

    static bool IsOverlapPeriods(clsPeriod period1, clsPeriod period2)
    {
        return(!((clsDate::CompareDate1WithDate2(period1.EndDate, period2.StartDate) == clsDate::enDateCompareResult::Before) ||
            (clsDate::CompareDate1WithDate2(period1.StartDate, period2.EndDate) == clsDate::enDateCompareResult::After)));

    }

    bool IsOverlapPeriods(clsPeriod period)
    {
        return IsOverlapPeriods(*this, period);

    }


    bool IsOverLapWith(clsPeriod Period2)
    {
        return IsOverlapPeriods(*this, Period2);
    }

    static int PreiodLength(clsPeriod period, bool IncludeEndDay = false) {
        return clsDate::GetDifferenceInDays(period.StartDate, period.EndDate, IncludeEndDay);

    }

    int PreiodLength(bool IncludeEndDay = false) {
        return PreiodLength(*this, IncludeEndDay);

    }

    static void Print(clsPeriod period)
    {
        cout << "Period Start: ";
        period.StartDate.PrintDate();


        cout << "Period End: ";
        period.EndDate.PrintDate();


    }

    void Print()
    {
        cout << "Period Start: ";
        StartDate.PrintDate();


        cout << "Period End: ";
        EndDate.PrintDate();


    }

    static bool CheckDateWithinPeriod(const clsDate& date, const clsPeriod& period) {
        return ((clsDate::CompareDate1WithDate2(date, period.StartDate) != clsDate::enDateCompareResult::Before) && (clsDate::CompareDate1WithDate2(date, period.EndDate) != clsDate::enDateCompareResult::After));
    }

    bool CheckDateWithinPeriod(clsDate date) {
        return CheckDateWithinPeriod(date, *this);
    }
};
