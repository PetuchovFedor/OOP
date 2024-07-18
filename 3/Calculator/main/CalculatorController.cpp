#include "CalcullatorController.h"
#include <sstream>
#include <string>
using namespace std;

namespace
{
    vector<string> Split(const string& str)
    {
        string substr;
        vector<string> result;
        for (char ch : str)
        {
            if (ch == ' ')
                continue;
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || isdigit(ch) || ch == '_')
            {
                substr = substr + ch;
            }
            else
            {
                string tmp;
                tmp[0] = ch;
                result.push_back(tmp);
                result.push_back(substr);
                substr.clear();               
            }
        }
        result.push_back(substr);
        return result;
    }
}

CalculatorController::CalculatorController(CCalculator& calculator, std::istream& input, std::ostream& output)
    : m_calculator(calculator)
    , m_input(input)
    , m_output(output)
    , m_actionMap({
                { "var", [this](std::istream& args) {
                    return CreateVar(args); } },
                { "let", [this](std::istream& args) {
                    return SetVarValue(args); } },
                { "fn", [this](std::istream& args) {
                    return CreateFunction(args); } },
                { "print", [this](std::istream& args) {
                    return PrintIdentifier(args); } },
                { "printvars", [this](std::istream& args) {
                    return PrintVars(args); } },
                { "printfns", [this](std::istream& args) {
                    return PrintFunctions(args); } }
        })
{
}

bool CalculatorController::HandleComand()
{
    string commandLine;
    getline(m_input, commandLine);
    istringstream strm(commandLine);

    string action;
    getline(strm, action, ' ');

    auto it = m_actionMap.find(action);
    if (it != m_actionMap.end())
    {
        it->second(strm);
        return true;
    }

    return false;
}

bool CalculatorController::CreateVar(std::istream& args)
{
    string var;
    args >> var;
    if (m_calculator.AddNewVar(var))
        return true;
    m_output << "error with variable declaration" << endl;
    return false;
}

bool CalculatorController::SetVarValue(std::istream& args)
{
    string var, val;
    getline(args, var, '=');
    args >> val;
    if (!m_calculator.SetVarValue(var, val))
    {
        m_output << "Assigment error" << endl;
        return false;
    }
    return true;
}

bool CalculatorController::CreateFunction(std::istream& args)
{
    string fn, ex;
    CCalculator::expression expr;
    getline(args, fn, '=');
    getline(args, ex);
    if (ex.empty())
    {
        m_output << "expression empty" << endl;
        return false;
    }
    vector<string> argsExpr = Split(ex);
    if (argsExpr.size() == 1)
    {
        expr.first = ' ';
        expr.second.first = argsExpr[0];
        if (m_calculator.AddFunction(fn, expr))
            return true;
    }
    if (argsExpr.size() == 3)
    {
        expr.first = (argsExpr[0][0]);
        argsExpr.erase(argsExpr.begin());
        expr.second.first = argsExpr[0];
        expr.second.second = argsExpr[1];
        if (m_calculator.AddFunction(fn, expr))
            return true;
    }
    m_output << "error with function declaration" << endl;
    return false;
}

bool CalculatorController::PrintIdentifier(std::istream& args)
{
    string arg;
    getline(args, arg);
    double val = m_calculator.GetIdentifierValue(arg);
    if (isinf(val))
    {
        m_output << "ERROR: identidier not declared" << endl;
        return false;
    }
    else
    {
        m_output << floor(val * 100) / 100 << endl;
    }
    return true;
}

bool CalculatorController::PrintVars(std::istream& /*args*/)
{
    map<string, double> vars = m_calculator.GetAllVars();
    for (auto& pair : vars)
    {
        m_output << pair.first << ": " << floor(pair.second * 100) / 100 << endl;
    }
    return true;
}

bool CalculatorController::PrintFunctions(std::istream& /*args*/)
{
    map<string, double> vars = m_calculator.GetAllFnValue();
    for (auto& pair : vars)
    {
        m_output << pair.first << ": " << floor(pair.second * 100) / 100 << endl;
    }
    return true;
}
