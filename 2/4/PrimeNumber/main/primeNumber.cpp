#include "primeNumber.h"
#include <iostream>
#include <vector>
using namespace std;

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    set<int> primeNumbers;
    vector<bool>prime(upperBound + 1, true);
    //улучшить алгоритм: неходить по чётным числам
    for (int i = 2; i <= sqrt(upperBound); i++)
        if (prime[i]) 
            for (int j = i * i; j <= upperBound; j += i)
                prime[j] = false;

    for (int i = 2; i < prime.size(); i++)
        if (prime[i])
            primeNumbers.insert(i);
    return primeNumbers;
}
