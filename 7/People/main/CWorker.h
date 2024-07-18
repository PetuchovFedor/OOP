#pragma once
#include "CPersonImpl.h"
#include "IWorker.h"

class CWorker : public CPersonImpl <IWorker>
{
public:
	CWorker(const std::string& SNMN, const std::string& address, const std::string& specialization);

	CWorker(
		const std::string& surname,
		const std::string& name,
		const std::string& middleName,
		const std::string& address,
		const std::string& specialization);

	std::string GetSpecialization() const override;

private:
	std::string m_specialization;
};
