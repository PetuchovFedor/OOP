#define CATCH_CONFIG_MAIN
//#include "../../../catch2/catch.hpp"
#include "catch.hpp"
#include "fakeit.hpp"
#include "../main/ICanvas.h"
#include "../main/CCircle.h"
#include "../main/CRectangle.h"
#include "../main/CTriangle.h"
#include <iostream>
#include "../main/CLineSegment.h"
using namespace fakeit;
using namespace std;

TEST_CASE("Checking rectnagle methods")
{
	GIVEN("Rectangle")
	{
		CPoint point;
		point.x = 10.3; point.y = 20.15;
		CRectangle rect(point, 30.7, 40.4, 16711680, 65280);
		WHEN("GetArea()")
		{
			double area = rect.GetArea();
			THEN("Area calculate correctly")
			{
				REQUIRE(area == 1240.28);
			}
		}
		WHEN("GetPerimeter()")
		{
			double perim = rect.GetPerimeter();
			THEN("Perimeter calculate correctly")
			{
				REQUIRE(perim == 142.2);
			}
		}
		WHEN("GetLeftTop()")
		{
			CPoint lefTop = rect.GetLeftTop();
			THEN("LefTop return correctly")
			{
				REQUIRE(lefTop.x == 10.3);  
				REQUIRE(lefTop.y == 20.15);
			}
		}
		WHEN("GetHeight()")
		{
			double height = rect.GetHeight();
			THEN("Height return correctly correctly")
			{
				REQUIRE(height == 40.4);
			}
		}
		WHEN("GetWidth()")
		{
			double width = rect.GetWidth();
			THEN("Height return correctly correctly")
			{
				REQUIRE(width == 30.7);
			}
		}
		WHEN("GetFillColor()")
		{
			uint32_t fillColor = rect.GetFillColor();
			THEN("GetFillColor return correctly correctly")
			{
				REQUIRE(fillColor == 65280);
			}
		}
		WHEN("GetOutlineColor()")
		{
			uint32_t outlineColor = rect.GetOutlineColor();
			THEN("GetOutlineColor return correctly correctly")
			{
				REQUIRE(outlineColor == 16711680);
			}
		}
		WHEN("ToString()")
		{
			string str = rect.ToString();
			THEN("ToString return correctly correctly")
			{
				REQUIRE(str == "rectangle left top point: (10.3; 20.15), width: 30.7, outline color: #ff0000, fill color: #ff00, area: 1240.28, perimeter: 142.2");
			}
		}
		WHEN("Draw")
		{
			/*struct RectTest
			{
				RectTest(const vector<CPoint>& points, uint32_t outlineColor, uint32_t fillColor)
					: points(points)
					, outlineColor(outlineColor)
					, fillColor(fillColor)
				{}
				vector<CPoint> points;
				uint32_t outlineColor;
				uint32_t fillColor;
			};
			vector<CPoint> points;
			points.push_back(rect.GetLeftTop());
			CPoint point;
			point.x = rect.GetLeftTop().x + rect.GetWidth();
			point.y = rect.GetLeftTop().y;
			points.push_back(point);
			point.y = rect.GetLeftTop().y - rect.GetHeight();
			points.push_back(point);
			point.x = rect.GetLeftTop().x;
			point.y = rect.GetLeftTop().y - rect.GetHeight();
			points.push_back(point);
			RectTest test(points, rect.GetOutlineColor(), rect.GetFillColor());*/
			Mock<ICanvas> mock;
			When(Method(mock, DrawPolygon)).AlwaysReturn();
			ICanvas& canvas = mock.get();
			rect.Draw(canvas);
			Verify(Method(mock, DrawPolygon)).Once();
			//Verify(Method(mock, DrawPolygon).Using(test)).Once();
			//Fake(Method(mock, );
		}
	}
}

TEST_CASE("Checking triangle methods")
{
	GIVEN("Triangle")
	{
		CPoint point1, point2, point3;
		point1.x = 2.0; point1.y = 4.0;
		point2.x = 0.0; point2.y = 2.6;
		point3.x = 2.9; point3.y = 1.0;
		CTriangle trian(point1, point2, point3, 16711680, 65280);
		WHEN("GetArea()")
		{
			double area = trian.GetArea();
			THEN("Area calculate correctly")
			{
				REQUIRE(area == 3.63);
			}
		}
		WHEN("GetPerimeter()")
		{
			double perim = trian.GetPerimeter();
			THEN("Perimeter calculate correctly")
			{
				REQUIRE(floor(perim * 1000) / 1000 == 9.065);
			}
		}
		WHEN("GetVertex1()")
		{
			CPoint v1 = trian.GetVertex1();
			THEN("LefTop return correctly")
			{
				REQUIRE(v1.x == 2.0);
				REQUIRE(v1.y == 4.0);
			}
		}
		WHEN("GetVertex2()")
		{
			CPoint v2 = trian.GetVertex2();
			THEN("LefTop return correctly")
			{
				REQUIRE(v2.x == 0.0);
				REQUIRE(v2.y == 2.6);
			}
		}
		WHEN("GetVertex3()")
		{
			CPoint v3 = trian.GetVertex3();
			THEN("LefTop return correctly")
			{
				REQUIRE(v3.x == 2.9);
				REQUIRE(v3.y == 1.0);
			}
		}
		WHEN("GetFillColor()")
		{
			uint32_t fillColor = trian.GetFillColor();
			THEN("GetFillColor return correctly correctly")
			{
				REQUIRE(fillColor == 65280);
			}
		}
		WHEN("GetOutlineColor()")
		{
			uint32_t outlineColor = trian.GetOutlineColor();
			THEN("GetOutlineColor return correctly correctly")
			{
				REQUIRE(outlineColor == 16711680);
			}
		}
		WHEN("ToString()")
		{
			string str = trian.ToString();
			THEN("ToString return correctly correctly")
			{
				REQUIRE(str == "triangle vertex1: (2; 4), vertex2: (0; 2.6), vertex3: (2.9; 1), outline color: #ff0000, fill color: #ff00, area: 3.63, perimeter: 9.06551");
			}
		}
		WHEN("Draw")
		{
			Mock<ICanvas> mock;
			When(Method(mock, DrawPolygon)).AlwaysReturn();
			ICanvas& canvas = mock.get();
			trian.Draw(canvas);
			Verify(Method(mock, DrawPolygon)).Once();
		}
	}
}

TEST_CASE("Checking circle methods")
{
	GIVEN("Circle")
	{
		CPoint point1;
		point1.x = 2.0; point1.y = 4.0;
		CCircle circ(point1, 10.5, 16711680, 65280);
		WHEN("GetArea()")
		{
			double area = circ.GetArea();
			THEN("Area calculate correctly")
			{
				REQUIRE(floor(area * 1000) / 1000 == 346.36);
			}
		}
		WHEN("GetPerimeter()")
		{
			double perim = circ.GetPerimeter();
			THEN("Perimeter calculate correctly")
			{
				REQUIRE(floor(perim * 1000) / 1000 == 65.973);
			}
		}
		WHEN("GetCenter()")
		{
			CPoint v1 = circ.GetCenter();
			THEN("LefTop return correctly")
			{
				REQUIRE(v1.x == 2.0);
				REQUIRE(v1.y == 4.0);
			}
		}
		WHEN("GetFillColor()")
		{
			uint32_t fillColor = circ.GetFillColor();
			THEN("GetFillColor return correctly correctly")
			{
				REQUIRE(fillColor == 65280);
			}
		}
		WHEN("GetOutlineColor()")
		{
			uint32_t outlineColor = circ.GetOutlineColor();
			THEN("GetOutlineColor return correctly correctly")
			{
				REQUIRE(outlineColor == 16711680);
			}
		}
		WHEN("ToString()")
		{
			string str = circ.ToString();
			THEN("ToString return correctly correctly")
			{

				REQUIRE(str == "circle center: (2; 4), radius: 10.5, outline color: #ff0000, fill color: #ff00, area: 346.361, perimeter: 65.9734");
			}
		}
		WHEN("Draw")
		{
			Mock<ICanvas> mock;
			When(Method(mock, DrawCircle)).AlwaysReturn();
			ICanvas& canvas = mock.get();
			circ.Draw(canvas);
			Verify(Method(mock, DrawCircle)).Once();
		}
	}
}

TEST_CASE("Checking line segment methods")
{
	GIVEN("line segment")
	{
		CPoint point1, point2;
		point1.x = 2.0; point1.y = 4.0;
		point2.x = 0.0; point2.y = 2.6;
		CLineSegment line(point1, point2, 16711680);
		WHEN("GetArea()")
		{
			double area = line.GetArea();
			THEN("Area calculate correctly")
			{
				REQUIRE(area == 0.0);
			}
		}
		WHEN("GetPerimeter()")
		{
			double perim = line.GetPerimeter();
			THEN("Perimeter calculate correctly")
			{
				REQUIRE(floor(perim * 1000) / 1000 == 2.441);
			}
		}
		WHEN("GetStartPoint()")
		{
			CPoint v1 = line.GetStartPoint();
			THEN("LefTop return correctly")
			{
				REQUIRE(v1.x == 2.0);
				REQUIRE(v1.y == 4.0);
			}
		}
		WHEN("GetEndPoint()")
		{
			CPoint v1 = line.GetEndPoint();
			THEN("LefTop return correctly")
			{
				REQUIRE(v1.x == 0.0);
				REQUIRE(v1.y == 2.6);
			}
		}
		WHEN("GetOutlineColor()")
		{
			uint32_t outlineColor = line.GetOutlineColor();
			THEN("GetOutlineColor return correctly correctly")
			{
				REQUIRE(outlineColor == 16711680);
			}
		}
		WHEN("ToString()")
		{
			string str = line.ToString();
			THEN("ToString return correctly correctly")
			{
				REQUIRE(str == "line start point: (2; 4), end point: (0; 2.6), outline color: #ff0000, perimeter: 2.44131");
			}
		}
		WHEN("Draw")
		{
			Mock<ICanvas> mock;
			When(Method(mock, DrawLine)).AlwaysReturn();
			ICanvas& canvas = mock.get();
			line.Draw(canvas);
			Verify(Method(mock, DrawLine)).Once();
		}
	}
}

TEST_CASE("Draw some shape and check count calls functions canvas")
{
	CPoint begin, end;
	begin.x = 2.0; begin.y = 4.0;
	end.x = 0.0; end.y = 2.6;
	CLineSegment line(begin, end, 16711680);
	CPoint center;
	center.x = 2.0; center.y = 4.0;
	CCircle circ(center, 10.5, 16711680, 65280);
	CPoint vert1, vert2, vert3;
	vert1.x = 2.0; vert1.y = 4.0;
	vert2.x = 0.0; vert2.y = 2.6;
	vert3.x = 2.9; vert3.y = 1.0;
	CTriangle trian(vert1, vert2, vert3, 16711680, 65280);
	CPoint leftPoint;
	leftPoint.x = 10.3; leftPoint.y = 20.15;
	CRectangle rect(leftPoint, 30.7, 40.4, 16711680, 65280);
	WHEN("Draw all functions")
	{
		Mock<ICanvas> mock;
		When(Method(mock, DrawLine)).AlwaysReturn();
		When(Method(mock, DrawPolygon)).AlwaysReturn();
		When(Method(mock, DrawCircle)).AlwaysReturn();
		ICanvas& canvas = mock.get();
		line.Draw(canvas);
		trian.Draw(canvas);
		rect.Draw(canvas);
		circ.Draw(canvas);
		Verify(Method(mock, DrawLine)).Once();
		Verify(Method(mock, DrawPolygon)).Exactly(2);
		Verify(Method(mock, DrawCircle)).Once();
	}
}