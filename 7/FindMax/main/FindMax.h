#pragma once
#include <vector>
#include <algorithm>
template <typename T>

bool FindMax(std::vector<T> const& arr, T& maxValue)
{
	if (arr.empty())
		return false;

	maxValue = *std::max_element(arr.begin(), arr.end());
	
	/*auto iterMax = arr.begin();
	for (auto iter = arr.begin() + 1; iter != arr.end(); iter++)
	{
		if (*iter > *iterMax)
			iterMax = it;
	}
	maxValue = *iterMax;*/
	return true;
}

template <>
bool FindMax<const char*>(std::vector<const char*> const& arr, const char*& maxValue)
{
	if (arr.empty())
		return false;
	maxValue = *std::max_element(arr.begin(), arr.end());
	/*auto iterMax = arr.begin();
	for (auto iter = arr.begin() + 1; iter != arr.end(); iter++)
	{
		if (strcmp(*iter, *iterMax) > 0)
			iterMax = iter;
	}
	maxValue = *iterMax;*/
	return true;
}
