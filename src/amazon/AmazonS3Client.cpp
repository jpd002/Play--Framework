#include "amazon/AmazonS3Client.h"
#include <stdexcept>
#include <memory>
#include "string_format.h"
#include "xml/Parser.h"

#define S3_HOSTNAME "s3.amazonaws.com"

CAmazonS3Client::CAmazonS3Client(CAmazonCredentials credentials, std::string region)
    : CAmazonClient("s3", std::move(credentials), std::move(region))
{
}

GetBucketLocationResult CAmazonS3Client::GetBucketLocation(const GetBucketLocationRequest& request)
{
	if(request.bucket.empty())
	{
		throw new std::runtime_error("Bucket name must be provided.");
	}

	Request rq;
	rq.method = Framework::Http::HTTP_VERB::GET;
	rq.host = string_format("%s." S3_HOSTNAME, request.bucket.c_str());
	rq.urlHost = S3_HOSTNAME;
	rq.uri = "/";
	//We add a bucket parameter even if the S3 API doesn't use it to prevent caching
	rq.query = string_format("bucket=%s&location=", request.bucket.c_str());

	auto response = ExecuteRequest(rq);
	if(response.statusCode != Framework::Http::HTTP_STATUS_CODE::OK)
	{
		throw std::runtime_error("Failed to get bucket location.");
	}

	GetBucketLocationResult result;

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
	Request rq;
	rq.method = Framework::Http::HTTP_VERB::GET;
	rq.uri = "/" + Framework::Http::CHttpClient::UrlEncode(request.key);
	rq.host = string_format("%s.s3-%s.amazonaws.com", request.bucket.c_str(), m_region.c_str());
	rq.urlHost = rq.host;

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
	Request rq;
	rq.method = Framework::Http::HTTP_VERB::HEAD;
	rq.uri = "/" + Framework::Http::CHttpClient::UrlEncode(request.key);
	rq.host = string_format("%s.s3-%s.amazonaws.com", request.bucket.c_str(), m_region.c_str());
	rq.urlHost = rq.host;

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
	Request rq;
	rq.method = Framework::Http::HTTP_VERB::GET;
	rq.uri = "/";
	rq.host = string_format("%s.s3-%s.amazonaws.com", bucket.c_str(), m_region.c_str());
	rq.urlHost = rq.host;

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
	Request rq;
	rq.method = Framework::Http::HTTP_VERB::PUT;
	rq.uri = "/" + Framework::Http::CHttpClient::UrlEncode(request.key);
	rq.host = string_format("%s.s3-%s.amazonaws.com", request.bucket.c_str(), m_region.c_str());
	rq.urlHost = rq.host;
	rq.content = request.data;
	
	auto response = ExecuteRequest(rq);
	if(response.statusCode != Framework::Http::HTTP_STATUS_CODE::OK)
	{
		throw std::runtime_error("Failed to put object.");
	}
}
