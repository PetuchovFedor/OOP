#include "CWorker.h"

CWorker::CWorker(const std::string& SNMN, const std::string& address, const std::string& specialization)
	: CPersonImpl(SNMN, address)
	, m_specialization(specialization)
{
}

CWorker::CWorker(
	const std::string& surname, 
	const std::string& name, 
	const std::string& middleName, 
	const std::string& address,
	const std::string& specialization)
	:CPersonImpl(surname, name, middleName, address)
	, m_specialization(specialization)
{
}

std::string CWorker::GetSpecialization() const
{
	return m_specialization;
}
