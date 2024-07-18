#pragma once
#include "CCalculator.h"
#include <functional>

class CalculatorController
{
public:
	CalculatorController(CCalculator& calculator, std::istream& input, std::ostream& output);
	bool HandleComand();
private:
	bool CreateVar(std::istream& args);
	bool SetVarValue(std::istream& args);
	bool CreateFunction(std::istream& args);
	bool PrintIdentifier(std::istream& args);
	bool PrintVars(std::istream& args);
	bool PrintFunctions(std::istream& args);
private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	CCalculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};