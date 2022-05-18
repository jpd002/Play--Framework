#include "amazon/AmazonS3Client.h"
#include <stdexcept>
#include <memory>
#include <cassert>
#include "string_format.h"
#include "xml/Parser.h"
#include "Url.h"

CAmazonS3Client::CAmazonS3Client(CAmazonConfigs configs, std::string region)
    : CAmazonClient("s3", std::move(configs), std::move(region))
{
}

CAmazonClient::Request CAmazonS3Client::CreateRequest(Framework::Http::HTTP_VERB method, std::string bucket, std::string key)
{
	Request rq;
	rq.method = method;

	// Path‐style bucket access
	if(m_configs.m_provider == CAmazonConfigs::S3PROVIDER::CF_R2)
	{
		auto endpoint = "r2.cloudflarestorage.com";
		rq.uri = string_format("/%s", bucket.c_str());
		if(!key.empty())
		{
			rq.uri = string_format("%s/%s", rq.uri.c_str(), key.c_str());
		}
		rq.host = string_format("%s.%s", m_configs.accountKeyId.c_str(), endpoint);
		rq.urlHost = rq.host;
		return rq;
	}

	// Virtual hosted‐style bucket access
	assert(m_configs.m_provider == CAmazonConfigs::S3PROVIDER::AWS_S3);

	rq.uri = "/";
	if(!key.empty())
	{
		rq.uri = string_format("/%s", key.c_str());
	}

	std::string endpoint = "amazonaws.com";
	if(m_region.empty())
	{
		rq.host = string_format("%s.s3.%s", bucket.c_str(), endpoint.c_str());
		rq.urlHost = string_format("s3.%s", endpoint.c_str());
	}
	else
	{
		rq.host = string_format("%s.s3-%s.%s", bucket.c_str(), m_region.c_str(), endpoint.c_str());
		rq.urlHost = rq.host;
	}
	return rq;
}

GetBucketLocationResult CAmazonS3Client::GetBucketLocation(const GetBucketLocationRequest& request)
{
	GetBucketLocationResult result;
	// CF R2 does not support regions, thus doesnt support location call,
	// but it seems region is needed for signature verification
	if(m_configs.m_provider == CAmazonConfigs::CF_R2)
	{
		result.locationConstraint = m_region;
		return result;
	}

	if(request.bucket.empty())
	{
		throw new std::runtime_error("Bucket name must be provided.");
	}

	Request rq = CreateRequest(Framework::Http::HTTP_VERB::GET, request.bucket);
	//We add a bucket parameter even if the S3 API doesn't use it to prevent caching
	rq.query = string_format("bucket=%s&location=", request.bucket.c_str());

	auto response = ExecuteRequest(rq);
	if(response.statusCode != Framework::Http::HTTP_STATUS_CODE::OK)
	{
		throw std::runtime_error("Failed to get bucket location.");
	}

	auto documentNode = std::unique_ptr<Framework::Xml::CNode>(Framework::Xml::CParser::ParseDocument(response.data));
	auto locationConstraintNode = documentNode->Select("LocationConstraint");
	if(locationConstraintNode)
	{
		auto locationConstraint = locationConstraintNode->GetInnerText();
		result.locationConstraint = locationConstraint ? locationConstraint : "";
	}

	return result;
}

GetObjectResult CAmazonS3Client::GetObject(const GetObjectRequest& request)
{
	Request rq = CreateRequest(Framework::Http::HTTP_VERB::GET, request.bucket, Framework::UrlEncode(request.key));

	if(request.range.first != request.range.second)
	{
		auto rangeHeader = string_format("bytes=%llu-%llu", request.range.first, request.range.second);
		rq.headers.insert(std::make_pair("Range", rangeHeader));
	}

	auto response = ExecuteRequest(rq);
	if(
	    (response.statusCode != Framework::Http::HTTP_STATUS_CODE::OK) &&
	    (response.statusCode != Framework::Http::HTTP_STATUS_CODE::PARTIAL_CONTENT))
	{
		throw std::runtime_error("Failed to get object.");
	}

	GetObjectResult result;
	uint32 dataLength = response.data.GetLength();
	result.data.resize(dataLength);
	response.data.Read(result.data.data(), dataLength);
	return result;
}

HeadObjectResult CAmazonS3Client::HeadObject(const HeadObjectRequest& request)
{
	Request rq = CreateRequest(Framework::Http::HTTP_VERB::HEAD, request.bucket, Framework::UrlEncode(request.key));

	auto response = ExecuteRequest(rq);
	if(response.statusCode != Framework::Http::HTTP_STATUS_CODE::OK)
	{
		throw std::runtime_error("Failed to head object.");
	}

	HeadObjectResult result;

	auto contentLengthIterator = response.headers.find("Content-Length");
	if(contentLengthIterator != std::end(response.headers))
	{
		result.contentLength = atoll(contentLengthIterator->second.c_str());
	}

	auto etagIterator = response.headers.find("ETag");
	if(etagIterator == std::end(response.headers)) etagIterator = response.headers.find("Etag");
	if(etagIterator != std::end(response.headers))
	{
		result.etag = etagIterator->second;
	}

	return result;
}

ListObjectsResult CAmazonS3Client::ListObjects(std::string bucket)
{
	Request rq = CreateRequest(Framework::Http::HTTP_VERB::GET, bucket);

	auto response = ExecuteRequest(rq);
	if(response.statusCode != Framework::Http::HTTP_STATUS_CODE::OK)
	{
		throw std::runtime_error("Failed to list objects");
	}

	ListObjectsResult result;

	auto documentNode = std::unique_ptr<Framework::Xml::CNode>(Framework::Xml::CParser::ParseDocument(response.data));
	auto contentsNodes = documentNode->SelectNodes("ListBucketResult/Contents");
	for(const auto& contentsNode : contentsNodes)
	{
		Object object;
		if(auto keyNode = contentsNode->Select("Key"))
		{
			object.key = keyNode->GetInnerText();
		}
		result.objects.push_back(object);
	}

	return result;
}

void CAmazonS3Client::PutObject(const PutObjectRequest& request)
{
	Request rq = CreateRequest(Framework::Http::HTTP_VERB::PUT, Framework::UrlEncode(request.key));
	rq.content = request.data;
	
	auto response = ExecuteRequest(rq);
	if(response.statusCode != Framework::Http::HTTP_STATUS_CODE::OK)
	{
		throw std::runtime_error("Failed to put object.");
	}
}
