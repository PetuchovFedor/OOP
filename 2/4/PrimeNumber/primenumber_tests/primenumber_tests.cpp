#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../main/primeNumber.h"
#include <ctime>
using namespace std;
//Больше тестов
SCENARIO("Cheching count of prime numbers if argument equals 100000000")
{
	int N = 100000000;
	set<int> primeNumbers = GeneratePrimeNumbersSet(N);
	REQUIRE(primeNumbers.size() == 5761455);
}

SCENARIO("Cheching count of prime numbers if argument equals 100")
{
	int N = 100;
	set<int> primeNumbers = GeneratePrimeNumbersSet(N);
	REQUIRE(primeNumbers.size() == 25);
}

//Пом=смотреть как подключить тет только в Debug конфигурации
SCENARIO("Cheching time of working if argument equals 100000000")
{
	int N = 100000000;
	unsigned start = clock();
	set<int> primeNumbers = GeneratePrimeNumbersSet(N);
	unsigned end = clock();
	REQUIRE(end - start < 12000);
}