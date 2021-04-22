#include <cassert>
#include <stdexcept>
#include <curl/curl.h>
#include "http/CurlHttpClient.h"
#include "string_format.h"
#include "PtrStream.h"

using namespace Framework;
using namespace Framework::Http;

static size_t readCallback(char* buffer, size_t size, size_t nmemb, void* userdata)
{
	auto totalSize = size * nmemb;
	auto inputStream = reinterpret_cast<Framework::CPtrStream*>(userdata);
	return inputStream->Read(buffer, totalSize);
}

static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
	auto totalSize = size * nmemb;
	auto outputStream = reinterpret_cast<decltype(Framework::Http::RequestResult::data)*>(userdata);
	outputStream->Write(ptr, totalSize);
	return totalSize;
}

static size_t headerCallback(char* buffer, size_t size, size_t nitems, void* userdata)
{
	auto totalSize = size * nitems;
	auto outputStream = reinterpret_cast<Framework::CMemStream*>(userdata);
	outputStream->Write(buffer, totalSize);
	return totalSize;
}

class CCurlRequest
{
public:
	CCurlRequest()
	{
		m_curl = curl_easy_init();
	}

	~CCurlRequest()
	{
		curl_easy_cleanup(m_curl);
	}

	operator CURL*() const
	{
		return m_curl;
	}

	CCurlRequest(const CCurlRequest&) = delete;
	CCurlRequest& operator =(const CCurlRequest&) = delete;

private:
	CURL* m_curl = nullptr;
};

RequestResult CCurlHttpClient::SendRequest()
{
	RequestResult result;
	CCurlRequest curl;
	assert(curl != nullptr);
	{
		Framework::CPtrStream bodyInputStream(m_requestBody.data(), m_requestBody.size());
		Framework::CMemStream responseHeadersStream;

		curl_easy_setopt(curl, CURLOPT_URL, m_url.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result.data);
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, &readCallback);
		curl_easy_setopt(curl, CURLOPT_READDATA, &bodyInputStream);
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, &headerCallback);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &responseHeadersStream);

		auto caBundlePath = m_globalSettings[GLOBAL_SETTING::CERTIFICATE_AUTHORITY_BUNDLE];
		if(!caBundlePath.empty())
		{
			curl_easy_setopt(curl, CURLOPT_CAINFO, caBundlePath.c_str());
		}

		switch(m_verb)
		{
		case HTTP_VERB::DELETE:
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
			break;
		case HTTP_VERB::HEAD:
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "HEAD");
			break;
		case HTTP_VERB::GET:
			break;
		case HTTP_VERB::PUT:
			curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
			curl_easy_setopt(curl, CURLOPT_INFILESIZE, m_requestBody.size());
			break;
		default:
			throw std::runtime_error("Unsupported HTTP verb.");
		}

		curl_slist* headerList = nullptr;
		if(!m_headers.empty())
		{
			for(const auto& headerPair : m_headers)
			{
				auto headerString = headerPair.first + ": " + headerPair.second;
				headerList = curl_slist_append(headerList, headerString.c_str());
			}
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);
		}

		auto performResult = curl_easy_perform(curl);

		if(headerList)
		{
			curl_slist_free_all(headerList);
			headerList = nullptr;
		}

		if(!(
		    (performResult == CURLE_OK) ||
		    ((performResult == CURLE_PARTIAL_FILE) && (m_verb == Framework::Http::HTTP_VERB::HEAD))
		))
		{
			auto errorMessage = string_format("Failed to execute request: %s.", curl_easy_strerror(performResult));
			throw std::runtime_error(errorMessage);
		}

		long responseCode = 0;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
		result.statusCode = static_cast<Framework::Http::HTTP_STATUS_CODE>(responseCode);
		result.data.Seek(0, Framework::STREAM_SEEK_SET);

		responseHeadersStream.Seek(0, Framework::STREAM_SEEK_SET);
		result.headers = ReadHeaderMap(responseHeadersStream);
	}
	return result;
}
