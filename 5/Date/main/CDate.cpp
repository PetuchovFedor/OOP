#include "CDate.h"
#include <stdexcept>
#include <sstream>
// не лучша€ иде€
using namespace std;

namespace
{
	const unsigned YEARS_IN_ERA = 400;

	const unsigned DAYS_IN_ERA = 146097;

	const unsigned DAYS_IN_FIRST_CENTURY_ERA = 36524;

	const unsigned DAYS_FROM_BEGIN_TO_1970 = 719468; // begin: 01:03:0000;

	const unsigned DAYS_IN_YEAR = 365;

	const unsigned MAX_DAYS_AFTER_1970 = 2932896;
}

CDate::CDate(unsigned day, Month month, unsigned year)
{
	if (IsValid(day, month, year))
		m_countDaysAfter1970 = CountDaysAfter1970(day, month, year);
	else
		throw out_of_range("Dates are out of range 01:01:1970 Ц 31:12:9999");
}

CDate::CDate(unsigned timestamp)
{
	if (IsValid(timestamp))
		m_countDaysAfter1970 = timestamp;
	else
		throw out_of_range("Dates are out of range 01:01:1970 Ц 31:12:9999");
}

// dauOfYEar в отдельный метод b dsxbcktybt vtczwf
unsigned CDate::GetDay() const
{
	unsigned dayOfEra = GetDayOfEra();
	unsigned yearOfEra = GetYearOfEra();
	unsigned dayOfYear = dayOfEra - (DAYS_IN_YEAR * yearOfEra + yearOfEra / 4 - yearOfEra / 100);
	unsigned month = (5 * dayOfYear + 2) / 153;
	return dayOfYear - (153 * month + 2) / 5 + 1;
}

Month CDate::GetMonth() const
{
	unsigned dayOfEra = GetDayOfEra();
	unsigned yearOfEra = GetYearOfEra();
	unsigned dayOfYear = dayOfEra - (DAYS_IN_YEAR * yearOfEra + yearOfEra / 4 - yearOfEra / 100);
	unsigned month = (5 * dayOfYear + 2) / 153;
	return month < 10 ? static_cast<Month>(month + 3) : month == 10 ? Month::JANUARY : Month::FEBRUARY;
}

unsigned CDate::GetYear() const
{
	unsigned year = GetYearOfEra() + GetCurrentEra() * YEARS_IN_ERA;
	return (GetMonth() <= Month::FEBRUARY) ? ++year : year;
}

WeekDay CDate::GetWeekDay() const
{
	return static_cast<WeekDay>((m_countDaysAfter1970 + 4) % 7);
}

CDate& CDate::operator++()
{
	++m_countDaysAfter1970;
	if (m_countDaysAfter1970 > MAX_DAYS_AFTER_1970)
	{
		throw out_of_range("Dates are out of range 01:01:1970 Ц 31:12:9999");
	}
	return *this;
}

CDate CDate::operator++(int)
{
	CDate tmpCopy(m_countDaysAfter1970);
	++m_countDaysAfter1970;
	if (m_countDaysAfter1970 > MAX_DAYS_AFTER_1970)
	{
		throw out_of_range("Dates are out of range 01:01:1970 Ц 31:12:9999");
	}
	return tmpCopy;
}

CDate& CDate::operator--()
{
	--m_countDaysAfter1970;
	if (m_countDaysAfter1970 > MAX_DAYS_AFTER_1970)
	{
		throw out_of_range("Dates are out of range 01:01:1970 Ц 31:12:9999");
	}
	return *this;
}

CDate CDate::operator--(int)
{
	CDate tmpCopy(m_countDaysAfter1970);
	--m_countDaysAfter1970;
	if (m_countDaysAfter1970 > MAX_DAYS_AFTER_1970)
	{
		throw out_of_range("Dates are out of range 01:01:1970 Ц 31:12:9999");
	}
	return tmpCopy;
}

CDate CDate::operator+(unsigned days)
{
	CDate tmpCopy(m_countDaysAfter1970 + days);
	return tmpCopy;
}

CDate CDate::operator-(unsigned days)
{
	CDate tmpCopy(m_countDaysAfter1970 - days);
	return tmpCopy;
}

int CDate::operator-(const CDate& date) const
{
	return m_countDaysAfter1970 - date.m_countDaysAfter1970;
}

CDate& CDate::operator+=(unsigned days)
{
	m_countDaysAfter1970 += days;
	if (m_countDaysAfter1970 > MAX_DAYS_AFTER_1970)
	{
		throw out_of_range("Dates are out of range 01:01:1970 Ц 31:12:9999");
	}
	return *this;
}

CDate& CDate::operator-=(unsigned days)
{
	m_countDaysAfter1970 -= days;
	if (m_countDaysAfter1970 > MAX_DAYS_AFTER_1970)
	{
		throw out_of_range("Dates are out of range 01:01:1970 Ц 31:12:9999");
	}
	return *this;
}

bool CDate::operator==(const CDate & other) const
{
	return m_countDaysAfter1970 == other.m_countDaysAfter1970;
}

bool CDate::operator!=(const CDate & other) const
{
	return m_countDaysAfter1970 != other.m_countDaysAfter1970;
}

bool CDate::operator>(const CDate& other) const
{
	return m_countDaysAfter1970 > other.m_countDaysAfter1970;
}

bool CDate::operator<(const CDate & other) const
{
	return m_countDaysAfter1970 <  other.m_countDaysAfter1970;
}

bool CDate::operator>=(const CDate & other) const
{
	return m_countDaysAfter1970 >= other.m_countDaysAfter1970;
}

bool CDate::operator<=(const CDate & other) const
{
	return m_countDaysAfter1970 <= other.m_countDaysAfter1970;
}

bool CDate::IsValid(unsigned day, Month month, unsigned year) const
{
	return (day >= 1 && day <= 31) && (static_cast<unsigned>(month) >= 1 && static_cast<unsigned>(month) <= 12) &&
		(year >= 1970 && year <= 9999);
}

bool CDate::IsValid(unsigned day) const
{
	return day >= 0 && day <= MAX_DAYS_AFTER_1970;
}

unsigned CDate::CountDaysAfter1970(unsigned day, Month month, unsigned year) const
{
	unsigned m = static_cast<unsigned>(month);
	// передулать в тернарный оператор
	year -= m <= 2;
	unsigned era = year / YEARS_IN_ERA;
	unsigned yearOfEra = year - era * YEARS_IN_ERA; // [0, 399]  
	unsigned dayOfYear = (153 * (m > 2 ? m - 3 : m + 9) + 2) / 5 + day - 1; // [0, 365]  
	unsigned dayOfEra = yearOfEra * DAYS_IN_YEAR + yearOfEra /4 - yearOfEra /100 + dayOfYear; // [0, 146096]
	return era * DAYS_IN_ERA + dayOfEra - DAYS_FROM_BEGIN_TO_1970;
}

unsigned CDate::GetCurrentEra() const
{
	return (m_countDaysAfter1970 + DAYS_FROM_BEGIN_TO_1970) / DAYS_IN_ERA;
}

unsigned CDate::GetDayOfEra() const
{
	unsigned era = GetCurrentEra();
	return m_countDaysAfter1970 + DAYS_FROM_BEGIN_TO_1970 - era * DAYS_IN_ERA;
}

unsigned CDate::GetYearOfEra() const
{
	unsigned dayOfEra = GetDayOfEra();
	return (dayOfEra - dayOfEra / 1460 + dayOfEra / DAYS_IN_FIRST_CENTURY_ERA - dayOfEra / (DAYS_IN_ERA - 1)) / DAYS_IN_YEAR;
}

std::istream& operator>>(std::istream& input, CDate& date)
{
	unsigned day = 0, month = 0, year = 0;
	if (input >> day && input.get() == '.' &&
		input >> month && input.get() == '.' &&
		input >> year)
	{
		date = CDate(day, static_cast<Month>(month), year);
	}
	else
		input.setstate(std::ios_base::failbit | input.rdstate());
	return input;
}

std::ostream& operator<<(std::ostream& output, const CDate& date)
{
	output << date.GetDay() << '.' << static_cast<unsigned>(date.GetMonth()) << '.' << date.GetYear();
	return output;
}
