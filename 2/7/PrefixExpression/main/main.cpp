#include <iostream>
#include "../main/prefixExpression.h"
using namespace std;

int main()
{
    string expr;
    getline(cin, expr);
    try
    { 
        cout << CalculatePrefixExpression(expr) << endl;
    }
    catch (exception)
    {
        cout << "ERROR" << endl;
    }

}
