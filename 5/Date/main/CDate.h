#pragma once
#include <sstream>
// ћес€ц
enum class Month
{
	JANUARY = 1, FEBRUARY, MARCH, APRIL,
	MAY, JUNE, JULY, AUGUST, SEPTEMBER,
	OCTOBER, NOVEMBER, DECEMBER
};

// ƒень недели
enum class WeekDay
{
	SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
	THURSDAY, FRIDAY, SATURDAY
};

class CDate
{
public:
	// примечание: год >= 1970
	CDate(unsigned day, Month month, unsigned year);

	// инициализируем дату количеством дней, прошедших после 1 €нвар€ 1970 года
	// например, 2 = 3 €нвар€ 1970, 32 = 2 феврал€ 1970 года и т.д.
	explicit CDate(unsigned timestamp = 0);

	// возвращает день мес€ца (от 1 до 31)
	unsigned GetDay() const;

	// возвращает мес€ц
	Month GetMonth() const;

	// возвращает год
	unsigned GetYear() const;

	// возвращает день недели
	WeekDay GetWeekDay() const;

	CDate& operator++();
	
	CDate operator++(int);

	CDate& operator--();

	CDate operator--(int);

	CDate operator+(unsigned days);

	CDate operator-(unsigned days);
	
	int operator-(const CDate & date) const;

	CDate& operator+=(unsigned days);

	CDate& operator-=(unsigned days);

	bool operator==(const CDate& other) const;

	bool operator!=(const CDate & other) const;

	bool operator>(const CDate & other) const;

	bool operator<(const CDate & other) const;

	bool operator>=(const CDate & other) const;

	bool operator<=(const CDate & other) const;

	friend std::istream& operator>>(std::istream& input, CDate& date);

	friend std::ostream& operator<<(std::ostream& output, const CDate& date);

private:
	bool IsValid(unsigned day, Month month, unsigned year) const;

	bool IsValid(unsigned day) const;

	unsigned CountDaysAfter1970(unsigned day, Month month, unsigned year) const;

	unsigned GetCurrentEra() const;

	unsigned GetDayOfEra() const;

	unsigned GetYearOfEra() const;
private:
	unsigned m_countDaysAfter1970;
};