#pragma once

#include <string>
#include "MemStream.h"

namespace Framework
{
	namespace Http
	{
		enum class HTTP_STATUS_CODE
		{
			OK = 200,
			NOT_FOUND = 404
		};

		enum class HTTP_VERB
		{
			GET,
			POST
		};

		struct RequestResult
		{
			HTTP_STATUS_CODE      statusCode = HTTP_STATUS_CODE::OK;
			Framework::CMemStream data;
		};

		class CHttpClient
		{
		public:
			virtual ~CHttpClient() = default;

			static std::string UrlEncode(const std::string&);

			void SetUrl(std::string);
			void SetVerb(HTTP_VERB);
			void SetRequestBody(std::string);
			virtual RequestResult SendRequest() = 0;

		protected:
			std::string m_url;
			HTTP_VERB m_verb = HTTP_VERB::GET;
			std::string m_requestBody;
		};
	}
}
