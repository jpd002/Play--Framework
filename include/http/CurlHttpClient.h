#pragma once

#include <string>
#include "HttpClient.h"

namespace Framework
{
	namespace Http
	{
		class CCurlHttpClient : public CHttpClient
		{
		public:
			RequestResult SendRequest() override;
		};
	}
}
