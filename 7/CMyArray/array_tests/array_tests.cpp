#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/CMyArray.h"
#include <sstream>
#include <iostream>
using namespace std;

TEST_CASE("Check methods of my array")
{
	GIVEN("Empty my array of integer")
	{
		CMyArray<int> arr;
		THEN("Initials data")
		{
			REQUIRE(arr.GetCapacity() == 0);
			REQUIRE(arr.IsEmpty());
			REQUIRE(arr.GetSize() == 0);
		}
		WHEN("push one elem")
		{
			arr.PushBack(3);
			REQUIRE(arr[0] == 3);
			REQUIRE(!arr.IsEmpty());
			REQUIRE(arr.GetSize() == 1);
			WHEN("Incorrect indexes")
			{
				REQUIRE_THROWS_AS(arr[-2], out_of_range);
				REQUIRE_THROWS_AS(arr[1], out_of_range);
				REQUIRE_THROWS_AS(arr[10], out_of_range);
			}
		}
		WHEN("push some elem")
		{
			arr.PushBack(4);
			arr.PushBack(1);
			arr.PushBack(5);
			REQUIRE(arr[0] == 4);
			REQUIRE(arr[1] == 1);
			REQUIRE(arr[2] == 5);
			REQUIRE(arr.GetSize() == 3);
			WHEN("Incorrect indexes")
			{
				REQUIRE_THROWS_AS(arr[-1], out_of_range);
				REQUIRE_THROWS_AS(arr[3], out_of_range);
				REQUIRE_THROWS_AS(arr[10], out_of_range);
			}
			WHEN("resize <")
			{
				arr.Resize(1);
				REQUIRE(arr.GetSize() == 1);
				REQUIRE(arr[0] == 4);
				REQUIRE(arr.GetCapacity() == 4);
				REQUIRE_THROWS(arr[1]);
			}
			WHEN("resize >")
			{
				arr.Resize(5);
				REQUIRE(arr.GetSize() == 5);
				REQUIRE(arr[3] == 0);
				REQUIRE(arr[4] == 0);
				REQUIRE(arr.GetCapacity() == 5);
			}
			WHEN("clear")
			{
				arr.Clear();
				REQUIRE(arr.GetSize() == 0);
				REQUIRE(arr.GetCapacity() == 4);
			}
			WHEN("stl algoritmhs")
			{
				stringstream ss;
				WHEN("copy")
				{
					copy(arr.begin(), arr.end(), ostream_iterator<int>(ss, " "));
					REQUIRE(ss.str() == "4 1 5 ");
					copy(arr.rbegin(), arr.rend(), ostream_iterator<int>(ss, " "));
					REQUIRE(ss.str() == "4 1 5 5 1 4 ");
				}
				WHEN("sort")
				{
					sort(arr.begin(), arr.end());
					copy(arr.begin(), arr.end(), ostream_iterator<int>(ss, " "));
					REQUIRE(ss.str() == "1 4 5 ");
				}
				WHEN("max_element")
				{
					REQUIRE(*max_element(arr.begin(), arr.end()) == 5);
				}
				WHEN("for_each")
				{
					for_each(arr.begin(), arr.end(), [](int& a) { a += 5; });
					copy(arr.begin(), arr.end(), ostream_iterator<int>(ss, " "));
					REQUIRE(ss.str() == "9 6 10 ");
				}
			}
		}
	}
	GIVEN("Empty my array of double")
	{
		CMyArray<double> arr;
		THEN("Initials data")
		{
			REQUIRE(arr.GetCapacity() == 0);
			REQUIRE(arr.IsEmpty());
			REQUIRE(arr.GetSize() == 0);
		}
		WHEN("push one elem")
		{
			arr.PushBack(3.98);
			REQUIRE(floor(arr[0] * 100) / 100 == 3.98);
			REQUIRE(!arr.IsEmpty());
			REQUIRE(arr.GetSize() == 1);
			WHEN("Incorrect indexes")
			{
				REQUIRE_THROWS_AS(arr[-2], out_of_range);
				REQUIRE_THROWS_AS(arr[1], out_of_range);
				REQUIRE_THROWS_AS(arr[10], out_of_range);
			}
		}
		WHEN("push some elem")
		{
			arr.PushBack(4.123);
			arr.PushBack(1.0);
			arr.PushBack(5.8);
			REQUIRE(floor(arr[0] * 1000) / 1000 == 4.123);
			REQUIRE(arr[1] == 1.0);
			REQUIRE(floor(arr[2] * 10) / 10 == 5.8);
			REQUIRE(arr.GetSize() == 3);
			WHEN("Incorrect indexes")
			{
				REQUIRE_THROWS_AS(arr[-1], out_of_range);
				REQUIRE_THROWS_AS(arr[3], out_of_range);
				REQUIRE_THROWS_AS(arr[10], out_of_range);
			}
			WHEN("resize <")
			{
				arr.Resize(1);
				REQUIRE(arr.GetSize() == 1);
				REQUIRE(floor(arr[0] * 1000) / 1000 == 4.123);
				REQUIRE(arr.GetCapacity() == 4);
				REQUIRE_THROWS(arr[1]);
			}
			WHEN("resize >")
			{
				arr.Resize(5);
				REQUIRE(arr.GetSize() == 5);
				REQUIRE(arr[3] == 0.0);
				REQUIRE(arr[4] == 0.0);
				REQUIRE(arr.GetCapacity() == 5);
			}
			WHEN("clear")
			{
				arr.Clear();
				REQUIRE(arr.GetSize() == 0);
				REQUIRE(arr.GetCapacity() == 4);
			}
			WHEN("stl algoritmhs")
			{
				stringstream ss;
				WHEN("copy")
				{
					copy(arr.begin(), arr.end(), ostream_iterator<double>(ss, " "));
					REQUIRE(ss.str() == "4.123 1 5.8 ");
					copy(arr.rbegin(), arr.rend(), ostream_iterator<double>(ss, " "));
					REQUIRE(ss.str() == "4.123 1 5.8 5.8 1 4.123 ");
				}
				WHEN("sort")
				{
					sort(arr.begin(), arr.end());
					copy(arr.begin(), arr.end(), ostream_iterator<double>(ss, " "));
					REQUIRE(ss.str() == "1 4.123 5.8 ");
				}
				WHEN("max_element")
				{
					REQUIRE(*max_element(arr.begin(), arr.end()) == floor(5.8 * 10) / 10);
				}
				WHEN("for_each")
				{
					for_each(arr.begin(), arr.end(), [](double& a) { a += 5; });
					copy(arr.begin(), arr.end(), ostream_iterator<double>(ss, " "));
					REQUIRE(ss.str() == "9.123 6 10.8 ");
				}
			}
		}
	}
	
	GIVEN("Empty my array of std string")
	{
		CMyArray<string> arr;
		THEN("Initials data")
		{
			REQUIRE(arr.GetCapacity() == 0);
			REQUIRE(arr.IsEmpty());
			REQUIRE(arr.GetSize() == 0);
		}
		WHEN("push one elem")
		{
			arr.PushBack("qwer");
			REQUIRE(arr[0] == "qwer");
			REQUIRE(!arr.IsEmpty());
			REQUIRE(arr.GetSize() == 1);
			WHEN("Incorrect indexes")
			{
				REQUIRE_THROWS_AS(arr[-2], out_of_range);
				REQUIRE_THROWS_AS(arr[1], out_of_range);
				REQUIRE_THROWS_AS(arr[10], out_of_range);
			}
		}
		WHEN("push some elem")
		{
			arr.PushBack("ert");
			arr.PushBack("903");
			arr.PushBack("cvx");
			REQUIRE(arr[0] == "ert");
			REQUIRE(arr[1] == "903");
			REQUIRE(arr[2] == "cvx");
			REQUIRE(arr.GetSize() == 3);
			WHEN("Incorrect indexes")
			{
				REQUIRE_THROWS_AS(arr[-1], out_of_range);
				REQUIRE_THROWS_AS(arr[3], out_of_range);
				REQUIRE_THROWS_AS(arr[10], out_of_range);
			}
			WHEN("resize <")
			{
				arr.Resize(1);
				REQUIRE(arr.GetSize() == 1);
				REQUIRE(arr[0] == "ert");
				REQUIRE(arr.GetCapacity() == 4);
				REQUIRE_THROWS(arr[1]);
			}
			WHEN("resize >")
			{
				arr.Resize(5);
				REQUIRE(arr.GetSize() == 5);
				REQUIRE(arr[3] == "");
				REQUIRE(arr[4] == "");
				REQUIRE(arr.GetCapacity() == 5);
			}
			WHEN("clear")
			{
				arr.Clear();
				REQUIRE(arr.GetSize() == 0);
				REQUIRE(arr.GetCapacity() == 4);
			}
			WHEN("stl algoritmhs")
			{
				stringstream ss;
				WHEN("copy")
				{
					copy(arr.begin(), arr.end(), ostream_iterator<string>(ss, " "));
					REQUIRE(ss.str() == "ert 903 cvx ");
					copy(arr.rbegin(), arr.rend(), ostream_iterator<string>(ss, " "));
					REQUIRE(ss.str() == "ert 903 cvx cvx 903 ert ");
				}
				WHEN("sort")
				{
					sort(arr.begin(), arr.end());
					copy(arr.begin(), arr.end(), ostream_iterator<string>(ss, " "));
					REQUIRE(ss.str() == "903 cvx ert ");
				}
				WHEN("max_element")
				{
					REQUIRE(*max_element(arr.begin(), arr.end()) == "ert");
				}
				WHEN("for_each")
				{
					for_each(arr.begin(), arr.end(), [](string& a) { a = a + "123"; });
					copy(arr.begin(), arr.end(), ostream_iterator<string>(ss, " "));
					REQUIRE(ss.str() == "ert123 903123 cvx123 ");
				}
			}
		}
	}
}

//TEST_CASE("Check static cast = ")
//{
//	CMyArray<double> arr1; 
//	CMyArray<int> arr2;
//	arr1.PushBack(4.123);
//	arr1.PushBack(1.0);
//	arr1.PushBack(5.8);
//	arr2 = arr1;
//	REQUIRE(arr2[0] == 4);
//	REQUIRE(arr2[1] == 1);
//	REQUIRE(arr2[2] == 5);
//}

TEST_CASE("Chech constructors and assignment operations")
{
	WHEN("array of double")
	{
		stringstream ss1;
		stringstream ss2;
		WHEN("copy")
		{
			CMyArray<double> arr1;
			arr1.PushBack(4.123);
			arr1.PushBack(1.0);
			arr1.PushBack(5.8);
			CMyArray<double> arr2(arr1);
			copy(arr2.begin(), arr2.end(), ostream_iterator<double>(ss1, " "));
			REQUIRE(ss1.str() == "4.123 1 5.8 ");
			CMyArray<double> arr3;
			arr3 = arr1;
			arr3 = arr3;
			copy(arr3.begin(), arr3.end(), ostream_iterator<double>(ss2, " "));
			REQUIRE(ss2.str() == "4.123 1 5.8 ");
		}
		WHEN("move")
		{
			CMyArray<double> arr1;
			arr1.PushBack(4.123);
			arr1.PushBack(1.0);
			arr1.PushBack(5.8);
			CMyArray<double> arr2(move(arr1));
			copy(arr2.begin(), arr2.end(), ostream_iterator<double>(ss1, " "));
			REQUIRE(ss1.str() == "4.123 1 5.8 ");
			CMyArray<double> arr3;
			arr3 = move(arr2);
			arr3 = move(arr3);
			copy(arr3.begin(), arr3.end(), ostream_iterator<double>(ss2, " "));
			REQUIRE(ss2.str() == "4.123 1 5.8 ");
		}
	}
	WHEN("array of int")
	{
		stringstream ss1;
		stringstream ss2;
		WHEN("copy")
		{
			CMyArray<int> arr1;
			arr1.PushBack(4);
			arr1.PushBack(1);
			arr1.PushBack(5);
			CMyArray<int> arr2(arr1);
			copy(arr2.begin(), arr2.end(), ostream_iterator<int>(ss1, " "));
			REQUIRE(ss1.str() == "4 1 5 ");
			CMyArray<int> arr3;
			arr3 = arr1;
			arr3 = arr3;
			copy(arr3.begin(), arr3.end(), ostream_iterator<int>(ss2, " "));
			REQUIRE(ss2.str() == "4 1 5 ");
		}
		WHEN("move")
		{
			CMyArray<int> arr1;
			arr1.PushBack(4.123);
			arr1.PushBack(1.0);
			arr1.PushBack(5.8);
			CMyArray<int> arr2(move(arr1));
			copy(arr2.begin(), arr2.end(), ostream_iterator<int>(ss1, " "));
			REQUIRE(ss1.str() == "4 1 5 ");
			CMyArray<int> arr3; 
			arr3 = move(arr2);
			arr3 = move(arr3);
			copy(arr3.begin(), arr3.end(), ostream_iterator<int>(ss2, " "));
			REQUIRE(ss2.str() == "4 1 5 ");
		}
	}
	WHEN("array of stl string")
	{
		stringstream ss1;
		stringstream ss2;
		WHEN("copy")
		{
			CMyArray<string> arr1;
			arr1.PushBack("qwerty");
			arr1.PushBack("asdf");
			arr1.PushBack("zxc");
			CMyArray<string> arr2(arr1);
			copy(arr2.begin(), arr2.end(), ostream_iterator<string>(ss1, " "));
			REQUIRE(ss1.str() == "qwerty asdf zxc ");
			CMyArray<string> arr3;
			arr3 = arr1;
			arr3 = arr3;
			copy(arr3.begin(), arr3.end(), ostream_iterator<string>(ss2, " "));
			REQUIRE(ss2.str() == "qwerty asdf zxc ");
		}
		WHEN("move")
		{
			CMyArray<string> arr1;
			arr1.PushBack("qwerty");
			arr1.PushBack("asdf");
			arr1.PushBack("zxc");
			CMyArray<string> arr2(move(arr1));
			copy(arr2.begin(), arr2.end(), ostream_iterator<string>(ss1, " "));
			REQUIRE(ss1.str() == "qwerty asdf zxc ");
			CMyArray<string> arr3;
			arr3 = move(arr2);
			arr3 = move(arr3);
			copy(arr3.begin(), arr3.end(), ostream_iterator<string>(ss2, " "));
			REQUIRE(ss2.str() == "qwerty asdf zxc ");
		}
	}
}

TEST_CASE("Check situation when not all elements initializations")
{
	GIVEN("struct with variabel expression")
	{
		struct Data
		{
			Data(const Data& data)
			{
				if (data.throwOnComparison)
					throw std::runtime_error("something bad has happened");
				else
				{
					value = data.value;
					throwOnComparison = data.throwOnComparison;
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
		WHEN("Try to catch expression")
		{
			CMyArray<Data> arr;

			arr.PushBack({ 5, false });
			arr[0];
			arr[0].throwOnComparison = true;
			THEN("Catch")
			{
				REQUIRE_THROWS(arr.PushBack({ 9, false }));
			}
		}
	}

}