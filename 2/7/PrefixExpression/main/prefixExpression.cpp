#include "prefixExpression.h"
#include <algorithm>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;


//int Pop(vector<int>& stack)
//{
//    int temp = stack.back();
//    stack.pop_back();
//    return temp;
//}
//
//void PushResult(vector<int>& stack, char ch, int op1, int op2)
//{
//    if (ch == '+')
//        stack.push_back(op1 + op2);
//    else if (ch == '*')
//        stack.push_back(op1 * op2);
//}
//
//void PushResult(vector<int>& stack, char ch, int op1, int op2, int op3)
//{
//    if (ch == '+')
//        stack.push_back(op1 + op2 + op3);
//    else if (ch == '*')
//        stack.push_back(op1 * op2 * op3);
//}

void OperationProcessingWithTwoOperand(stack<int>& stack, char operation)
{
    int op1 = stack.top();
    stack.pop();
    int op2 = stack.top();
    stack.pop();
    if (operation == '+')
    {
       
        stack.push(op1 + op2);
    }
    else
    {
        /*int op1 = stack.top();
        stack.pop();
        int op2 = stack.top();
        stack.pop();*/
        stack.push(op1 * op2);
    }

}

void OperationProcessingWithThreeOperand(stack<int>& stack, char operation)
{
    int op1 = stack.top();
    stack.pop();
    int op2 = stack.top();
    stack.pop();
    int op3 = stack.top();
    stack.pop();
    if (operation == '+')
    {
        
        stack.push(op1 + op2 + op3);
    }
    else
    {
       /* int op1 = stack.top();
        stack.pop();
        int op2 = stack.top();
        stack.pop();
        int op3 = stack.top();
        stack.pop();*/
        stack.push(op1 * op2 * op3);
    }
}

void OperationProcessing(stack<int>& stack, char operation, int countOperands)
{
    if (countOperands == 2)
        OperationProcessingWithTwoOperand(stack, operation);
    else if (countOperands == 1 || countOperands == 3)
        OperationProcessingWithThreeOperand(stack, operation);
    else
        while (stack.size() != 1)
            OperationProcessingWithTwoOperand(stack, operation);
}

int CalculatePrefixExpression(std::string& expr)
{
    stack<int> stack;
    reverse(expr.begin(), expr.end());
    istringstream ss(expr);
    char ch = 0;
    string str;
    //Норм названоеи для count
    int countOperands = 0, num = 0;
    //разбить while на функции 
    while (ss >> ch)
    {
        if (ch == '(' || ch == ')')
            continue;
        if (isdigit(ch))
        {
            ss.unget();
            ss >> str;
            if (str.size() > 1)
                reverse(str.begin(), str.end());
            stack.push(stoi(str));
            countOperands++;
        }
        //+ и * вынести в константы
        if (ch == '+' || ch == '*')
        {
            if (stack.size() == 1)
                continue;
            OperationProcessing(stack, ch, countOperands);
            countOperands = 0;
        }
    }
    return stack.top();
}
