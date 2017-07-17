#include <cassert>
#include "http/Win32HttpClient.h"
#include "win32/InternetHandle.h"
#include "tcharx.h"
#include "string_cast.h"

using namespace Framework;
using namespace Framework::Http;

struct SAFE_URL_COMPONENTS
{
	INTERNET_SCHEME scheme = INTERNET_SCHEME_DEFAULT;
	std::tstring hostName;
	INTERNET_PORT port = 0;
	std::tstring urlPath;
};

static SAFE_URL_COMPONENTS SafeInternetCrackUrl(const std::tstring& url)
{
	URL_COMPONENTS components = {};
	components.dwStructSize = sizeof(URL_COMPONENTS);
	components.dwUrlPathLength = 1;
	components.dwHostNameLength = 1;

	BOOL crackResult = InternetCrackUrl(url.c_str(), 0, 0, &components);
	assert(crackResult == TRUE);
	if(crackResult == FALSE)
	{
		return SAFE_URL_COMPONENTS();
	}

	SAFE_URL_COMPONENTS safeComponents = {};
	safeComponents.hostName = std::tstring(components.lpszHostName, components.dwHostNameLength);
	safeComponents.port = components.nPort;
	safeComponents.scheme = components.nScheme;
	safeComponents.urlPath = std::tstring(components.lpszUrlPath, components.dwUrlPathLength);
	return safeComponents;
}

RequestResult CWin32HttpClient::SendRequest()
{
	auto inet = Framework::Win32::CInternetHandle(InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0));
	if(inet.IsEmpty())
	{
		throw std::runtime_error("Failed to open internet.");
	}

	auto components = SafeInternetCrackUrl(string_cast<std::tstring>(m_url));
	auto connect = Framework::Win32::CInternetHandle(InternetConnect(inet, components.hostName.c_str(), components.port, nullptr, nullptr, INTERNET_SERVICE_HTTP, 0, 0));
	if(connect.IsEmpty())
	{
		throw std::runtime_error("Failed to connect to host.");
	}

	auto verbString = (m_verb == HTTP_VERB::GET) ? _T("GET") : _T("POST");
	auto request = Framework::Win32::CInternetHandle(HttpOpenRequest(connect, verbString, components.urlPath.c_str(), nullptr, nullptr, nullptr, 0, 0));
	assert(!request.IsEmpty());

	auto optionalData = reinterpret_cast<LPVOID>(const_cast<char*>(m_requestBody.c_str()));
	BOOL sendRequestResult = HttpSendRequest(request, nullptr, 0, optionalData, m_requestBody.size());
	if(sendRequestResult == FALSE)
	{
		throw std::runtime_error("Failed to send request.");
	}

	DWORD statusCode = 0;
	DWORD statusCodeSize = sizeof(DWORD);
	BOOL queryInfoResult = HttpQueryInfo(request, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &statusCode, &statusCodeSize, nullptr);
	assert(queryInfoResult == TRUE);

	RequestResult result;
	result.statusCode = static_cast<HTTP_STATUS_CODE>(statusCode);
	while(1)
	{
		uint8 buff[0x10000];
		DWORD read = 0;
		BOOL readResult = InternetReadFile(request, buff, sizeof(buff), &read);
		if(readResult == FALSE)
		{
			throw std::runtime_error("Failed to read contents.");
		}
		if(read == 0)
		{
			break;
		}
		result.data.Write(buff, read);
	}
	result.data.Seek(0, Framework::STREAM_SEEK_SET);
	return result;
}
