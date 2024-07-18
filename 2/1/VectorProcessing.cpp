#include "VectorProcessing.h"


void ReadVector(std::istream& input, std::vector<double>& numbers)
{
	copy(std::istream_iterator<double>(input), std::istream_iterator<double>(), back_inserter(numbers));
}

void MultiplyingVectorByMinEl(std::vector<double>& numbers)
{
	if (numbers.empty())
		return;
	double min = *min_element(numbers.begin(), numbers.end());
	transform(numbers.begin(), numbers.end(), numbers.begin(), [&](double i) { return i * min; });
}

void SortVector(std::vector<double>& numbers)
{
	if (numbers.empty())
		return;
	sort(numbers.begin(), numbers.end(), [](double first, double second) { return first < second; });
}

void PrintVector(std::ostream& output, const std::vector<double>& numbers)
{
	copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(output, " "));
}