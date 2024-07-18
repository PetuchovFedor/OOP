#include "CHttpUrl.h"
#include "CUrlParsingError .h"
#include <regex>
#include <sstream>
#include <algorithm>
using namespace std;

CHttpUrl::CHttpUrl(std::string const& url)
{
	//выбрасывать своё исключение из Parseurl

	try
	{
		ParseUrl(url);
	}
	catch (const exception& e)
	{
		throw CUrlParsingError(e.what());
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: CHttpUrl(domain, document, protocol, (protocol == Protocol::HTTP ? 80 : 443))
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
{
	if (domain.empty())
		throw invalid_argument("Wrong domain");
	if (port >= 65535)
		throw invalid_argument("Wrong port. It shoud be in [0 - 65535]");
	m_document = ParseDocument(document);
	m_domain = domain;
	m_protocol = protocol;
	m_port = port;
}

std::string CHttpUrl::GetURL() const
{
	ostringstream strm;
	strm << ProtocolToString();
	strm << "://" << m_domain;
	(m_port != 80 && m_port != 443) ? strm << ':' << m_port : strm << "";
	strm << m_document;
	return strm.str();
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::ProtocolToString() const
{
	return (m_protocol == Protocol::HTTP) ? "http" : "https";
}

void CHttpUrl::ParseUrl(const std::string& url)
{
	smatch matches;
	regex regex("^([[:alpha:]]+)://([-.[:alnum:]]+)(:([[:digit:]]+))?(/(.*))?$");
	regex_search(url, matches, regex);
	//выбрасывать своё исключение из Parseurl
	if (matches.empty())
		throw invalid_argument("WrongUrl");
	m_protocol = ParseProtocol(matches[1]);
	m_domain = matches[2];
	m_port = ParsePort(matches[4]);
	m_document = ParseDocument(matches[6]);
}

Protocol CHttpUrl::ParseProtocol(const std::string& protocol)
{
	string str = protocol;
	transform(str.begin(), str.end(), str.begin(), [](unsigned char ch) {
		return tolower(ch);
		});
	//выбрасывать своё исключение из Parseurl

	if (str != "http" && str != "https")
		throw invalid_argument("Wrong protocol");
	return str == "http" ? Protocol::HTTP : Protocol::HTTPS;
}

unsigned short CHttpUrl::ParsePort(const std::string& port)
{
	if (port.empty())
		return m_protocol == Protocol::HTTP ? 80 : 443;
	int num = stoi(port);
	//в константу 65535
	if (num > 65535 && num <= 0)
		throw invalid_argument("Wrong port. It shoud be in [0 - 65535]");
	return static_cast<unsigned short>(num);
}

std::string CHttpUrl::ParseDocument(const std::string& document)
{
	return (document.empty() || document[0] != '/') ? '/' + document : document;
}

