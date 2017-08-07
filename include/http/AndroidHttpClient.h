#pragma once

#include <string>
#include "HttpClient.h"

namespace Framework
{
	namespace Http
	{
		class CAndroidHttpClient : public CHttpClient
		{
		public:
			RequestResult SendRequest() override;
		};
	}
}
