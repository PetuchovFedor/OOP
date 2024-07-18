#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

void ReadVector(std::istream& input,  std::vector<double>& numbers);

void MultiplyingVectorByMinEl(std::vector<double>& numbers);

void SortVector(std::vector<double>& numbers);

void PrintVector(std::ostream& output, const std::vector<double>& numbers);