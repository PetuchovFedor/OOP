#pragma once
#include "IShape.h"
#include <vector>
#include <map>
#include <functional>
#include <memory>

class ShapesController
{
public:
	ShapesController(std::istream& input, std::ostream& output);
	bool ShapeProcessing();
	void DrawShapes() const;
	void WriteInfoAboutNecesariosShapes() const;

private:
	bool SetLine(std::istream& args);
	bool SetTriangle(std::istream& args);
	bool SetRectangle(std::istream& args);
	bool SetCircle(std::istream& args);
	int FindIndexShapeWithMaxArea() const;
	int FindIndexShapeWithMinPeriment() const;
private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;
	
	std::vector<std::unique_ptr<IShape>> m_shapes;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};