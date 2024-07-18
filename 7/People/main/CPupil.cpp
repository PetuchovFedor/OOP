#include "CPupil.h"

CPupil::CPupil(
	const std::string& SNMN,
	const std::string& address,
	const std::string& schoolName,
	const std::string& group)
	: CPersonImpl(SNMN, address)
	, m_schoolName(schoolName)
	, m_group(group)
{
}

CPupil::CPupil(
	const std::string& surname, 
	const std::string& name, 
	const std::string& middleName, 
	const std::string& address, 
	const std::string& schoolName, 
	const std::string& group)
	: CPersonImpl(surname, name, middleName, address)
	, m_schoolName(schoolName)
	, m_group(group)
{
}

std::string CPupil::GetSchoolName() const
{
	return m_schoolName;
}

std::string CPupil::GetGroup() const
{
	return m_group;
}
