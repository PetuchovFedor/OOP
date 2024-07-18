#include "CTeacher.h"

CTeacher::CTeacher(const std::string& SNMN, const std::string& address, const std::string& subject)
	: CPersonImpl(SNMN, address)
	, m_subject(subject)
{
}

CTeacher::CTeacher(
	const std::string& surname, 
	const std::string& name, 
	const std::string& middleName, 
	const std::string& address, 
	const std::string& subject)
	:CPersonImpl(surname, name, middleName, address)
	, m_subject(subject)
{
}

std::string CTeacher::GetSubject() const
{
	return m_subject;
}
