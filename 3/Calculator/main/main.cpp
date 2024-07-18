#include <iostream>
#include "CalcullatorController.h"

int main()
{
	CCalculator cal;
	CalculatorController calc(cal, std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		if (!calc.HandleComand() && !std::cin.eof())
			std::cout << "Unknown command" << std::endl;
	}
}

