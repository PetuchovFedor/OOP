#pragma once
#include <string>
#include <sstream>

template<typename Base>
class CPersonImpl : public Base
{
public:
	CPersonImpl(
		const std::string& surname,
		const std::string& name,
		const std::string& middleName,
		const std::string& address)
		: m_surname(surname)
		, m_name(name)
		, m_middleName(middleName)
		, m_address(address)
	{}
	CPersonImpl(const std::string& SNMN, const std::string& address)
	{
		std::stringstream ss(SNMN);
		std::string str;
		ss >> str;
		m_surname = str;
		ss >> str;
		m_name = str;
		ss >> str;
		m_middleName = str;
		m_address = address;
	}

	std::string GetSurname() const override
	{
		return m_surname;
	}

	std::string GetName() const override
	{
		return m_name;
	}

	std::string GetMiddleName() const override
	{
		return m_middleName;
	}

	std::string GetAddress() const override
	{
		return m_address;
	}

private:
	std::string m_surname;
	std::string m_name;
	std::string m_middleName;
	std::string m_address;

};