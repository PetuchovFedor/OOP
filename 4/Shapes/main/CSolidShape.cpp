#include "CSolidShape.h"

CSolidShape::CSolidShape(uint32_t outlineColor, uint32_t fillColor)
	: m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
{
}

uint32_t CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

uint32_t CSolidShape::GetOutlineColor() const
{
	return m_outlineColor;
}
