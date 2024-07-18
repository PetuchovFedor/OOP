#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/CMyString.h"
#include <sstream>
using namespace std;

TEST_CASE("Checking conctuctors")
{
	WHEN("default")
	{
		CMyString myStr;
		THEN("Initial data")
		{
			REQUIRE(myStr.GetLength() == 0);
			REQUIRE(myStr.GetStringData() == "\0");
			REQUIRE_THROWS_AS(myStr.SubString(1, 4), out_of_range);
			myStr.Clear();
			THEN("data is null")
			{
				REQUIRE(myStr.GetLength() == 0);
				REQUIRE(myStr.GetStringData() == "\0");
			}
		}
	}
	WHEN("char*")
	{
		CMyString myStr("qwerty");
		THEN("Methods return correct data")
		{
			REQUIRE(myStr.GetLength() == 6);
			REQUIRE(memcmp(myStr.GetStringData(),"qwerty", 6) == 0);
			CMyString subStr = myStr.SubString(1, 3);			
			REQUIRE_THROWS_AS(myStr.SubString(1, 10), out_of_range);
			REQUIRE(memcmp(subStr.GetStringData(), "wer", 3) == 0);
			myStr.Clear();
			THEN("data is null")
			{
				REQUIRE(myStr.GetLength() == 0);
				REQUIRE(myStr.GetStringData() == "\0");
			}
		}
	}
	WHEN("char* with length")
	{
		CMyString myStr("qwerty", 3);

		THEN("Methods return correct data")
		{
			REQUIRE(myStr.GetLength() == 3);
			REQUIRE(memcmp(myStr.GetStringData(), "qwe", 3) == 0);
			CMyString subStr = myStr.SubString(0, 2);
			REQUIRE_THROWS_AS(myStr.SubString(1, 10), out_of_range);
			REQUIRE(memcmp(subStr.GetStringData(), "qw", 3) == 0);
			myStr.Clear();
			THEN("data is null")
			{
				REQUIRE(myStr.GetLength() == 0);
				REQUIRE(myStr.GetStringData() == "\0");
			}
		}
	}

	WHEN("stl string")
	{
		string str = "qwerty";
		CMyString myStr(str);
		THEN("Methods return correct data")
		{
			REQUIRE(myStr.GetLength() == 6);
			REQUIRE(memcmp(myStr.GetStringData(), "qwerty", 6) == 0);
			CMyString subStr = myStr.SubString(1, 3);
			REQUIRE_THROWS_AS(myStr.SubString(1, 10), out_of_range);
			REQUIRE(memcmp(subStr.GetStringData(), "wer", 3) == 0);
			myStr.Clear();
			THEN("data is null")
			{
				REQUIRE(myStr.GetLength() == 0);
				REQUIRE(myStr.GetStringData() == "\0");
			}
		}
	}
	WHEN("copy construct")
	{
		string str = "qwerty";
		CMyString myStr(str);
		CMyString myStr1(myStr);
		THEN("Methods return correct data")
		{
			REQUIRE(myStr.GetLength() == 6);
			REQUIRE(memcmp(myStr.GetStringData(), "qwerty", 6) == 0);
			REQUIRE(memcmp(myStr.GetStringData(), myStr1.GetStringData(), 6) == 0);
			REQUIRE(myStr1.GetLength() == 6);
			REQUIRE(memcmp(myStr1.GetStringData(), "qwerty", 6) == 0);

			myStr.Clear();
			myStr1.Clear();
			THEN("data is null")
			{
				REQUIRE(myStr.GetLength() == 0);
				REQUIRE(myStr.GetStringData() == "\0");
				REQUIRE(myStr1.GetLength() == 0);
				REQUIRE(myStr1.GetStringData() == "\0");
			}
		}
	}
	//Перемещающий
}

TEST_CASE("Checking operations on all constructors")
{
	WHEN("default constr")
	{
		//Добавить проверку самого себя
		CMyString myStr;
		THEN("Operations")
		{
			REQUIRE(myStr == CMyString());
			myStr = "str";
			REQUIRE(myStr == CMyString("str"));
			REQUIRE((myStr + CMyString("ing")) == CMyString("string"));
			REQUIRE(("ing" + myStr) == CMyString("ingstr"));
			string str = "str";
			REQUIRE((str + myStr) == CMyString("strstr"));
			myStr += CMyString("ing");
			REQUIRE(myStr == CMyString("string"));
			REQUIRE(myStr > CMyString("strinag"));
			REQUIRE(myStr >= CMyString("strinag"));
			REQUIRE(myStr >= CMyString("string"));
			REQUIRE(myStr < CMyString("strinng"));
			REQUIRE(myStr <= CMyString("strinng"));
			REQUIRE(myStr <= CMyString("string"));
		}
	}
	WHEN("char* const")
	{
		CMyString myStr("mystr");
		THEN("Operations")
		{
			REQUIRE(myStr == CMyString("mystr"));
			REQUIRE((myStr + CMyString("ing")) == CMyString("mystring"));
			REQUIRE(("ing" + myStr) == CMyString("ingmystr"));
			string str = "str";
			REQUIRE((str + myStr) == CMyString("strmystr"));
			myStr += CMyString("ing");
			REQUIRE(myStr == CMyString("mystring"));
			REQUIRE(myStr > CMyString("mystrinag"));
			REQUIRE(myStr >= CMyString("mystrinag"));
			REQUIRE(myStr >= CMyString("mystring"));
			REQUIRE(myStr < CMyString("mystrinng"));
			REQUIRE(myStr <= CMyString("mystrinng"));
			REQUIRE(myStr <= CMyString("mystring"));
		}
	}
	WHEN("char* with length constr")
	{
		CMyString myStr("string", 3);
		THEN("Operations")
		{
			REQUIRE(myStr == CMyString("str"));
			REQUIRE((myStr + CMyString("ing")) == CMyString("string"));
			REQUIRE(("ing" + myStr) == CMyString("ingstr"));
			string str = "str";
			REQUIRE((str + myStr) == CMyString("strstr"));
			myStr += CMyString("ing");
			REQUIRE(myStr == CMyString("string"));
			REQUIRE(myStr > CMyString("strinag"));
			REQUIRE(myStr >= CMyString("strinag"));
			REQUIRE(myStr >= CMyString("string"));
			REQUIRE(myStr < CMyString("strinng"));
			REQUIRE(myStr <= CMyString("strinng"));
			REQUIRE(myStr <= CMyString("string"));
		}
	}
	WHEN("stl string constr")
	{
		string str = "str";
		CMyString myStr(str);
		THEN("Operations")
		{
			REQUIRE(myStr == CMyString("str"));
			REQUIRE((myStr + CMyString("ing")) == CMyString("string"));
			REQUIRE(("ing" + myStr) == CMyString("ingstr"));
			REQUIRE((str + myStr) == CMyString("strstr"));
			myStr += CMyString("ing");
			REQUIRE(myStr == CMyString("string"));
			REQUIRE(myStr > CMyString("strinag"));
			REQUIRE(myStr >= CMyString("strinag"));
			REQUIRE(myStr >= CMyString("string"));
			REQUIRE(myStr < CMyString("strinng"));
			REQUIRE(myStr <= CMyString("strinng"));
			REQUIRE(myStr <= CMyString("string"));
		}
	}
}

SCENARIO("indexex")
{
	CMyString myStr;
	REQUIRE_THROWS_AS(myStr[2], out_of_range);
	myStr = CMyString("qwerty");
	REQUIRE(myStr[3] == 'r');
	myStr[3] = 'e';
	REQUIRE(myStr[3] == 'e');
}

SCENARIO("istream and ostream")
{
	istringstream is("qwerty");
	CMyString myStr;
	is >> myStr;
	REQUIRE(myStr == CMyString("qwerty"));
	REQUIRE(myStr.GetLength() == 6);
	ostringstream os;
	os << myStr;
	REQUIRE(os.str() == myStr.GetStringData());
}