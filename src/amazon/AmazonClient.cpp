#include "amazon/AmazonClient.h"
#include "http/HttpClientFactory.h"
#include <algorithm>
#include <cassert>
#include <ctime>
#include <stdexcept>
#include "HashUtils.h"
#include "string_format.h"

static std::string hashToString(const std::array<uint8, 0x20> hash)
{
	std::string result;
	for (uint32 i = 0; i < 0x20; i += 8)
	{
		result += string_format("%02x%02x%02x%02x%02x%02x%02x%02x",
			hash[i + 0], hash[i + 1], hash[i + 2], hash[i + 3],
			hash[i + 4], hash[i + 5], hash[i + 6], hash[i + 7]);
	}
	return result;
}

static std::string buildSignedHeadersParam(const Framework::Http::HeaderMap& headers)
{
	std::string result;
	for(auto headerPairIterator = headers.begin();
		headerPairIterator != headers.end(); headerPairIterator++)
	{
		bool isEnd =
			[&]() {
			auto headerPairIteratorCopy = headerPairIterator;
			headerPairIteratorCopy++;
			return headerPairIteratorCopy == std::end(headers);
		}();
		auto headerKey = headerPairIterator->first;
		std::transform(headerKey.begin(), headerKey.end(), headerKey.begin(), &::tolower);
		result += headerKey;
		if(!isEnd)
		{
			result += ";";
		}
	}
	return result;
}

static std::string buildCanonicalRequest(Framework::Http::HTTP_VERB method, const std::string& uri, const std::string& query, const std::string& hashedPayload, const Framework::Http::HeaderMap& headers)
{
	std::string result;
	switch (method)
	{
	case Framework::Http::HTTP_VERB::DELETE:
		result += "DELETE";
		break;
	case Framework::Http::HTTP_VERB::HEAD:
		result += "HEAD";
		break;
	case Framework::Http::HTTP_VERB::GET:
		result += "GET";
		break;
	case Framework::Http::HTTP_VERB::PUT:
		result += "PUT";
		break;
	case Framework::Http::HTTP_VERB::POST:
		result += "POST";
		break;
	default:
		assert(false);
		break;
	}
	result += "\n";

	//CanonicalURI
	result += uri;
	result += "\n";

	//CanonicalQueryString
	result += query;
	result += "\n";

	//CanonicalHeaders
	for (const auto& headerPair : headers)
	{
		auto headerKey = headerPair.first;
		auto headerValue = headerPair.second;
		std::transform(headerKey.begin(), headerKey.end(), headerKey.begin(), &::tolower);
		result += headerKey;
		result += ":";
		result += headerValue;
		result += "\n";
	}
	result += "\n";

	//SignedHeaders
	result += buildSignedHeadersParam(headers);
	result += "\n";

	//HashedPayload
	result += hashedPayload;

	return result;
}

static std::string buildStringToSign(const std::string& timestamp, const std::string& scope, const std::string& canonicalRequest)
{
	auto result = std::string("AWS4-HMAC-SHA256\n");
	result += timestamp;
	result += "\n";

	result += scope;
	result += "\n";

	auto canonicalRequestHash = hashToString(Framework::HashUtils::ComputeSha256(canonicalRequest.data(), canonicalRequest.size()));
	result += canonicalRequestHash;

	return result;
}

static std::array<uint8, 0x20> buildSigningKey(const std::string& secretAccessKey, const std::string& date, const std::string& region, const std::string& service, const std::string& requestType)
{
	auto signKey = "AWS4" + secretAccessKey;

	auto result = Framework::HashUtils::ComputeHmacSha256(signKey.c_str(), signKey.length(), date.c_str(), date.length());
	result = Framework::HashUtils::ComputeHmacSha256(result.data(), result.size(), region.c_str(), region.length());
	result = Framework::HashUtils::ComputeHmacSha256(result.data(), result.size(), service.c_str(), service.length());
	result = Framework::HashUtils::ComputeHmacSha256(result.data(), result.size(), requestType.c_str(), requestType.length());
	return result;
}

static std::string timeToString(const tm* timeInfo)
{
	static const size_t bufferSize = 0x100;
	char output[bufferSize];
	auto result = strftime(output, bufferSize, "%Y%m%dT%H%M%SZ", timeInfo);
	if (result == 0)
	{
		throw std::runtime_error("Failed to convert time");
	}
	return std::string(output);
}

CAmazonClient::CAmazonClient(std::string service, CAmazonCredentials credentials, std::string region)
    : m_service(std::move(service))
    , m_credentials(std::move(credentials))
    , m_region(std::move(region))
{
}

Framework::Http::RequestResult CAmazonClient::ExecuteRequest(const Request& request)
{
	assert(!m_credentials.accessKeyId.empty());
	assert(!m_credentials.secretAccessKey.empty());
	assert(!request.host.empty());
	assert(!request.urlHost.empty());

	time_t rawTime;
	time(&rawTime);
	auto timeInfo = gmtime(&rawTime);

	auto date = string_format("%04d%02d%02d", timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday);
	auto requestType = std::string("aws4_request");

	auto contentHashString = hashToString(Framework::HashUtils::ComputeSha256(request.content.data(), request.content.size()));

	auto scope = string_format("%s/%s/%s/%s", date.c_str(), m_region.c_str(), m_service.c_str(), requestType.c_str());
	auto timestamp = timeToString(timeInfo);

	Framework::Http::HeaderMap headers;
	headers.insert(std::make_pair("Host", request.host));
	headers.insert(std::make_pair("x-amz-content-sha256", contentHashString));
	headers.insert(std::make_pair("x-amz-date", timestamp));
	if(!m_credentials.sessionToken.empty())
	{
		headers.insert(std::make_pair("x-amz-security-token", m_credentials.sessionToken));
	}
	
	auto canonicalRequest = buildCanonicalRequest(request.method, request.uri, request.query, contentHashString, headers);
#ifdef DEBUG_REQUEST
	printf("canonicalRequest:\n%s\n\n", canonicalRequest.c_str());
#endif

	auto stringToSign = buildStringToSign(timestamp, scope, canonicalRequest);
#ifdef DEBUG_REQUEST
	printf("stringToSign:\n%s\n\n", stringToSign.c_str());
#endif

	auto signedHeaders = buildSignedHeadersParam(headers);
	auto signingKey = buildSigningKey(m_credentials.secretAccessKey, date, m_region, m_service, requestType);
	auto signature = hashToString(Framework::HashUtils::ComputeHmacSha256(signingKey.data(), signingKey.size(), stringToSign.c_str(), stringToSign.length()));

	auto authorizationString = string_format("AWS4-HMAC-SHA256 Credential=%s/%s, SignedHeaders=%s, Signature=%s",
		m_credentials.accessKeyId.c_str(), scope.c_str(), signedHeaders.c_str(), signature.c_str());
	headers.insert(std::make_pair("Authorization", authorizationString));
	headers.insert(request.headers.begin(), request.headers.end());

	auto url = string_format("https://%s%s", request.urlHost.c_str(), request.uri.c_str());
	if (!request.query.empty())
	{
		url += "?";
		url += request.query;
	}

	auto httpClient = Framework::Http::CreateHttpClient();
	httpClient->SetVerb(request.method);
	httpClient->SetUrl(url);
	httpClient->SetHeaders(headers);
	httpClient->SetRequestBody(request.content);
	auto response = httpClient->SendRequest();
#ifdef DEBUG_REQUEST
	auto responseString = std::string(response.data.GetBuffer(), response.data.GetBuffer() + response.data.GetLength());
	printf("%s", responseString.c_str());
#endif
	return response;
}
