#include <iostream>
#include "HtmlDecode.h"
using namespace std;

int main()
{
    string str;
    getline(cin, str, static_cast<char>(EOF));
    cout << HtmlDecode(str) << endl;
}