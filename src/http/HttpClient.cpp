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
			result += string_format("%%%02x", inputChar);
			break;
		default:
			result += inputChar;
			break;
		}
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

void CHttpClient::SetRequestBody(std::string requestBody)
{
	m_requestBody = std::move(requestBody);
}
