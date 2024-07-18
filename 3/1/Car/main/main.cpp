#include "CarRemoteControl.h"

int main()
{
	Car car;
	CarRemoteControl CarRemoteControl(car, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!CarRemoteControl.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
}