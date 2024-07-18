#include <windows.h>
#include "dictionary.h"
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Incorrect number of command line arguments. The command line should look like: main.exe <file1>\n";
        return 1;
    }
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    Dictionary dict = LoadDictionary(argv[1]);
    //Более надёдный способ определения ищменений без полного сравнения
    if (DialogProgramWithUser(cout, dict))
        //Выделить в функцию  
        if (IsNeedToSaveDictionary(cin, cout))
            SaveDictionary(argv[1], dict);
}
            

