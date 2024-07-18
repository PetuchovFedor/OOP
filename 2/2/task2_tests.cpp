#include <iostream>
#define CATCH_CONFIG_MAIN
#include <sstream>
#include "../../catch2/catch.hpp"
#include "../task2/HtmlDecode.h"
using namespace std;

SCENARIO("Empty string decoded in empty string")
{
	const string str;
	REQUIRE(HtmlDecode(str).empty());
}

SCENARIO("Decoded one string")
{
	const string str = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	const string result = "Cat <says> \"Meow\". M&M's";
	REQUIRE(HtmlDecode(str) == result);
}

SCENARIO("Decoded some strings")
{
	const string str = R"(Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s
        Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s
        Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s)";
	const string result = R"(Cat <says> "Meow". M&M's
        Cat <says> "Meow". M&M's
        Cat <says> "Meow". M&M's)";
	REQUIRE(HtmlDecode(str) == result);
}