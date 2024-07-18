#pragma once
#include <string>

class IPerson
{
public:
	virtual ~IPerson() = default;
	virtual std::string GetSurname() const = 0;
	virtual std::string GetName() const = 0;
	virtual std::string GetMiddleName() const = 0;
	virtual std::string GetAddress() const = 0;
};