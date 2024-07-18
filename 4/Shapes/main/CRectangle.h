#pragma once
#include "CSolidShape.h"
#include "CPoint.h"
class CRectangle : public CSolidShape
{
public:
	CRectangle(CPoint leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	double GetWidth() const;
	double GetHeight() const;
	CPoint GetLeftTop() const;
	void Draw(ICanvas& canvas) const override;
private:
	CPoint m_leftTop;
	double m_width, m_height;
};
