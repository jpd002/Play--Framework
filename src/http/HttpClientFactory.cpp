#include "http/HttpClientFactory.h"
#include "http/Win32HttpClient.h"

using namespace Framework::Http;

std::unique_ptr<CHttpClient> Framework::Http::CreateHttpClient()
{
	return std::make_unique<CWin32HttpClient>();
}
