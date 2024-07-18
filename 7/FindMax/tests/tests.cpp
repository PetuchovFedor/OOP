#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/FindMax.h"
using namespace std;

SCENARIO("find max on empty vector")
{
	vector<int> ve1;
	int max1;
	REQUIRE(!FindMax(ve1, max1));
	vector<double> ve2; 
	double max2;
	REQUIRE(!FindMax(ve2, max2));
	vector<float> ve3;
	float max3;
	REQUIRE(!FindMax(ve3, max3));
	vector<string> ve4;
	string max4;
	REQUIRE(!FindMax(ve4, max4));
	vector<const char*> ve5;
	const char* max5;
	REQUIRE(!FindMax(ve5, max5));
}

SCENARIO("find max on vector with one element")
{
	vector<int> ve1 = { 5 };
	int max1;
	REQUIRE(FindMax(ve1, max1));
	REQUIRE(max1 == 5);
	vector<double> ve2 = { 5.0 };
	double max2;
	REQUIRE(FindMax(ve2, max2));
	REQUIRE(max2 == 5.0);
	vector<float> ve3 = { 5.0f };
	float max3;
	REQUIRE(FindMax(ve3, max3));
	REQUIRE(max3 == 5.0f);
	vector<string> ve4 = { "qwe" };
	string max4;
	REQUIRE(FindMax(ve4, max4));
	REQUIRE(max4 == "qwe");
	vector<const char*> ve5 = { "qwe\0" };
	const char* max5;
	REQUIRE(FindMax(ve5, max5));
	REQUIRE(strcmp(max5, "qwe\0") == 0);
}

SCENARIO("Find max on vector with some element")
{
	vector<int> vec = { 0, 5, -3, 5, 7, 10, 1, 13, 2 };
	int max;
	REQUIRE(FindMax(vec, max));
	REQUIRE(max == 13);
	vector<float> vec1 = { 0.0f, 5.43f, -3.0f, 5.23f, 7, 10.43f, 13.54f, 13.21f, 2.0f };
	float max1;
	REQUIRE(FindMax(vec1, max1));
	REQUIRE(max1 == 13.54f);
	vector<double> vec2 = { 0.0, 5.98, -3.56, 5.89, 7.455, 10.34, 13, 13.08, 2.54 };
	double max2;
	REQUIRE(FindMax(vec2, max2));
	REQUIRE(max2 == 13.08);
	vector<string> vec3 = { "qwe", "qwer", "abcd", "acasds", "zzzzz" };
	string max3;
	REQUIRE(FindMax(vec3, max3));
	REQUIRE(max3 == "zzzzz");
	/*vector<const char*> vec2 = { "abcfd\0", "abcd\0", "zasca\0", "zzzz\0" };
	const char* max2;
	FindMax(vec2, max2);*/
}