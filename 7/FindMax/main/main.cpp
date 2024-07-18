#include <iostream>
#include "FindMax.h"
using namespace std;

int main()
{
	vector<int> vec = { 0, 5, -3, 5, 7, 10, 1, 13, 2 };
	int max;
	FindMax(vec, max);
	cout << "Max of int array: " << max << endl;
	vector<float> vec1 = { 0.0f, 5.43f, -3.0f, 5.23f, 7, 10.43f, 13.54f, 13.21f, 2.0f };
	float max1;
	FindMax(vec1, max1);
	cout << "Max of float array: " << max1 << endl;
	vector<const char*> vec2 = { "abcfd\0", "abcd\0", "zasca\0", "zzzz\0" };
	const char* max2;
	FindMax(vec2, max2);
	cout << "Max of char* array: " << max2 << endl;
	vector<double> vec3 = { 0.0, 5.98, -3.56, 5.89, 7.455, 10.34, 13, 13.08, 2.54 };
	double max3;
	FindMax(vec3, max3);
	cout << "Max of double array: " << max3 << endl;
	vector<string> vec4 = { "qwe", "qwer", "abcd", "acasds", "zzzzz" };
	string max4;
	FindMax(vec4, max4);
	cout << "Max of stl string array: " << max4 << endl;
}
