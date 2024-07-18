#include <iostream>
#include "ShapesController.h"
int main()
{
	ShapesController ShapeRemoteControl(std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		if (!ShapeRemoteControl.ShapeProcessing())
		{
			if (std::cin.eof())
			{
				ShapeRemoteControl.WriteInfoAboutNecesariosShapes();
				ShapeRemoteControl.DrawShapes();
				break;
			}		
			std::cout << "Unknown command!" << std::endl;
		}
	}
}