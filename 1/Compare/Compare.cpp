#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int CompareFiles(ifstream& file1, ifstream& file2)
{
	if (file1.peek() == EOF && file2.peek() == EOF)
		return 0;
	string str1;
	string str2;
	int lineNumber = 1;

	while (!file1.eof() && !file2.eof())
	{
		getline(file1, str1);
		getline(file2, str2);
		if (str1 != str2)
			return lineNumber;
		lineNumber++;
	}
	if (file1.eof() && file2.eof())
		return 0;
}
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Incorrect number of command line arguments. The command line should look like: compare.exe <file1> <file2>" << endl;
		return 1;
	}

	ifstream input1(argv[1]);
	ifstream input2(argv[2]);

	if (!input1.is_open() || !input2.is_open()) {
		cout << "Error opening a file for reading" << endl;
		return 1;
	}
	int lineNumber = CompareFiles(input1, input2);
	if (lineNumber == 0)
	{
		cout << "Files are equal" << endl;
		return 0;
	}
	else
	{
		cout << "Files are different. Line number is " << lineNumber << endl;
		return 1;
	}
}
