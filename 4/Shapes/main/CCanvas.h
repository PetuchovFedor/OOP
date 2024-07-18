#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class CCanvas : public ICanvas
{
public:
	//зависимость от рендер таргет
	CCanvas(sf::RenderWindow& window);
	void DrawLine(const CPoint& first, const CPoint& second, uint32_t outlineColor) override;
	void DrawPolygon(const std::vector<CPoint> points, uint32_t outlineColor, uint32_t fillColor) override;
	void DrawCircle(const CPoint& center, double radius, uint32_t outlineColor, uint32_t fillColor) override;
private:
	sf::Color GetColor(uint32_t color);
	sf::RenderWindow& m_window;
};