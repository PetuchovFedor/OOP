#include <iostream>
#define CATCH_CONFIG_MAIN
#include <sstream>
#include "../../catch2/catch.hpp"
#include "../vector/VectorProcessing.h"
using namespace std;

SCENARIO("If nothing is entered then the vector is empty")
{
	istringstream input("");
	vector<double> numbers;
	ReadVector(input, numbers);
	REQUIRE(numbers.empty());
}

SCENARIO("If the vector is empty then nothing will be output")
{
	ostringstream output;
	vector<double> numbers;
	PrintVector(output, numbers);
	REQUIRE(output.str() == "");
}

SCENARIO("Checking for the correctness of multiplication by the minimum element")
{
	vector<double> numbers = {9, 3.4, 4, 0.45, -2};
	vector<double> result = { -18, -6.8, -8, -0.9, 4 };
	MultiplyingVectorByMinEl(numbers);
	REQUIRE(numbers == result);
}

SCENARIO("Checking vector sorting")
{
	vector<double> numbers = { 9, 3.4, 4, 0.45, -2 };
	vector<double> sortedNumbers = { -2, 0.45, 3.4,  4, 9 };
	SortVector(numbers);
	REQUIRE(numbers == sortedNumbers);
}
