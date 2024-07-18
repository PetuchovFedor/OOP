#pragma once
#include "IPerson.h"

class IStudent : public IPerson
{
public:
	virtual std::string GetUniversityName() const = 0;
	virtual std::string GetStudentId() const = 0;
};