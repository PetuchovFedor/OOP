#include <iostream>
#include "primeNumber.h"
#include <string>
#include <iterator>
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Incorrect number of command line arguments. The command line should look like: main.exe number\n";
        return 1;
    }
    try
    {
        int upperBount = stoi(argv[1]);
        set<int> primeNumbers = GeneratePrimeNumbersSet(upperBount);
        copy(primeNumbers.begin(), primeNumbers.end(), ostream_iterator<int>(cout, " "));
    }
    catch (const exception& e) 
    {
        cout << e.what() << "\n";
    }
}
