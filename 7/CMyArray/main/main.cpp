#include <iostream>
#include <vector>
#include "CMyArray.h"
#include <algorithm>
#include <string>
#include <iterator>
using namespace std;

struct Data
{
	Data()
	{
		//throw std::runtime_error("something bad has happened");
	}
	Data(const Data& d)
	{
		if (d.throwOnComparison)
			throw std::runtime_error("something bad has happened");
		else
		{
			value = d.value;
			throwOnComparison = d.throwOnComparison;
		}
	}
	Data(int v, bool b)
	{
		if (b)
			throw std::runtime_error("something bad has happened");
		else
		{
			value = v;
			throwOnComparison = b;
		}
	}

	int value = 0;
	bool throwOnComparison = false;
};


bool operator<(const Data& lhs, const Data& rhs)
{
    if (lhs.throwOnComparison || rhs.throwOnComparison)
    {
        throw std::runtime_error("something bad has happened");
    }
    return lhs.value < rhs.value;
}

bool operator==(const Data& lhs, const Data& rhs)
{
    return lhs.value == rhs.value;
}


int main()
{
    CMyArray<Data> ve;
    ve.PushBack({ 5, false });
    ve.PushBack({ 5, false });
    ve.PushBack({ 5, false });
	ve[1].throwOnComparison = true;
    ve.Resize(6);
    for (size_t i = 0; i < ve.GetSize(); i++)
    {
        //cout << ve[i] << endl;
    }
   // CMyArray<int> ve;
   // //ve.resize(4);
   // //ve.size();
   // ve.PushBack(4);
   // ve.PushBack(43);
   // ve.PushBack(24);
   // ve.Reserve(20);
   // ve.PushBack(41);
   // ve.PushBack(34);
   // ve.PushBack(14);
   // //ve.GetCapacity();
   //// ve.Resize(7);
   // //ve.PushBack(14);
   // //ve.PushBack(134);
   // CMyArray<double> ve1; 
   // ve1 = ve;
   // for (int i = 0; i < ve1.GetSize(); i++)
   // {
   //     cout << ve1[i] << endl;
   // }
    //ve.end();
    //CMyArray<Data> arr;

}
