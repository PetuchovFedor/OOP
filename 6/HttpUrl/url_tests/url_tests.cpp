#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include <iostream>
#include "../main/CHttpUrl.h"
#include "../main/CUrlParsingError .h"

TEST_CASE("CreateUrl")
{
	WHEN("first constructor without port")
	{
		CHttpUrl url("http://qwerty.com/rt.jpg");
		THEN("get url")
		{
			REQUIRE(url.GetURL() == "http://qwerty.com/rt.jpg");
		}
		THEN("get protocol")
		{
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
		}
		THEN("get domain")
		{
			REQUIRE(url.GetDomain() == "qwerty.com");
		}
		THEN("get port")
		{
			REQUIRE(url.GetPort() == 80);
		}
		THEN("get document")
		{
			REQUIRE(url.GetDocument() == "/rt.jpg");
		}
	}
	WHEN("first constructor with port")
	{
		CHttpUrl url("https://qwerty.com:96/rt.jpg");
		THEN("get url")
		{
			REQUIRE(url.GetURL() == "https://qwerty.com:96/rt.jpg");
		}
		THEN("get protocol")
		{
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
		THEN("get domain")
		{
			REQUIRE(url.GetDomain() == "qwerty.com");
		}
		THEN("get port")
		{
			REQUIRE(url.GetPort() == 96);
		}
		THEN("get document")
		{
			REQUIRE(url.GetDocument() == "/rt.jpg");
		}
	}
	//корректные названия
	WHEN("second constructor")
	{
		CHttpUrl url("app.ru", "asfdf/fewe/pot.html", Protocol::HTTPS);
		THEN("get url")
		{
			REQUIRE(url.GetURL() == "https://app.ru/asfdf/fewe/pot.html");
		}
		THEN("get protocol")
		{
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
		THEN("get domain")
		{
			REQUIRE(url.GetDomain() == "app.ru");
		}
		THEN("get port")
		{
			REQUIRE(url.GetPort() == 443);
		}
		THEN("get document")
		{
			REQUIRE(url.GetDocument() == "/asfdf/fewe/pot.html");
		}
	}
	WHEN("third constructor")
	{
		CHttpUrl url("app.ru", "asfdf/fewe/pot.html", Protocol::HTTPS, 113);
		THEN("get url")
		{
			REQUIRE(url.GetURL() == "https://app.ru:113/asfdf/fewe/pot.html");
		}
		THEN("get protocol")
		{
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
		THEN("get domain")
		{
			REQUIRE(url.GetDomain() == "app.ru");
		}
		THEN("get port")
		{
			REQUIRE(url.GetPort() == 113);
		}
		THEN("get document")
		{
			REQUIRE(url.GetDocument() == "/asfdf/fewe/pot.html");
		}
	}
	WHEN("first constructor without port and empty document")
	{
		CHttpUrl url("http://qwerty.com");
		THEN("get url")
		{
			REQUIRE(url.GetURL() == "http://qwerty.com/");
		}
		THEN("get protocol")
		{
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
		}
		THEN("get domain")
		{
			REQUIRE(url.GetDomain() == "qwerty.com");
		}
		THEN("get port")
		{
			REQUIRE(url.GetPort() == 80);
		}
		THEN("get document")
		{
			REQUIRE(url.GetDocument() == "/");
		}
	}
	WHEN("first constructor with port and empty docement")
	{
		CHttpUrl url("https://qwerty.com:96");
		THEN("get url")
		{
			REQUIRE(url.GetURL() == "https://qwerty.com:96/");
		}
		THEN("get protocol")
		{
			REQUIRE(url.GetProtocol() == Protocol::HTTPS);
		}
		THEN("get domain")
		{
			REQUIRE(url.GetDomain() == "qwerty.com");
		}
		THEN("get port")
		{
			REQUIRE(url.GetPort() == 96);
		}
		THEN("get document")
		{
			REQUIRE(url.GetDocument() == "/");
		}
	}
}

TEST_CASE("Check exceprion with creating")
{
	//пересмотреть структуру 
	WHEN("first constructor")
	{
		//для невалидного порта
		THEN("exception with protocol")
		{
			REQUIRE_THROWS_AS(CHttpUrl("ftp://qewq.com"), CUrlParsingError);
		}
		THEN("exception with ://")
		{
			REQUIRE_THROWS_AS(CHttpUrl("qwrewqwr"), CUrlParsingError);
		}
		THEN("exception with domain")
		{
			REQUIRE_THROWS_AS(CHttpUrl("http://"), CUrlParsingError);
		}
	}
	WHEN("second constructor")
	{
		THEN("exception with empty domain")
		{
			REQUIRE_THROWS_AS(CHttpUrl("", "asfas.html", Protocol::HTTP), std::invalid_argument);
		}
	}
	WHEN("third constructor")
	{
		THEN("exception with empty domain")
		{
			REQUIRE_THROWS_AS(CHttpUrl("", "asfas.html", Protocol::HTTP, 854), std::invalid_argument);
		}
		THEN("exception with port")
		{
			REQUIRE_THROWS_AS(CHttpUrl("qwwety.com", "asfas.html", Protocol::HTTP, -1), std::invalid_argument);
		}
		THEN("exception with port")
		{
			REQUIRE_THROWS_AS(CHttpUrl("qwwety.com", "asfas.html", Protocol::HTTP, 65535), std::invalid_argument);
		}
		THEN("boundary values port")
		{
			REQUIRE_NOTHROW(CHttpUrl("qwwety.com", "asfas.html", Protocol::HTTP, 0));
			REQUIRE_NOTHROW(CHttpUrl("qwwety.com", "asfas.html", Protocol::HTTP, 65534));
		}
	}
}