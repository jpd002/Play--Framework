#include <cassert>
#include <vector>
#include "http/Win32HttpClient.h"
#include "win32/InternetHandle.h"
#include "tcharx.h"
#include "string_cast.h"
#include "PtrStream.h"

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

	const TCHAR* verbString = nullptr;
	switch(m_verb)
	{
	case HTTP_VERB::HEAD:
		verbString = _T("HEAD");
		break;
	case HTTP_VERB::GET:
		verbString = _T("GET");
		break;
	case HTTP_VERB::POST:
		verbString = _T("POST");
		break;
	case HTTP_VERB::PUT:
		verbString = _T("PUT");
		break;
	default:
		assert(false);
		break;
	}

	DWORD openRequestFlags = (components.scheme == INTERNET_SCHEME_HTTPS) ? INTERNET_FLAG_SECURE : 0;
	auto request = Framework::Win32::CInternetHandle(HttpOpenRequest(connect, verbString, components.urlPath.c_str(), nullptr, nullptr, nullptr, openRequestFlags, 0));
	assert(!request.IsEmpty());

	//Add custom request headers
	{
		std::tstring headers;
		for(auto headerPair : m_headers)
		{
			headers += string_cast<std::tstring>(headerPair.first) + _T(": ") + string_cast<std::tstring>(headerPair.second);
			headers += _T("\r\n");
		}

		if(!headers.empty())
		{
			BOOL addRequestHeadersResult = HttpAddRequestHeaders(request, headers.c_str(), -1, HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);
			assert(addRequestHeadersResult);
		}
	}

	auto optionalData = reinterpret_cast<LPVOID>(m_requestBody.data());
	BOOL sendRequestResult = HttpSendRequest(request, nullptr, 0, optionalData, m_requestBody.size());
	if(sendRequestResult == FALSE)
	{
		throw std::runtime_error("Failed to send request.");
	}

	//Get HTTP status code
	DWORD statusCode = 0;
	{
		DWORD statusCodeSize = sizeof(DWORD);
		BOOL queryInfoResult = HttpQueryInfo(request, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &statusCode, &statusCodeSize, nullptr);
		assert(queryInfoResult == TRUE);
	}

	RequestResult result;
	result.statusCode = static_cast<HTTP_STATUS_CODE>(statusCode);

	//Get response headers
	{
		DWORD headersSize = 0;
		BOOL queryInfoResult = HttpQueryInfo(request, HTTP_QUERY_RAW_HEADERS_CRLF, nullptr, &headersSize, NULL);
		if(headersSize != 0)
		{
			std::vector<char> headersBytes;
			headersBytes.resize(headersSize);
			queryInfoResult = HttpQueryInfo(request, HTTP_QUERY_RAW_HEADERS_CRLF, headersBytes.data(), &headersSize, NULL);
			assert(queryInfoResult == TRUE);
			auto headers = string_cast<std::string>(reinterpret_cast<const TCHAR*>(headersBytes.data()));
			Framework::CPtrStream headerStream(headers.data(), headers.size());
			result.headers = ReadHeaderMap(headerStream);
		}
	}

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
