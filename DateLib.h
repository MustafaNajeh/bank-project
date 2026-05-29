#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;
#pragma warning(disable : 4996)
namespace DateLib
{

	struct sDate {

		short Year;
		short Month;
		short Day;
	};

	struct sPeriod {

		sDate Start;
		sDate End;


	};

	short ReadMonth()
	{
		short num = 0;
		cout << "plaese enter your Month To Check ? ";
		cin >> num;
		cout << "\n";
		return num;
	}

	short ReadDay()
	{
		short num = 0;
		cout << "plaese enter your Day To Check ? ";
		cin >> num;
		cout << "\n";
		return num;
	}
	short ReadYear()
	{
		short num = 0;
		cout << "plaese enter your Year To Check ? ";
		cin >> num;
		cout << "\n";
		return num;
	}

	sDate ReadDate() {

		sDate Date;
		Date.Year = ReadYear();
		Date.Month = ReadMonth();
		Date.Day = ReadDay();

		return Date;
	}

	sPeriod ReadPeriod() {
		sPeriod Period;
		cout << "Enter Satrt Date:\n";
		Period.Start = ReadDate();
		cout << "\n";
		cout << "Enter End Date:\n";
		Period.End = ReadDate();
		return Period;
	}

	short OrderDay(short Year, short Month, short Day) {

		short a = ((14 - Month) / 12);
		short y = Year - a;
		short m = Month + 12 * a - 2;
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

	}

	bool IsLeapYear(short Year) {

		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);

	}

	short NumberOfDaysInMonth(short Year, short Month) {

		if (Month < 1 || Month > 12) {
			return 0;
		}
		short MonthOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : MonthOfDays[Month - 1];



	}
	

	

	string DayNameOfTheWeek(short OrderDay) {

		string arrDayName[] = { "Sun","Mon","Tue","Win","Thu","Fri","Sat" };
		return arrDayName[OrderDay];

	}
	string NameMonthInTheYear(short NumberOfMonth) {

		string arrStringMonth[12] = {
			"Jan","Feb","Mar","Apr"
			,"May","Jun","Jul","Aug"
			,"Sep","Oct","Nov","Dec" };

		return(arrStringMonth[NumberOfMonth - 1]);
	}

	void PrintMonthCalender(short Year, short Month) {

		int NumberOfDays;

		int CurrentDay = OrderDay(Year, Month, 1);

		NumberOfDays = NumberOfDaysInMonth(Year, Month);

		printf("\n  __________________%s______________\n\n",
			NameMonthInTheYear(Month).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
		int i;
		for (i = 0; i < CurrentDay; i++) {
			printf("     ");
		}

		for (int j = 1; j <= NumberOfDays; j++) {

			printf("%5d", j);
			if (++i == 7) {
				i = 0;
				printf("\n");
			}

		}

		printf("\n  _____________________________________\n");
	}

	short TotalDaysFromBeginningYear(short Year, short Month, short Days) {
		short TotalDays = 0;

		for (int i = 1; i <= Month - 1; i++) {

			TotalDays += NumberOfDaysInMonth(Year, i);

		}
		TotalDays += Days;
		return TotalDays;



	}

	sDate ConvertTotalDaysToDate(short Year, short TotalDays) {

		sDate Date;
		short RminingDays = TotalDays;
		short MonthDays;

		Date.Year = Year;
		Date.Month = 1;

		while (true) {

			MonthDays = NumberOfDaysInMonth(Year, Date.Month);

			if (RminingDays > MonthDays) {

				RminingDays -= MonthDays;
				Date.Month++;

			}
			else {

				Date.Day = RminingDays;
				break;


			}

		}
		return Date;
	}

	sDate AddingDaysIntoTheDate(int DaysToAdd, sDate Date) {

		short RminingDays = DaysToAdd + TotalDaysFromBeginningYear(Date.Year, Date.Month, Date.Day);
		short MonthDays;

		Date.Month = 1;

		while (true) {

			MonthDays = NumberOfDaysInMonth(Date.Year, Date.Month);

			if (RminingDays >= MonthDays) {
				RminingDays -= MonthDays;
				Date.Month++;
				if (Date.Month > 12) {
					Date.Year++;
					Date.Month = 1;
				}
			}
			else {

				Date.Day = RminingDays;

				break;
			}


		}
		return Date;
	}

	bool IsDate1BeforDate2(sDate Date1, sDate Date2) {

		return Date1.Year < Date2.Year ? true : Date1.Year == Date2.Year ?
			(Date1.Month < Date2.Month) ? true : ((Date1.Month == Date2.Month) ? (Date1.Day < Date2.Day) : false) : false;

	}

	bool IsDate1EqualDate2(sDate Date1, sDate Date2) {

		return Date1.Year == Date2.Year ? (Date1.Month == Date2.Month ? (Date1.Day == Date2.Day ? true : false) : false) : false;

	}

	bool IsDate1AfterDate2(sDate Date1, sDate Date2) {

		return (!IsDate1BeforDate2(Date1, Date2)) && (!IsDate1EqualDate2(Date1, Date2));

	}

	enum enCompareDates { After = 1, befor = -1, equal = 0 };

	enCompareDates CompareDates(sDate Date1, sDate Date2) {

		if (IsDate1AfterDate2(Date1, Date2))
			return enCompareDates::After;

		if (IsDate1BeforDate2(Date1, Date2))
			return enCompareDates::befor;

		return enCompareDates::equal;


	}

	bool IsLastDayInAMonth(sDate Date) {

		return Date.Day == NumberOfDaysInMonth(Date.Year, Date.Month);

	}

	bool IsLastMonthInAYear(short Month) {

		return Month == 12;

	}

	sDate IncreaseDateOneDay(sDate Date) {
		if (IsLastDayInAMonth(Date))
		{
			if (IsLastMonthInAYear(Date.Month))
			{
				Date.Year++;
				Date.Month = 1;
				Date.Day = 1;
			}

			else {
				Date.Month++;
				Date.Day = 1;
			}
		}

		else {
			Date.Day++;
		}

		return Date;

	}

	void SwapDates(sDate& Date1, sDate& Date2) {

		sDate Temp;

		Temp = Date1;
		Date1 = Date2;
		Date2 = Temp;


	}

	short CalculateDiffBetwenDate1AndDate2(sDate Date1, sDate Date2, bool including = false) {


		int Day = 0;
		int FalgValue = 1;
		if (!IsDate1BeforDate2(Date1, Date2)) {

			SwapDates(Date1, Date2);
			FalgValue = -1;

		}

		while (IsDate1BeforDate2(Date1, Date2)) {

			Day++;

			Date1 = IncreaseDateOneDay(Date1);
		}

		return including ? FalgValue * (++Day) : FalgValue * Day;

	}

	sDate GetSystemDate() {


		sDate ToDay;

		time_t t = time(0);
		tm* now = localtime(&t);

		ToDay.Year = now->tm_year + 1900;
		ToDay.Month = now->tm_mon + 1;
		ToDay.Day = now->tm_mday;

		return ToDay;
	}

	short DaysUntilTheEndOfWeek(short OrderDay) {

		return 6 - OrderDay;

	}

	short DaysUntilTheEndOfMonth(sDate Date) {
		//return NumberOfDaysInMonth(Date.Year, Date.Month) - Date.Day;

		sDate EndOfMonth;
		EndOfMonth.Day = NumberOfDaysInMonth(Date.Year, Date.Month);
		EndOfMonth.Month = Date.Month;
		EndOfMonth.Year = Date.Year;

		return CalculateDiffBetwenDate1AndDate2(Date, EndOfMonth, true);
	}

	short DaysUntilTheEndOfYear(sDate Date) {

		//short DaysOfYear = IsLeapYear(Date.Year) ? 366 : 365;

		//return DaysOfYear - TotalDaysFromBeginningYear(Date.Year, Date.Month, Date.Day);
		sDate EndOfYear;
		EndOfYear.Day = 31;
		EndOfYear.Month = 12;
		EndOfYear.Year = Date.Year;

		return CalculateDiffBetwenDate1AndDate2(Date, EndOfYear, true);

	}

	bool IsWeekEnd(short OrderDay) {

		return OrderDay == 5 || OrderDay == 6;

	}

	bool IsEndOfWeek(short OrderDay) {

		return OrderDay == 6;

	}

	bool IsBusinessDay(short OrderDay) {

		return !IsWeekEnd(OrderDay);

	}

	bool ReadTwoPeridsAndCheckOverlap(sPeriod Period1, sPeriod Period2) {

		if (
			CompareDates(Period2.End, Period1.Start) == enCompareDates::befor
			||
			CompareDates(Period2.Start, Period1.End) == enCompareDates::After
			)
			return false;
		else
			return true;

	}

	short PeriodLengthInDays(sPeriod Period, bool including = false) {

		return CalculateDiffBetwenDate1AndDate2(Period.Start, Period.End, including);

	}

	bool IsDateWithinPeriod(sPeriod Period1, sDate Date) {


		return   !(CompareDates(Date, Period1.Start) == enCompareDates::befor
			||
			CompareDates(Date, Period1.End) == enCompareDates::After);

	}

	int CountOverLap(sPeriod Period1, sPeriod Period2) {
		int Period1Length = PeriodLengthInDays(Period1, true);
		int Period2Length = PeriodLengthInDays(Period2, true);
		int CountOverLap = 0;

		if (!ReadTwoPeridsAndCheckOverlap(Period1, Period2)) {
			return 0;
		}
		if (Period1Length < Period2Length) {
			while (IsDate1BeforDate2(Period1.Start, Period1.End)) {

				if (IsDateWithinPeriod(Period2, Period1.Start))
					CountOverLap++;


				Period1.Start = IncreaseDateOneDay(Period1.Start);

			}
		}

		else {

			while (IsDate1BeforDate2(Period2.Start, Period2.End)) {

				if (IsDateWithinPeriod(Period1, Period2.Start))
					CountOverLap++;


				Period2.Start = IncreaseDateOneDay(Period2.Start);

			}

		}

		return CountOverLap;
	}

	bool ValidateDate(sDate Date)
	{
		/*return (Date.Month <= 12 && Date.Month >= 1) && (Date.Day <= NumberOfDaysInMonth(Date.Year, Date.Month) && Date.Day >= 1);*/
		//my sultion.

		if (Date.Day < 1 || Date.Day >31)
			return false;

		if (Date.Month < 1 || Date.Month > 12)
			return false;

		if (Date.Month == 2) {

			if (IsLeapYear(Date.Year))
			{

				if (Date.Day > 29)
					return false;

			}
			else {
				if (Date.Day > 28)
					return false;
			}


		}

		short DaysInMonth = NumberOfDaysInMonth(Date.Year, Date.Month);
		if (Date.Day > DaysInMonth)
			return false;

		return true;
	}



}



