#pragma once
#include "IAdvancedStudent.h"
#include "CStudentImpl.h"

class CAdvancedStudent : public CStudentImpl<IAdvancedStudent>
{
public:
	CAdvancedStudent(
		const std::string& surname,
		const std::string& name,
		const std::string& middleName,
		const std::string& address,
		const std::string& universityName,
		const std::string& studentId,
		const std::string& dissertationTopic);

	CAdvancedStudent(
		const std::string& SNMN,
		const std::string& address,
		const std::string& universityName,
		const std::string& studentId,
		const std::string& dissertationTopic);

	std::string GetDissertationTopic() const override;

private:
	std::string m_dissertationTopic;
};