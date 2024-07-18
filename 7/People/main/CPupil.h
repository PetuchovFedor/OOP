#pragma once
#include "CPersonImpl.h"
#include "IPupil.h"

class CPupil : public CPersonImpl<IPupil>
{
public:
	CPupil(const std::string& SNMN, const std::string& address, const std::string& schoolName, const std::string& group);

	CPupil(
		const std::string& surname,
		const std::string& name,
		const std::string& middleName,
		const std::string& address,
		const std::string& schoolName,
		const std::string& group);

	std::string GetSchoolName() const override;

	std::string GetGroup() const override;

private:
	std::string m_schoolName;
	std::string m_group;
};