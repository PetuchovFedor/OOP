#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../main/dictionary.h"
#include <algorithm>
#include <sstream>
using namespace std;


SCENARIO("Load dictionary from nonexistent file")
{
	LoadDictionary("file.txt");
	REQUIRE(LoadDictionary("file.txt").empty());
}

//SCENARIO("Load dictionary from test file")
//{
//	Dictionary dict1;
//	dict1.insert({ "test", "тест" });
//	dict1.insert({ "house", "дом" });
//	dict1.insert({ "home", "дом" });
//	Dictionary dict2 = LoadDictionary("test.txt");
//	//auto pred = [] (const auto& pair1, const auto& pair2) 
//	//{
//	//	return pair1.first == pair2.first && pair1.second == pair2.second;
//	//};
//	REQUIRE(dict1.size() == dict2.size() && equal(dict1.begin(), dict1.end(), dict2.begin(), 
//		[](const auto& pair1, const auto& pair2) {
//			return pair1.first == pair2.first && pair1.second == pair2.second;
//		})
//	);
//}

SCENARIO("Translate phrase from english to russian")
{
	Dictionary dict;
	dict.insert({ "row", "ряд" });
	string str = "row";
	ostringstream output;
	TranslatePhraseFromEnglishToRussian(dict, output, str);
	REQUIRE(output.str() == "ряд\n");
}

SCENARIO("Translate phrase from russian to english")
{
	Dictionary dict;
	dict.insert({ "row", "ряд" });
	string str = "ряд";
	ostringstream output;
	TranslatePhraseFromRussianToEnglish(dict, output, str);
	REQUIRE(output.str() == "row\n");
}

SCENARIO("Translate phrase from english to russian(some translation)")
{
	Dictionary dict;
	dict.insert({ "cat", "кошка" });
	dict.insert({ "cat", "кот" });
	dict.insert({ "cat", "киса" });
	string str = "cat";
	ostringstream output;
	TranslatePhraseFromEnglishToRussian(dict, output, str);
	REQUIRE(output.str() == "кошка, кот, киса\n");
}

SCENARIO("Translate phrase from russian to english(some translation)")
{
	Dictionary dict;
	dict.insert({ "word", "слово" });
	dict.insert({ "phrase", "слово" });
	string str = "слово";
	ostringstream output;
	TranslatePhraseFromRussianToEnglish(dict, output, str);
	REQUIRE(output.str() == "phrase, word\n");
}