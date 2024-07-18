#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include <iostream>
#include "../main/CCalculator.h"
using namespace std;

SCENARIO("Create a new valid variable")
{
	CCalculator calculator;
	string str = "X";
	REQUIRE(calculator.AddNewVar(str));
	str = "X_1";
	REQUIRE(calculator.AddNewVar(str));
	str = "vars";
	REQUIRE(calculator.AddNewVar(str));
}

SCENARIO("Create a new non-vaid variable")
{
	CCalculator calculator;
	string str = "1X";
	REQUIRE(!calculator.AddNewVar(str));
	str = "X#$";
	REQUIRE(!calculator.AddNewVar(str));
	str = "X Y";
	REQUIRE(!calculator.AddNewVar(str));
	str = "";
	REQUIRE(!calculator.AddNewVar(str));
}

SCENARIO("Create an existing variable")
{
	CCalculator calculator;
	string str = "X";
	calculator.AddNewVar(str);
	REQUIRE(!calculator.AddNewVar(str));
}

SCENARIO("Set an existing variable a value")
{
	CCalculator calculator;
	string str = "X";
	calculator.AddNewVar(str);
	string val = "2.5";
	REQUIRE(calculator.SetVarValue(str, val));
}

SCENARIO("Set a non-existing variable a value")
{
	CCalculator calculator;
	string val = "2.5";
	REQUIRE(calculator.SetVarValue("str", val));
}

SCENARIO("Set an existing variable, which has value a  new value")
{
	CCalculator calculator;
	string str = "X";
	string val = "2.5";
	calculator.SetVarValue(str, val);
	val = "3.12";
	REQUIRE(calculator.SetVarValue(str, val));
}

SCENARIO("Set a non-existing non-valid variable a value")
{
	CCalculator calculator;
	string val = "2.5";
	REQUIRE(!calculator.SetVarValue("1str", val));
	REQUIRE(!calculator.SetVarValue("str eqw", val));
	REQUIRE(!calculator.SetVarValue("", val));
}

SCENARIO("Add function: fn = op1 + op2")
{
	CCalculator calcuator;
	string val1 = "2.45";
	string val2 = "5.34";
	calcuator.SetVarValue("var1", val1);
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	REQUIRE(calcuator.AddFunction("Plus", expr));
}

SCENARIO("Add function: fn1 = op")
{
	CCalculator calcuator;
	string val1 = "2.45";
	string val2 = "5.34";
	calcuator.SetVarValue("var1", val1);
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	CCalculator::expression expr1;
	expr1.first = ' ';
	expr1.second.first = "var2";
	REQUIRE(calcuator.AddFunction("FN", expr1));
}

SCENARIO("Add function: fn1 = fn")
{
	CCalculator calcuator;
	string val1 = "2.45";
	string val2 = "5.34";
	calcuator.SetVarValue("var1", val1);
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	CCalculator::expression expr1;
	expr1.first = ' ';
	expr1.second.first = "Plus";
	REQUIRE(calcuator.AddFunction("FN", expr1));
}

SCENARIO("Add function: fn1 = fn * op")
{
	CCalculator calcuator;
	string val1 = "2.45";
	string val2 = "5.34";
	calcuator.SetVarValue("var1", val1);
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	CCalculator::expression expr1;
	expr1.first = '*';
	expr1.second.first = "Plus";
	expr1.second.second = "var2";
	REQUIRE(calcuator.AddFunction("FN", expr1));
}

SCENARIO("Add function: fn1 = fn - fn0")
{
	CCalculator calcuator;
	string val1 = "2.45";
	string val2 = "5.34";
	calcuator.SetVarValue("var1", val1);
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	CCalculator::expression expr1;
	expr1.first = '*';
	expr1.second.first = "Plus";
	expr1.second.second = "var2";
	calcuator.AddFunction("Fn0", expr1);
	CCalculator::expression expr2;
	expr2.first = '-';
	expr2.second.first = "Plus";
	expr2.second.second = "Fn0";
	REQUIRE(calcuator.AddFunction("Fn1", expr2));
}

SCENARIO("Get value existed variable")
{
	CCalculator calcuator;
	string val1 = "2.45";
	calcuator.SetVarValue("X", val1);
	REQUIRE(calcuator.GetIdentifierValue("X") == 2.45);
}

SCENARIO("Get value non-existed variable")
{
	CCalculator calcuator;
	string val1 = "2.45";
	calcuator.SetVarValue("X", val1);
	REQUIRE(calcuator.GetIdentifierValue("Y") == INFINITY);
}

SCENARIO("Get value existed non-value variable")
{
	CCalculator calculator;
	calculator.AddNewVar("X");
	REQUIRE(isnan(calculator.GetIdentifierValue("X")));
}

SCENARIO("Get value fn = op1")
{
	CCalculator calcuator;
	string val1 = "2.45";
	calcuator.SetVarValue("var1", val1);
	CCalculator::expression expr;
	expr.first = ' ';
	expr.second.first = "var1";
	calcuator.AddFunction("Plus", expr);
	REQUIRE(floor(calcuator.GetIdentifierValue("Plus") * 100) / 100 == 2.45);
}

SCENARIO("Get value fn = fn1")
{
	CCalculator calcuator;
	string val1 = "2.45";
	string val2 = "5.34";
	calcuator.SetVarValue("var1", val1);
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	CCalculator::expression expr1;
	expr1.first = ' ';
	expr1.second.first = "Plus";
	calcuator.AddFunction("Fn", expr1);
	REQUIRE(floor(calcuator.GetIdentifierValue("Fn") * 100) / 100 == 7.79);
}

SCENARIO("Get value fn = op1 + op2")
{
	CCalculator calcuator;
	string val1 = "2.45";
	string val2 = "5.34";
	calcuator.SetVarValue("var1", val1);
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	REQUIRE(calcuator.GetIdentifierValue("Plus") == 7.79);
}

SCENARIO("Get value fn = op1(nan) + op2")
{
	CCalculator calcuator;
	string val2 = "5.34";
	calcuator.AddNewVar("var1");
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	REQUIRE(isnan(calcuator.GetIdentifierValue("Plus")));
}

SCENARIO("Get value fn = op1(non-exist) + op2")
{
	CCalculator calcuator;
	string val2 = "5.34";
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	REQUIRE(isinf(calcuator.GetIdentifierValue("Plus")));
}


SCENARIO("Get value fn = op1(non-exist) + op2(non-exist)")
{
	CCalculator calcuator;
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	REQUIRE(isinf(calcuator.GetIdentifierValue("Plus")));
}

SCENARIO("Get value fn = op1(nan) + op2(nan)")
{
	CCalculator calcuator;
	calcuator.AddNewVar("var1");
	calcuator.AddNewVar("var2");
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	REQUIRE(isnan(calcuator.GetIdentifierValue("Plus")));
}

SCENARIO("Get value fn = op1 / op2(0)")
{
	CCalculator calcuator;
	string val1 = "2.45";
	string val2 = "0";
	calcuator.SetVarValue("var1", val1);
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '/';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Fn", expr);
	REQUIRE(isnan(calcuator.GetIdentifierValue("Fn")));
}

SCENARIO("Get value fn = fn1(nan) + op2")
{
	CCalculator calcuator;
	string val2 = "5.34";
	calcuator.AddNewVar("var1");
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	CCalculator::expression expr1;
	expr1.first = '+';
	expr1.second.first = "Plus";
	expr1.second.second = "var2";
	calcuator.AddFunction("Fn", expr1);
	REQUIRE(isnan(calcuator.GetIdentifierValue("Fn")));
}

SCENARIO("Get value fn = fn1 + op2(nan)")
{
	CCalculator calcuator;
	string val2 = "5.34";
	calcuator.AddNewVar("var1");
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	CCalculator::expression expr1;
	expr1.first = '+';
	expr1.second.first = "Plus";
	expr1.second.second = "var1";
	calcuator.AddFunction("Fn", expr1);
	REQUIRE(isnan(calcuator.GetIdentifierValue("Fn")));
}

SCENARIO("Get value fn = fn1(non-exist) + op2")
{
	CCalculator calcuator;
	string val2 = "5.34";
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr1;
	expr1.first = '+';
	expr1.second.first = "Plus";
	expr1.second.second = "var2";
	calcuator.AddFunction("Fn", expr1);
	REQUIRE(isinf(calcuator.GetIdentifierValue("Fn")));
}

SCENARIO("Get value fn = fn1 + op2(non-exist)")
{
	CCalculator calcuator;
	string val1 = "3.9";
	string val2 = "5.34";
	calcuator.SetVarValue("var1", val1);
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	CCalculator::expression expr1;
	expr1.first = '+';
	expr1.second.first = "Plus";
	expr1.second.second = "var4";
	calcuator.AddFunction("Fn", expr1);
	REQUIRE(isinf(calcuator.GetIdentifierValue("Fn")));
}

SCENARIO("Get value fn = fn1 * fn2")
{
	CCalculator calcuator;
	string val1 = "2.45";
	string val2 = "5.34";
	calcuator.SetVarValue("var1", val1);
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	CCalculator::expression expr1;
	expr1.first = '-';
	expr1.second.first = "var1";
	expr1.second.second = "var2";
	calcuator.AddFunction("Fn", expr1);
	CCalculator::expression expr2;
	expr2.first = '*';
	expr2.second.first = "Plus";
	expr2.second.second = "Fn";
	calcuator.AddFunction("mult", expr2);
	REQUIRE(floor(calcuator.GetIdentifierValue("mult") * 100) / 100 == -22.52);
}

SCENARIO("Get value fn = fn1(nan) * fn2")
{
	CCalculator calcuator;
	string val2 = "5.34";
	calcuator.AddNewVar("var1");
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	CCalculator::expression expr1;
	expr1.first = '-';
	expr1.second.first = "var1";
	expr1.second.second = "var2";
	calcuator.AddFunction("Fn", expr1);
	CCalculator::expression expr2;
	expr2.first = '*';
	expr2.second.first = "Plus";
	expr2.second.second = "Fn";
	calcuator.AddFunction("mult", expr2);
	REQUIRE(isnan(calcuator.GetIdentifierValue("mult")));
}

SCENARIO("Get value fn = fn1(nan) * fn2(nan)")
{
	CCalculator calcuator;
	string val2 = "5.34";
	calcuator.AddNewVar("var1");
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	CCalculator::expression expr1;
	expr1.first = '-';
	expr1.second.first = "var1";
	expr1.second.second = "var2";
	calcuator.AddFunction("Fn", expr1);
	CCalculator::expression expr2;
	expr2.first = '*';
	expr2.second.first = "Plus";
	expr2.second.second = "Fn";
	calcuator.AddFunction("mult", expr2);
	REQUIRE(isnan(calcuator.GetIdentifierValue("mult")));
}

SCENARIO("Get value fn = fn1(non-exist) * fn2")
{
	CCalculator calcuator;
	string val1 = "2.45";
	string val2 = "5.34";
	CCalculator::expression expr1;
	expr1.first = '-';
	expr1.second.first = "var1";
	expr1.second.second = "var2";
	calcuator.AddFunction("Fn", expr1);
	CCalculator::expression expr2;
	expr2.first = '*';
	expr2.second.first = "Plus";
	expr2.second.second = "Fn";
	calcuator.AddFunction("mult", expr2);
	REQUIRE(isinf(calcuator.GetIdentifierValue("mult")));
}

SCENARIO("Get value fn = fn1(non-exist) * fn2(non-exist)")
{
	CCalculator calcuator;
	CCalculator::expression expr2;
	expr2.first = '*';
	expr2.second.first = "Plus";
	expr2.second.second = "Fn";
	calcuator.AddFunction("mult", expr2);
	REQUIRE(isinf(calcuator.GetIdentifierValue("mult")));
}

SCENARIO("Get all fns values")
{
	CCalculator calcuator;
	string val1 = "2.45";
	string val2 = "5.34";
	calcuator.SetVarValue("var1", val1);
	calcuator.SetVarValue("var2", val2);
	CCalculator::expression expr;
	expr.first = '+';
	expr.second.first = "var1";
	expr.second.second = "var2";
	calcuator.AddFunction("Plus", expr);
	CCalculator::expression expr1;
	expr1.first = '-';
	expr1.second.first = "var1";
	expr1.second.second = "var2";
	calcuator.AddFunction("Fn", expr1);
	CCalculator::expression expr2;
	expr2.first = '*';
	expr2.second.first = "Plus";
	expr2.second.second = "Fn";
	calcuator.AddFunction("mult", expr2);
	map<string, double> results = calcuator.GetAllFnValue();
	REQUIRE(results.at("Plus") == 7.79);
	REQUIRE(floor(results.at("Fn") * 100) / 100 == -2.89);
	REQUIRE(floor(results.at("mult") * 100) / 100 == -22.52);
}

SCENARIO("Get all vars")
{
	CCalculator calcuator;
	string val1 = "2.45";
	string val2 = "5.34";
	calcuator.SetVarValue("var1", val1);
	calcuator.SetVarValue("var2", val2);
	map<string, double> results = calcuator.GetAllVars();
	REQUIRE(results.at("var1") == 2.45);
	REQUIRE(results.at("var2") == 5.34);
}