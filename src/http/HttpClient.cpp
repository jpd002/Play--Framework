#include "http/HttpClient.h"
#include "string_format.h"

using namespace Framework::Http;

std::string CHttpClient::UrlEncode(const std::string& input)
{
	std::string result;
	for(auto inputChar : input)
	{
		switch(inputChar)
		{
		case ':':
		case ' ':
		case '&':
		case '+':
		case '\'':
			result += string_format("%%%02X", inputChar);
			break;
		default:
			result += inputChar;
			break;
		}
	}
	return result;
}

HeaderMap CHttpClient::ReadHeaderMap(Framework::CStream& stream)
{
	HeaderMap result;
	auto line = stream.ReadLine();
	while(!stream.IsEOF())
	{
		auto colonPos = line.find(':');
		if(colonPos != std::string::npos)
		{
			auto key = std::string(line.substr(0, colonPos));
			auto value = std::string(line.substr(colonPos + 2, line.length()));
			result.insert(std::make_pair(key, value));
		}
		line = stream.ReadLine();
	}
	return result;
}

void CHttpClient::SetUrl(std::string url)
{
	m_url = std::move(url);
}

void CHttpClient::SetVerb(HTTP_VERB verb)
{
	m_verb = verb;
}

void CHttpClient::SetHeaders(HeaderMap headers)
{
	m_headers = std::move(headers);
}

void CHttpClient::SetRequestBody(std::string requestBody)
{
	m_requestBody = std::move(requestBody);
}
