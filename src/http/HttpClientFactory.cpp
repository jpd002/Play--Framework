#include "http/HttpClientFactory.h"

#ifdef _WIN32
#include "http/Win32HttpClient.h"
#elif defined(ANDROID)
#include "http/AndroidHttpClient.h"
#elif defined(__APPLE__)
#include "http/AppleHttpClient.h"
#endif

using namespace Framework::Http;

std::unique_ptr<CHttpClient> Framework::Http::CreateHttpClient()
{
#ifdef _WIN32
	return std::make_unique<CWin32HttpClient>();
#elif defined(ANDROID)
	return std::make_unique<CAndroidHttpClient>();
#elif defined(__APPLE__)
	return std::make_unique<CAppleHttpClient>();
#else
	throw std::runtime_error("Platform not supported");
#endif
}
