#include "CPerson.h"

CPerson::CPerson(
	const std::string& surname, 
	const std::string& name, 
	const std::string& middleName, 
	const std::string& address)
	: CPersonImpl(surname, name, middleName, address)
{
}

CPerson::CPerson(const std::string& SNMN, const std::string& address)
	:CPersonImpl(SNMN, address)
{
}
