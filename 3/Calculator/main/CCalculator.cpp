#include "CCalculator.h"
#include <algorithm>
using namespace std;

namespace
{
    double StrToDouble(string& str)
    {
        try
        {
            double val = stod(str);
            return val;
        }
        catch (exception e)
        {
            cout << e.what() << endl;
        }     
    }
    bool IsDouble(const string& str)
    {
        return all_of(str.begin(), str.end(), [&](char ch) {
            return isdigit(ch) || ch == '.' || ch == '-';
            });
    }
}
bool CCalculator::AddNewVar(const std::string& varName)
{
    if (!IsValidName(varName) || IsExistVar(varName))
        return false;
    m_vars.insert({ varName, NAN });
    return true;
}

bool CCalculator::SetVarValue(const std::string& varName, std::string& value)
{
    double val = IsDouble(value) ? StrToDouble(value) : (IsExistFN(value) || IsExistVar(value)) ? GetIdentifierValue(value) : NAN;
    if (isnan(val))
        return false;
    if (IsExistVar(varName))
        m_vars.at(varName) = val;
    else if (IsValidName(varName))
        m_vars.insert({ varName, val });
    else
        return false;
    return true;
}

bool CCalculator::AddFunction(const std::string& fnName, const expression& expr)
{
    if (!IsValidName(fnName) || IsExistFN(fnName))
        return false;
    if (!IsValidExpression(expr))
        return false;
    m_functions.insert({ fnName, expr });
    return true;
}

double CCalculator::GetIdentifierValue(const std::string& name)
{
    if (m_vars.find(name) != m_vars.end())
        return m_vars.at(name);
    else if (m_functions.find(name) != m_functions.end())
        return CalculateFnValue(name);
    else
        return INFINITY;
}

std::map<std::string, double> CCalculator::GetAllVars()
{
    std::map<std::string, double> allVars = m_vars;
    return allVars;
}

std::map<std::string, double> CCalculator::GetAllFnValue() 
{
    std::map<std::string, double> allFns;
    for (auto it = m_functions.begin(); it != m_functions.end(); it++)
        allFns.insert({ it->first, CalculateFnValue(it->first)});
    return allFns;
}

double CCalculator::CalculateFnValue(const std::string& name)
{
    expression expr = m_functions.find(name)->second;
    if (expr.first == ' ')
        return GetIdentifierValue(expr.second.first);
    double op1 = GetIdentifierValue(expr.second.first);
    double op2 = GetIdentifierValue(expr.second.second);
    if (isinf(op1) || isinf(op2))
        return INFINITY;
    if (isnan(op1) || isnan(op2))
        return NAN;
    switch (expr.first)
    {
    case '+':
        return op1 + op2;
    case '-':
        return op1 - op2;
    case '*':
        return op1 * op2;
    case '/':
        return op2 != 0 ? op1 / op2 : NAN;
    default:
        break;
    }
}

bool CCalculator::IsValidName(const std::string& name) const
{
    if (name.empty())
        return false;
    if (isdigit(name[0]))
        return false;
    return all_of(name.begin(), name.end(), [](char ch) 
        {
            return isdigit(ch) || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
        });
}

bool CCalculator::IsExistVar(const std::string& name) const
{ 
    if (m_vars.find(name) == m_vars.end())
        return false;
    else
        return true;
}

bool CCalculator::IsExistFN(const std::string& name) const
{
    if (m_functions.find(name) == m_functions.end())
        return false;
    else
        return true;
}

bool CCalculator::IsValidExpression(const expression& expr) const
{
    if (expr.first == ' ' && expr.second.second == "")
    { 
        if (IsExistVar(expr.second.first) || IsExistFN(expr.second.first))
        { 
            return true;
        }
    }
    else if (find(m_operations.begin(), m_operations.end(), expr.first) != m_operations.end())
    { 
        if ((IsExistVar(expr.second.first) || IsExistFN(expr.second.first)) && (IsExistVar(expr.second.second) || IsExistFN(expr.second.second)))
        { 
            return true;
        }
    }
    return false;
}
