#pragma once
#include "IPerson.h"
#include "CPersonImpl.h"

class CPerson : public CPersonImpl<IPerson>
{
public:
	CPerson(
		const std::string& surname,
		const std::string& name,
		const std::string& middleName,
		const std::string& address);
	CPerson(const std::string& SNMN, const std::string& address);

};