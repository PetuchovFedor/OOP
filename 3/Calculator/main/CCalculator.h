#pragma once
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

class CCalculator
{
public:
	using expression = std::pair<char, std::pair<std::string, std::string>>;
	bool AddNewVar(const std::string& varName);
	bool SetVarValue(const std::string& varName, std::string& value);
	bool AddFunction(const std::string& fnName, const expression& expr);
	double GetIdentifierValue(const std::string& name);
	std::map<std::string, double> GetAllVars();
	std::map<std::string, double> GetAllFnValue();
private:
	double CalculateFnValue(const std::string& name);
	bool IsValidName(const std::string& name) const;
	bool IsExistVar(const std::string& name) const;
	bool IsExistFN(const std::string& name) const;
	bool IsValidExpression(const expression& expr) const;
private:
	std::vector<char> m_operations = { '+', '-', '*', '/' };
	std::map<std::string, double> m_vars;
	std::map<std::string, expression> m_functions;
};