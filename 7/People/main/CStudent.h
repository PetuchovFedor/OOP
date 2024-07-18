#pragma once
#include "IStudent.h"
#include "CStudentImpl.h"

class CStudent : public CStudentImpl<IStudent>
{
public:
	CStudent(
		const std::string& surname,
		const std::string& name,
		const std::string& middleName,
		const std::string& address,
		const std::string& universityName,
		const std::string& studentId)
		: CStudentImpl<IStudent>(surname, name, middleName, address, universityName, studentId)
	{}
	CStudent(
		const std::string& SNMN,
		const std::string& address,
		const std::string& universityName,
		const std::string& studentId)
		: CStudentImpl<IStudent>(SNMN, address, universityName, studentId)
	{}
};