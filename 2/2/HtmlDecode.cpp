#include "HtmlDecode.h"
#include <regex>
using namespace std;

std::string HtmlDecode(const std::string& str)
{
    string temp = str;
    temp = regex_replace(temp, regex("&quot;"), "\"");
    temp = regex_replace(temp, regex("&apos;"), "\'");
    temp = regex_replace(temp, regex("&lt;"), "<");
    temp = regex_replace(temp, regex("&gt;"), ">");
    temp = regex_replace(temp, regex("&amp;"), "&");
    return temp;
}
