#include "CAdvancedStudent.h"

CAdvancedStudent::CAdvancedStudent(
	const std::string& surname, 
	const std::string& name, 
	const std::string& middleName, 
	const std::string& address, 
	const std::string& universityName, 
	const std::string& studentId, 
	const std::string& dissertationTopic)
	: CStudentImpl<IAdvancedStudent>(surname, name, middleName, address, universityName, studentId)
	, m_dissertationTopic(dissertationTopic)
{
}

CAdvancedStudent::CAdvancedStudent(
	const std::string& SNMN, 
	const std::string& address, 
	const std::string& universityName, 
	const std::string& studentId, 
	const std::string& dissertationTopic)
	: CStudentImpl<IAdvancedStudent>(SNMN, address, universityName, studentId)
	, m_dissertationTopic(dissertationTopic)
{
}

std::string CAdvancedStudent::GetDissertationTopic() const
{
	return m_dissertationTopic;
}
