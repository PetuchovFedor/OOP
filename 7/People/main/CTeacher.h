#pragma once
#include "CPersonImpl.h"
#include "ITeacher.h"

class CTeacher : public CPersonImpl<ITeacher>
{
public:
	CTeacher(const std::string& SNMN, const std::string& address, const std::string& subject);

	CTeacher(
		const std::string& surname,
		const std::string& name,
		const std::string& middleName,
		const std::string& address,
		const std::string& subject);

	std::string GetSubject() const override;
private:
	std::string m_subject;
};
