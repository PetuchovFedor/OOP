#include "CMyString.h"
#include <stdexcept>
#include <algorithm>
#include <sstream>

namespace
{
	int Compare(char* first, char* second)
	{
		//Доработать
		auto minSizeStr = std::min(first, second);
		return memcmp(first, second, strlen(minSizeStr));
	}
}

CMyString::CMyString()
{
	m_size = 0;
	m_str = new char[1];
	m_str[0] = '\0';
}

CMyString::CMyString(const char* pString)
{
	//Использовать коструктор с указателем и длиной
	m_size = strlen(pString);
	m_str = new char [m_size + 1];
	memcpy(m_str, pString, m_size);
	m_str[m_size] = '\0';
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_size = length;
	m_str = new char [m_size + 1];
	memcpy(m_str, pString, m_size);
	m_str[m_size] = '\0';
}

CMyString::CMyString(CMyString const& other)
	: m_size(other.m_size)
	, m_str(new char [other.m_size + 1])
{
	if (m_size != 0)
	{
		//Дублирование присваиванмя /0
		memcpy(m_str, other.m_str, m_size);
		m_str[m_size] = '\0';
	}
	else
		m_str[0] = '\0';
}

CMyString::CMyString(CMyString&& other)
	: m_size(other.m_size) 
	, m_str(other.m_str)
{
	other.m_size = 0;
	other.m_str = nullptr;
}

CMyString::CMyString(std::string const& stlString)
{
	//Дублирование memcpy
	m_size = stlString.size();
	m_str = new char[m_size + 1];
	memcpy(m_str, stlString.c_str(), m_size);
	m_str[m_size] = '\0';
}

CMyString::~CMyString()
{
	Clear();
}

size_t CMyString::GetLength() const
{
	return m_size;
}

const char* CMyString::GetStringData() const
{
	if (m_size == 0)
	{
		const char* ch = "\0";
		return ch;
	}
	return m_str;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	//Дописать тесты и подправить
	if (start > m_size || length > m_size)
		throw std::out_of_range("Parameters beyond the length of the string");
	const char* ch = &m_str[start];
	return CMyString(ch, length);
}

void CMyString::Clear()
{
	delete[] m_str;
	m_str = nullptr;
	m_size = 0;
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (std::addressof(other) != this)
	{
		CMyString tmpCopy(other);
		std::swap(m_str, tmpCopy.m_str);
		m_size = other.m_size;
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other)
{
	if (&other != this)
	{
		//через конструктор перемещения
		delete[] m_str;
		m_str = other.m_str;
		m_size = other.m_size;
		other.m_str = NULL;
		other.m_size = 0;
	}
	return *this;

}

CMyString CMyString::operator+(CMyString const& other) const
{
	size_t resSize = m_size + other.m_size;
	char* res = new char[resSize + 1];
	memcpy(res, m_str, m_size);
	memcpy(res + m_size, other.m_str, other.m_size);
	//Утечка памяти в случае исключения
	return CMyString(res, resSize);
}

CMyString& CMyString::operator+=(CMyString const& other)
{
	*this = *this + other;
	return *this;
}

bool CMyString::operator==(const CMyString& other) const
{
	//Лишние ветвления
	if (Compare(m_str, other.m_str) == 0)
		return true;
	return false;
}

bool CMyString::operator!=(const CMyString& other) const
{
	if (Compare(m_str, other.m_str) != 0)
		return true;
	return false;
}

bool CMyString::operator<(const CMyString& other) const
{
	if (Compare(m_str, other.m_str) < 0)
		return true;
	return false;
}

bool CMyString::operator>(const CMyString& other) const
{
	if (Compare(m_str, other.m_str) > 0)
		return true;
	return false;
}

bool CMyString::operator<=(const CMyString& other) const
{
	if (Compare(m_str, other.m_str) <= 0)
		return true;
	return false;
}

bool CMyString::operator>=(const CMyString& other) const
{
	if (Compare(m_str, other.m_str) >= 0)
		return true;
	return false;
}

const char& CMyString::operator[](size_t index) const
{
	if (index >= m_size)
		throw std::out_of_range("CMyString subscript out of range");
	return m_str[index];
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_size)
		throw std::out_of_range("CMyString subscript out of range");
	return m_str[index];
}

const CMyString operator+(std::string const& stlString, CMyString const& myString)
{
	return CMyString(stlString) + myString;
}

const CMyString operator+(const char* charString, CMyString const& myString)
{
	return CMyString(charString) + myString;
}

std::istream& operator>>(std::istream& input, CMyString& myString)
{
	if (input.eof())
		return input;
	std::string str;
	if (input >> str)
		myString = CMyString(str);
	else
		input.setstate(std::ios_base::failbit | input.rdstate());
	return input;
}
std::ostream& operator<<(std::ostream& output, CMyString const& myString)
{
	output << myString.GetStringData();
	return output;
}
