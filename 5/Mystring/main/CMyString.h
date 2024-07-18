#pragma once
#include <string>

class CMyString
{
public:
	// ����������� �� ���������
	CMyString();

	// �����������, ���������������� ������ ������� ������
// � ����������� ������� ��������
	CMyString(const char* pString);

	// �����������, ���������������� ������ ������� �� 
// ����������� ������� �������� �����
	CMyString(const char* pString, size_t length);

	// ����������� �����������
	CMyString(CMyString const& other);

	// ������������ ����������� (��� ������������, ����������� � C++11)
	//  ����������� ��������� � ������������ ���������� ������������ 
	CMyString(CMyString&& other);

	// �����������, ���������������� ������ ������� �� 
// ������ ����������� ���������� C++
	CMyString(std::string const& stlString);

	// ���������� ������ - ����������� ������, ���������� ��������� ������
	~CMyString();

	// ���������� ����� ������ (��� ����� ������������ �������� �������)
	size_t GetLength()const;

	// ���������� ��������� �� ������ �������� ������.
	// � ����� ������� ����������� ������ ���� ����������� ������� ������
	// ���� ���� ������ ������ 
	const char* GetStringData()const;

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	CMyString SubString(size_t start, size_t length) const;

	// ������� ������ (������ ���������� ����� ������� �����)
	void Clear();

	CMyString& operator =(CMyString const& other);

	CMyString& operator=(CMyString&& other);

	CMyString operator +(CMyString const& other) const;

	CMyString& operator+=(CMyString const& other);

	bool operator==(const CMyString& other) const;

	bool operator!=(const CMyString& other) const;

	bool operator<(const CMyString & other) const;

	bool operator>(const CMyString& other) const;

	bool operator<=(const CMyString& other) const;

	bool operator>=(const CMyString& other) const;

	const char& operator[](size_t index) const;

	char& operator[](size_t index);

private:

	char* m_str;
	size_t m_size = 0;
};

const CMyString operator+(std::string const& stlString, CMyString const& myString);

const CMyString operator+(const char* charString, CMyString const& myString);

std::istream& operator>>(std::istream& input, CMyString& myString);

std::ostream& operator<<(std::ostream& output, CMyString const& myString);
