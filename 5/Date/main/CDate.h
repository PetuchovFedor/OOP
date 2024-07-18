#pragma once
#include <sstream>
// �����
enum class Month
{
	JANUARY = 1, FEBRUARY, MARCH, APRIL,
	MAY, JUNE, JULY, AUGUST, SEPTEMBER,
	OCTOBER, NOVEMBER, DECEMBER
};

// ���� ������
enum class WeekDay
{
	SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
	THURSDAY, FRIDAY, SATURDAY
};

class CDate
{
public:
	// ����������: ��� >= 1970
	CDate(unsigned day, Month month, unsigned year);

	// �������������� ���� ����������� ����, ��������� ����� 1 ������ 1970 ����
	// ��������, 2 = 3 ������ 1970, 32 = 2 ������� 1970 ���� � �.�.
	explicit CDate(unsigned timestamp = 0);

	// ���������� ���� ������ (�� 1 �� 31)
	unsigned GetDay() const;

	// ���������� �����
	Month GetMonth() const;

	// ���������� ���
	unsigned GetYear() const;

	// ���������� ���� ������
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