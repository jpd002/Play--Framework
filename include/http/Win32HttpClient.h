#pragma once

#include <string>
#include "HttpClient.h"

namespace Framework
{
	namespace Http
	{
		class CWin32HttpClient : public CHttpClient
		{
		public:
			RequestResult SendRequest() override;
		};
	}
}
