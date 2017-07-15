#pragma once

#include <memory>
#include "http/HttpClient.h"

namespace Framework
{
	namespace Http
	{
		std::unique_ptr<CHttpClient> CreateHttpClient();
	}
}
