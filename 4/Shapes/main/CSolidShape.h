#pragma once
#include "ISolidShape.h"

class CSolidShape : public ISolidShape
{
public:
	CSolidShape(uint32_t outlineColor, uint32_t fillColor);
	uint32_t GetFillColor() const override;
	uint32_t GetOutlineColor() const override;

private:
	uint32_t m_fillColor, m_outlineColor;
};