#include <iostream>
#include <vector>;
#include "CStringStack.h"
using namespace std;

int main()
{
	//std::vector<std::string> ve = { "qe", "qe", "safsa", "casc", "asc"};
	CStringStack stack;
	stack.Push("qwe");
	stack.GetSize();
	stack.Push("adc");
	stack.Push("fds");
	CStringStack qwe(stack);
	CStringStack qwe1(move(qwe));
	qwe1.Pop();
	qwe = stack;
	qwe = move(stack);
	string tmp = stack.GetTop();
	stack.Push("asd");
	stack.Pop();
}