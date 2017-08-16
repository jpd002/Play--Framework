#pragma once

#include <string>
#include "HttpClient.h"

namespace Framework
{
	namespace Http
	{
		class CAppleHttpClient : public CHttpClient
		{
		public:
			RequestResult SendRequest() override;
		};
	}
}
