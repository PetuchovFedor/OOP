#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../main/prefixExpression.h"

using namespace std;

SCENARIO("argument is one number with operator")
{
	string str = "(+ 7)";
	REQUIRE(CalculatePrefixExpression(str) == 7);
}
SCENARIO("argument is one number without operator")
{
	string str = "7";
	REQUIRE(CalculatePrefixExpression(str) == 7);
}

SCENARIO("argument is two number with operator plus")
{
	string str = "(+ 2 3)";
	REQUIRE(CalculatePrefixExpression(str) == 5);
}

SCENARIO("argument is two number with operator plus and negative number")
{
	string str = "(+ -2 3)";
	REQUIRE(CalculatePrefixExpression(str) == 1);
}

SCENARIO("argument is two number with operator miltiplication")
{
	string str = "(* 2 3)";
	REQUIRE(CalculatePrefixExpression(str) == 6);
}

SCENARIO("argument is three number with operator plus")
{
	string str = "(+ 2 3 5)";
	REQUIRE(CalculatePrefixExpression(str) == 10);
}

SCENARIO("argument is  three number with operator miltiplication")
{
	string str = "(* 2 3 5 )";
	REQUIRE(CalculatePrefixExpression(str) == 30);
}

SCENARIO("argument is expression with some operators")
{
	string str = "(+ (* 2 3) (* 3 4))";
	REQUIRE(CalculatePrefixExpression(str) == 18);
}

SCENARIO("argument is big expression with some operators")
{
	string str = "(+ 5 (* 2 3 2) (+ 5 (+ 2 5) (* 2 2) ))";
	REQUIRE(CalculatePrefixExpression(str) == 33);
}

SCENARIO("Argument is expession with bog operands")
{
	string str = "(+ 100 100)";
	REQUIRE(CalculatePrefixExpression(str) == 200)
}