#include <iostream>
#include "VectorProcessing.h"
using namespace std;

int main()
{
	vector<double> numbers;
	ReadVector(cin, numbers);
	MultiplyingVectorByMinEl(numbers);
	SortVector(numbers);
	PrintVector(cout, numbers);
}