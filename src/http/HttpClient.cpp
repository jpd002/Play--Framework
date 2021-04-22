#include "http/HttpClient.h"
#include "string_format.h"

#include <set>

using namespace Framework::Http;

GlobalSettingMap CHttpClient::m_globalSettings;

std::string CHttpClient::UrlEncode(const std::string& input)
{
	static const std::set<char> allowedSymbols = {'-', '_', '.', '~', '/'};

	std::string result;
	for(auto inputChar : input)
	{
		if(isalnum(inputChar) || allowedSymbols.find(inputChar) != allowedSymbols.end())
		{
			result += inputChar;
		}
		else
		{
			result += string_format("%%%02X", inputChar);
		}
	}
	return result;
}

void CHttpClient::SetGlobalSetting(GLOBAL_SETTING setting, std::string value)
{
	m_globalSettings[setting] = value;
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

void CHttpClient::SetRequestBody(ByteArray requestBody)
{
	m_requestBody = std::move(requestBody);
}

void CHttpClient::SetRequestBody(std::string requestBody)
{
	SetRequestBody(ByteArray(requestBody.c_str(), requestBody.c_str() + requestBody.length()));
}
