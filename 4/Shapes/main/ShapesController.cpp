#include "CPoint.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CCircle.h"
#include "CCanvas.h"
#include <algorithm>
#include <sstream>
#include <vector>
#include "ShapesController.h"
using namespace std;

namespace 
{
    bool CheckForDigit(const string& str)
    {
        return all_of(str.begin(), str.end(), [](char ch) { return isdigit(ch) || ch == '.'; });
    }
    bool CheckColor(const string& str)
    {
        if (str.size() > 6)
            return false;
        return all_of(str.begin(), str.end(), [](char ch) { return isdigit(ch) || (ch >= 'a' || ch <= 'f'); });
    }

    bool CheckShapeInput(istream& args, int numDimension, int numColor)
    {
        string str;
        int i = 0;
        while (args >> str && i < numDimension)
        {
            if (!CheckForDigit(str))
                return false;
            i++;
        }
        i = 0;
        while (args >> str && i < numColor)
        {
            if (!CheckColor(str))
                return false;
            i++;
        }
        if (!args.eof())
            return false;
        return true;
    }
    bool CheckShape(const std::string& args)
    {
        istringstream in(args);
        string shape;
        in >> shape;
        if (shape == "line")
        {
            if (!CheckShapeInput(in, 4, 1))
                return false;
        }
        else if (shape == "triangle")
        {
            if (!CheckShapeInput(in, 6, 2))
                return false;
        }
        else if (shape == "rectangle")
        {
            if (!CheckShapeInput(in, 4, 2))
                return false;
        }
        else if (shape == "circle")
        {
            if (!CheckShapeInput(in, 3, 2))
                return false;
        }
        else
        {
            return false;
        }
        return true;
    }

    vector<string> SplitStream(istream& stream)
    {
        string str;
        vector<string> args;
        while (stream >> str)
            args.push_back(str);
        return args;
    }

}

ShapesController::ShapesController(std::istream& input, std::ostream& output)
    : m_input(input)
    , m_output(output)
    , m_actionMap({
                { "line", [this](std::istream& args) {
                    return SetLine(args); } },
                { "triangle", [this](std::istream& args) {
                    return SetTriangle(args); } },
                { "rectangle", [this](std::istream& args) {
                    return SetRectangle(args); } },
                { "circle", [this](std::istream& args) {
                    return SetCircle(args); } } 
        })
{
}

bool ShapesController::ShapeProcessing()
{
    string commandLine;
    getline(m_input, commandLine);
    
    if (!CheckShape(commandLine) && !m_input.eof())
    {
        m_output << "Error with description shape" << endl;
        return true;
    }
    istringstream strm(commandLine);
    string action;
    strm >> action;
    auto it = m_actionMap.find(action);
    if (it != m_actionMap.end())
    {
        return it->second(strm);
    }

    return false;
}

void ShapesController::DrawShapes() const
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    CCanvas canvas(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(135, 206, 235));
        for (unsigned i = 0; i < m_shapes.size(); i++)
        {
            m_shapes[i]->Draw(canvas);
        }
        window.display();
    }
}

int ShapesController::FindIndexShapeWithMaxArea() const
{
    auto it = max_element(m_shapes.begin(), m_shapes.end(),
        [](const unique_ptr<IShape>& first, const unique_ptr<IShape>& second)
        { return first->GetArea() < second->GetArea(); });
    return distance(m_shapes.begin(), it);
}

int ShapesController::FindIndexShapeWithMinPeriment() const
{
    auto it = min_element(m_shapes.begin(), m_shapes.end(),
        [](const unique_ptr<IShape>& first, const unique_ptr<IShape>& second)
        { return first->GetPerimeter() < second->GetPerimeter(); });
    return distance(m_shapes.begin(), it);
}

void ShapesController::WriteInfoAboutNecesariosShapes() const
{
    if (m_shapes.empty())
    {
        m_output << "Shapes are not entered" << endl;
        return;
    }
    int firstShapeIdx = FindIndexShapeWithMaxArea();
    int secondShapeIdx = FindIndexShapeWithMinPeriment();
    m_output << "Shape with max area " << m_shapes[firstShapeIdx]->ToString() << endl;
    m_output << "Shape with min perimeter " << m_shapes[secondShapeIdx]->ToString() << endl;
}

bool ShapesController::SetLine(std::istream& args)
{
    vector<string> properties = SplitStream(args);
    CPoint startPoint, endPoint;
    startPoint.x = stod(properties[0]);
    startPoint.y = stod(properties[1]);
    endPoint.x = stod(properties[2]);
    endPoint.y = stod(properties[3]);
    CLineSegment line(startPoint, endPoint, static_cast<uint32_t>(stoul(properties[4], nullptr, 16)));
    m_shapes.push_back(make_unique<CLineSegment>(line));
	return true;
}

bool ShapesController::SetTriangle(std::istream& args)
{
    //args.
    vector<string> properties = SplitStream(args);
    CPoint vertex1, vertex2, vertex3;
    vertex1.x = stod(properties[0]);
    vertex1.y = stod(properties[1]);
    vertex2.x = stod(properties[2]);
    vertex2.y = stod(properties[3]);
    vertex3.x = stod(properties[4]);
    vertex3.y = stod(properties[5]);
    CTriangle triangle(vertex1, vertex2, vertex3, static_cast<uint32_t>(stoul(properties[6], nullptr, 16)), static_cast<uint32_t>(stoul(properties[7], nullptr, 16)));
    m_shapes.push_back(make_unique<CTriangle>(triangle));
    return true;
}

bool ShapesController::SetRectangle(std::istream& args)
{
    vector<string> properties = SplitStream(args);
    CPoint leftTop;
    leftTop.x = stod(properties[0]);
    leftTop.y = stod(properties[1]);
    double width = stod(properties[2]);
    double height = stod(properties[3]);
    CRectangle rectangle(leftTop, width, height, static_cast<uint32_t>(stoul(properties[4], nullptr, 16)), static_cast<uint32_t>(stoul(properties[5], nullptr, 16)));
    m_shapes.push_back(make_unique<CRectangle>(rectangle));
    return true;
}

bool ShapesController::SetCircle(std::istream& args)
{
    vector<string> properties = SplitStream(args);
    CPoint center;
    center.x = stod(properties[0]);
    center.y = stod(properties[1]);
    double radius = stod(properties[2]);
    CCircle circle(center, radius, static_cast<uint32_t>(stoul(properties[3], nullptr, 16)), static_cast<uint32_t>(stoul(properties[4], nullptr, 16)));
    m_shapes.push_back(make_unique<CCircle>(circle));
	return true;
}