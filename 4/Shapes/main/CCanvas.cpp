#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void CCanvas::DrawLine(const CPoint& first, const CPoint& second, uint32_t outlineColor)
{
	sf::Vertex line[2] =
	{
		sf::Vector2f(static_cast<float>(first.x), static_cast<float>(first.y)),
		sf::Vector2f(static_cast<float>(second.x), static_cast<float>(second.y))
	};
	line[0].color = GetColor(outlineColor);
	line[1].color = GetColor(outlineColor);
	m_window.draw(line, 2, sf::Lines);
}

void CCanvas::DrawPolygon(const std::vector<CPoint> points, uint32_t outlineColor, uint32_t fillColor)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	for (unsigned i = 0; i < points.size(); i++)
	{
		polygon.setPoint(i, sf::Vector2f(static_cast<float>(points[i].x), static_cast<float>(points[i].y)));
	}
	polygon.setOutlineColor(GetColor(outlineColor));
	polygon.setOutlineThickness(5);
	polygon.setFillColor(GetColor(fillColor));
	m_window.draw(polygon);
}

void CCanvas::DrawCircle(const CPoint& center, double radius, uint32_t outlineColor, uint32_t fillColor)
{
	sf::CircleShape circle;
	circle.setPosition(static_cast<float>(center.x), static_cast<float>(center.y));
	circle.setRadius(static_cast<float>(radius));
	circle.setOutlineColor(GetColor(outlineColor));
	circle.setOutlineThickness(5);
	circle.setFillColor(GetColor(fillColor));
	m_window.draw(circle);
}

sf::Color CCanvas::GetColor(uint32_t color)
{
	uint32_t blue = color % 256;
	uint32_t green = (color / 256) % 256;
	uint32_t red = ((color / 256) / 256) % 256;
	return sf::Color(red, green, blue);
}
