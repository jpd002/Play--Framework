#pragma once

#include <string>
#include <map>
#include <vector>
#include "MemStream.h"

//Win32 defines DELETE
#ifdef DELETE
#undef DELETE
#endif

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
			UNAUTHORIZED = 401,
			FORBIDDEN = 403,
			NOT_FOUND = 404,
			METHOD_NOT_ALLOWED = 405,
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

		enum class GLOBAL_SETTING
		{
			CERTIFICATE_AUTHORITY_BUNDLE,
		};

		typedef std::vector<uint8> ByteArray;
		typedef std::map<std::string, std::string> HeaderMap;
		typedef std::map<GLOBAL_SETTING, std::string> GlobalSettingMap;

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
			static void SetGlobalSetting(GLOBAL_SETTING, std::string);

			void SetUrl(std::string);
			void SetVerb(HTTP_VERB);
			void SetHeaders(HeaderMap);
			void SetRequestBody(ByteArray);
			void SetRequestBody(std::string);
			virtual RequestResult SendRequest() = 0;

		protected:
			static HeaderMap ReadHeaderMap(Framework::CStream&);

			static GlobalSettingMap m_globalSettings;
			
			std::string m_url;
			HTTP_VERB m_verb = HTTP_VERB::GET;
			HeaderMap m_headers;
			ByteArray m_requestBody;
		};
	}
}
