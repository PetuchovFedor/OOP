#include "EmptyStackExpression.h"

EmptyStackExpression::EmptyStackExpression(const std::string& message)
	:std::logic_error(message)
{
}