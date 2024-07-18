#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/CDate.h"
#include <iostream>
using namespace std;

TEST_CASE("Begin date(01.01.1970)")
{
	WHEN("Date")
	{
		CDate date;
		THEN("day is 1")
		{
			REQUIRE(date.GetDay() == 1);
		}
		THEN("month is 1")
		{
			REQUIRE(date.GetMonth() == Month::JANUARY);
		}
		THEN("year is 1970")
		{
			REQUIRE(date.GetYear() == 1970);
		}
		THEN("week day is")
		{
			REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
		}
		THEN("exceprion with minus")
		{
			REQUIRE_THROWS(date--);
			REQUIRE_THROWS(--date);
			REQUIRE_THROWS(date -= 2);
		}
	}
}

TEST_CASE("End date(31.12.9999)")
{
	WHEN("Date")
	{
		CDate date(31, Month::DECEMBER, 9999);
		THEN("day is 31")
		{
			REQUIRE(date.GetDay() == 31);
		}
		THEN("month is december")
		{
			REQUIRE(date.GetMonth() == Month::DECEMBER);
		}
		THEN("year is 9999")
		{
			REQUIRE(date.GetYear() == 9999);
		}
		THEN("week day is")
		{
			REQUIRE(date.GetWeekDay() == WeekDay::FRIDAY);
		}
		THEN("exception with plus")
		{
			REQUIRE_THROWS(date++);
			REQUIRE_THROWS(++date);
			REQUIRE_THROWS(date += 3);
		}
	}
}

TEST_CASE("Check today date")
{
	WHEN("date 14.05.2023")
	{
		CDate date(19491);
		THEN("day is 14")
		{
			REQUIRE(date.GetDay() == 14);
		}
		THEN("month is may")
		{
			REQUIRE(date.GetMonth() == Month::MAY);
		}
		THEN("year is 2023")
		{
			REQUIRE(date.GetYear() == 2023);
		}
		THEN("week day is sunday")
		{
			REQUIRE(date.GetWeekDay() == WeekDay::SUNDAY);
		}
	}
}

TEST_CASE("operations with date")
{
	WHEN("Date")
	{
		CDate date(20, Month::OCTOBER, 3980);
		THEN("Plus")
		{
			CDate tmp = date++;
			REQUIRE(date.GetDay() == 21);
			REQUIRE(tmp.GetDay() == 20);
			tmp = ++date;
			REQUIRE(date.GetDay() == tmp.GetDay());
			tmp += 5;
			REQUIRE(tmp.GetDay() == 27);
			date = tmp + 10;
			REQUIRE(date.GetDay() == 6);
			REQUIRE(date.GetMonth() == Month::NOVEMBER);
			date += 364;
			REQUIRE(date.GetYear() == 3981);
		}
		THEN("Minus")
		{
			CDate tmp = date--;
			REQUIRE(date.GetDay() == 19);
			REQUIRE(tmp.GetDay() == 20);
			tmp = --date;
			REQUIRE(date.GetDay() == tmp.GetDay());
			tmp -= 10;
			REQUIRE(tmp.GetDay() == 8);
			date = tmp - 10;
			REQUIRE(date.GetDay() == 28);
			REQUIRE(date.GetMonth() == Month::SEPTEMBER);
			REQUIRE(tmp - date == 10);
			REQUIRE(date - tmp == -10);
			date -= 364;
			REQUIRE(date.GetYear() == 3979);
		}
		THEN("compare operations")
		{
			CDate date1(3456);
			CDate date2(3455);
			REQUIRE(date1 > date2);
			REQUIRE(date2 < date1);
			REQUIRE(date2 != date1);
			date2++;
			REQUIRE(date1 >= date2);
			REQUIRE(date2 <= date1);
			REQUIRE(date2 == date1);
		}
		THEN("input");
		{
			istringstream inp("15.09.2004");
			CDate d;
			inp >> d;
			REQUIRE(d.GetDay() == 15);
			REQUIRE(d.GetMonth() == Month::SEPTEMBER);
			REQUIRE(d.GetYear() == 2004);
		}
		THEN("output")
		{
			ostringstream out;
			out << date;
			REQUIRE(out.str() == "20.10.3980");
		}
	}
}

SCENARIO("exception with creation")
{
	CDate date;
	istringstream strm("32.99.1874");
	REQUIRE_THROWS(strm >> date);
}

SCENARIO("leap year")
{
	CDate date;
	istringstream strm("29.02.2024");
	REQUIRE(strm >> date);
	date++;
	REQUIRE(date.GetDay() == 1);
	REQUIRE(date.GetMonth() == Month::MARCH);
	date -= 2;
	REQUIRE(date.GetDay() == 28);
	REQUIRE(date.GetMonth() == Month::FEBRUARY);
}