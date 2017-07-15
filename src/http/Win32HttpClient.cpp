#include <cassert>
#include "http/Win32HttpClient.h"
#include "win32/InternetHandle.h"
#include "tcharx.h"
#include "string_cast.h"

using namespace Framework;
using namespace Framework::Http;

RequestResult CWin32HttpClient::SendRequest()
{
	auto inet = Framework::Win32::CInternetHandle(InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0));
	auto inetUrl = Framework::Win32::CInternetHandle(InternetOpenUrl(inet, string_cast<std::tstring>(m_url).c_str(), nullptr, 0, 0, NULL));
	if(inetUrl.IsEmpty())
	{
		throw std::runtime_error("Failed to open url.");
	}

	DWORD statusCode = 0;
	DWORD statusCodeSize = sizeof(DWORD);
	BOOL queryInfoResult = HttpQueryInfo(inetUrl, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &statusCode, &statusCodeSize, nullptr);
	assert(queryInfoResult == TRUE);

	RequestResult result;
	result.statusCode = static_cast<HTTP_STATUS_CODE>(statusCode);
	while(1)
	{
		uint8 buff[0x10000];
		DWORD read = 0;
		BOOL readResult = InternetReadFile(inetUrl, buff, sizeof(buff), &read);
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
