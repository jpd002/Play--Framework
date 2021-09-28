#include "http/AndroidHttpClient.h"
#include <cassert>
#include "http/java_net_URL.h"
#include "http/java_net_HttpURLConnection.h"
#include "http/java_io_InputStream.h"
#include "http/java_io_OutputStream.h"
#include "android/JavaVM.h"

using namespace Framework;
using namespace Framework::Http;

struct ScopedDisconnecter
{
public:
	ScopedDisconnecter(java::net::HttpURLConnection& connection)
		: m_connection(connection)
	{
		
	}
	
	~ScopedDisconnecter()
	{
		m_connection.disconnect();
	}
	
private:
	java::net::HttpURLConnection& m_connection;
};

RequestResult CAndroidHttpClient::SendRequest()
{
	auto env = CJavaVM::GetEnv();
	
	auto url = java::net::URL(env->NewStringUTF(m_url.c_str()));
	auto connection = CJavaObject::CastTo<java::net::HttpURLConnection>(url.openConnection());

	{
		ScopedDisconnecter disconnecter(connection);

		const char* verbString = nullptr;
		switch(m_verb)
		{
		default:
			assert(false);
			[[fallthrough]];
		case HTTP_VERB::GET:
			verbString = "GET";
			break;
		case HTTP_VERB::POST:
			verbString = "POST";
			break;
		case HTTP_VERB::HEAD:
			verbString = "HEAD";
			break;
		}
		connection.setRequestMethod(env->NewStringUTF(verbString));

		for(const auto& header : m_headers)
		{
			jstring headerKey = env->NewStringUTF(header.first.c_str());
			jstring headerValue = env->NewStringUTF(header.second.c_str());
			connection.setRequestProperty(headerKey, headerValue);
			env->DeleteLocalRef(headerKey);
			env->DeleteLocalRef(headerValue);
		}
		
		if(m_verb == HTTP_VERB::POST)
		{
			auto outputStream = CJavaObject::CastTo<java::io::OutputStream>(connection.getOutputStream());
			outputStream.write(reinterpret_cast<const jbyte*>(m_requestBody.data()), m_requestBody.size());
			outputStream.close();
		}
		
		RequestResult result;
		result.statusCode = static_cast<HTTP_STATUS_CODE>(connection.getResponseCode());

		for(uint32 headerIdx = 0; ; headerIdx++)
		{
			jstring headerKey = connection.getHeaderFieldKey(headerIdx);
			jstring headerValue = connection.getHeaderField(headerIdx);
			if(!headerKey || !headerValue) break;
			const char* headerKeyChars = env->GetStringUTFChars(headerKey, 0);
			const char* headerValueChars = env->GetStringUTFChars(headerValue, 0);
			result.headers.insert(std::make_pair(headerKeyChars, headerValueChars));
			env->ReleaseStringUTFChars(headerKey, headerKeyChars);
			env->ReleaseStringUTFChars(headerValue, headerValueChars);
		}

		auto inputStream = 
			[&] ()
			{
				uint32 resultClass = static_cast<uint32>(result.statusCode) / 100;
				switch(resultClass)
				{
				case 4:
				case 5:
					return CJavaObject::CastTo<java::io::InputStream>(connection.getErrorStream());
				default:
					return CJavaObject::CastTo<java::io::InputStream>(connection.getInputStream());
				}
			}();

		static const int bufferSize = 0x10000;
		std::vector<jbyte> buffer;
		buffer.resize(bufferSize);

		while(1)
		{
			auto readResult = inputStream.read(buffer);
			if(readResult == -1)
			{
				break;
			}
			result.data.Write(buffer.data(), readResult);
		}
		result.data.Seek(0, Framework::STREAM_SEEK_SET);
		
		return result;
	}
}
