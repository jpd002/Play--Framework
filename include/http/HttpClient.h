#pragma once

#include <string>
#include <map>
#include "MemStream.h"

namespace Framework
{
	namespace Http
	{
		enum class HTTP_STATUS_CODE
		{
			OK = 200,
			PARTIAL_CONTENT = 206,
			TEMPORARY_REDIRECT = 307,
			BAD_REQUEST = 400,
			FORBIDDEN = 403,
			NOT_FOUND = 404,
			NOT_IMPLEMENTED = 501
		};

		enum class HTTP_VERB
		{
			DELETE,
			HEAD,
			GET,
			POST,
			PUT
		};

		typedef std::map<std::string, std::string> HeaderMap;

		struct RequestResult
		{
			HTTP_STATUS_CODE      statusCode = HTTP_STATUS_CODE::OK;
			HeaderMap             headers;
			Framework::CMemStream data;
		};

		class CHttpClient
		{
		public:
			virtual ~CHttpClient() = default;

			static std::string UrlEncode(const std::string&);

			void SetUrl(std::string);
			void SetVerb(HTTP_VERB);
			void SetHeaders(HeaderMap);
			void SetRequestBody(std::string);
			virtual RequestResult SendRequest() = 0;

		protected:
			static HeaderMap ReadHeaderMap(Framework::CStream&);

			std::string m_url;
			HTTP_VERB m_verb = HTTP_VERB::GET;
			HeaderMap m_headers;
			std::string m_requestBody;
		};
	}
}
