#include "CLineSegment.h"

#include "CLineSegment.h"
#include <sstream>
using namespace std;

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor)
    : m_startPoint(startPoint)
    , m_endPoint(endPoint)
    , m_outlineColor(outlineColor)
{
}


double CLineSegment::GetPerimeter() const
{
    return sqrt(pow(m_endPoint.x - m_startPoint.x, 2) + pow(m_endPoint.y - m_startPoint.y, 2));
}

double CLineSegment::GetArea() const
{
    return 0.0;
}

std::string CLineSegment::ToString() const
{
    stringstream output;
    output << "line ";
    output << "start point: (" << m_startPoint.x << "; " << m_startPoint.y << "), ";
    output << "end point: (" << m_endPoint.x << "; " << m_endPoint.y << "), ";
    output << "outline color: #" << hex << GetOutlineColor() << ", ";
    output << "perimeter: " << GetPerimeter();
    return output.str();
}

void CLineSegment::Draw(ICanvas& canvas) const
{
    canvas.DrawLine(m_startPoint, m_endPoint, GetOutlineColor());
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return m_outlineColor;;
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}

