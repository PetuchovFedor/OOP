#pragma once
#include <stdexcept>
#include <string>

class EmptyStackExpression : public std::logic_error
{
public:
	EmptyStackExpression(const std::string& message);

};