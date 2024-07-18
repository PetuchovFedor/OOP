#include "CTriangle.h"
#include "CLineSegment.h"
#include <sstream>
using namespace std;

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, CSolidShape(outlineColor, fillColor)
{
}

double CTriangle::GetArea() const
{
	return (m_vertex1.x * (m_vertex2.y - m_vertex3.y) + m_vertex2.x * (m_vertex3.y - m_vertex1.y) + m_vertex3.x * (m_vertex1.y - m_vertex2.y)) / 2;
}

double CTriangle::GetPerimeter() const
{
	double side1 = sqrt(pow(m_vertex2.x - m_vertex1.x, 2) + pow(m_vertex2.y - m_vertex1.y, 2));
	double side2 = sqrt(pow(m_vertex3.x - m_vertex2.x, 2) + pow(m_vertex3.y - m_vertex2.y, 2));
	double side3 = sqrt(pow(m_vertex3.x - m_vertex2.x, 2) + pow(m_vertex3.y - m_vertex2.y, 2));
	return side1 + side2 + side3;
}

std::string CTriangle::ToString() const
{
	stringstream output;
	output << "triangle ";
	output << "vertex1: (" << m_vertex1.x << "; " << m_vertex1.y << "), ";
	output << "vertex2: (" << m_vertex2.x << "; " << m_vertex2.y << "), ";
	output << "vertex3: (" << m_vertex3.x << "; " << m_vertex3.y << "), ";
	output << "outline color: #" << hex << GetOutlineColor();
	output << ", fill color: #" << hex << GetFillColor() << ", ";
	output << "area: " << GetArea() << ", ";
	output << "perimeter: " << GetPerimeter();
	return output.str();
}

void CTriangle::Draw(ICanvas& canvas) const
{
	vector<CPoint> points;
	points.push_back(m_vertex1);
	points.push_back(m_vertex2);
	points.push_back(m_vertex3);
	canvas.DrawPolygon(points, GetOutlineColor(), GetFillColor());
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}
