#pragma once
#include "CPersonImpl.h"

template <typename Base>
class CStudentImpl : public CPersonImpl<Base>
{
public:
	CStudentImpl(
		const std::string& surname,
		const std::string& name,
		const std::string& middleName,
		const std::string& address,
		const std::string& universityName,
		const std::string& studentId)
		: CPersonImpl<Base>(surname, name, middleName, address)
		, m_universityName(universityName)
		, m_studentId(studentId)
	{}
	CStudentImpl(
		const std::string& SNMN, 
		const std::string& address,
		const std::string& universityName,
		const std::string& studentId)
		: CPersonImpl<Base>(SNMN, address)
		, m_universityName(universityName)
		, m_studentId(studentId)
	{}

	std::string GetUniversityName() const override
	{
		return m_universityName;
	}

	std::string GetStudentId() const override
	{
		return m_studentId;
	}

private:
	std::string m_universityName;
	std::string m_studentId;
};
	
