#include <iostream>
#include <string>
using namespace std;

int FlipByte(int  num)
{
    num = ((num & 0b1111) << 4) | ((num & 0b11110000) >> 4);
    num = ((num & 0b00110011) << 2) | ((num & 0b11001100) >> 2);
    num = ((num & 0b01010101) << 1) | ((num & 0b10101010) >> 1);
    return num;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Incorrect number of command line arguments. The command line should look like: flipbyte.exe <input byte>" << endl;
        return 1;
    }
    try
    {
        double inputParam = stod(argv[1]);
        if ((inputParam < 0) || (inputParam > 255))
            throw invalid_argument("Beyond 0 - 255");
        int temp = static_cast<int>(inputParam);
        if ((inputParam - temp) > 0)
            throw invalid_argument("Not a int number");
        int inputNum = static_cast<int>(inputParam);
        cout << FlipByte(inputNum) << endl;
    }
    catch (const invalid_argument& e)
    {
        cout << e.what() << endl;
        return 1;
    }
}
