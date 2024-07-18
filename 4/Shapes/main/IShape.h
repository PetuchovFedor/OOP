#pragma once
#include <string>
#include "ICanvasDrawable.h"

class IShape : public ICanvasDrawable
{
public:
	//Добавитть виртуальный деструктор
	virtual ~IShape() = default;
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;

};