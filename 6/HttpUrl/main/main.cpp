#include <iostream>
#include "CHttpUrl.h"
using namespace std;

int main()
{
	string input;
	while (getline(cin, input))
	{
		try
		{
			CHttpUrl url(input);
			cout << "protocol: " << url.ProtocolToString() << endl;
			cout << "domain: " << url.GetDomain() << endl;
			cout << "port: " << url.GetPort() << endl;
			cout << "document: " << url.GetDocument() << endl;
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
	}
}