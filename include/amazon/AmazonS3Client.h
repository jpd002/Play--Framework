#pragma once

#include <string>
#include <vector>
#include "amazon/AmazonClient.h"

struct GetBucketLocationRequest
{
	std::string bucket;
};

struct GetBucketLocationResult
{
	std::string locationConstraint;
};

struct GetObjectRequest
{
	std::string bucket;
	std::string key;
	std::pair<uint64, uint64> range;
};

struct GetObjectResult
{
	std::vector<uint8> data;
};

struct HeadObjectRequest
{
	std::string bucket;
	std::string key;
};

struct HeadObjectResult
{
	uint64 contentLength = 0;
	std::string etag;
};

struct Object
{
	std::string key;
};

struct ListObjectsResult
{
	std::vector<Object> objects;
};

struct PutObjectRequest
{
	std::string key;
	std::string bucket;
	std::vector<uint8> data;
};

class CAmazonS3Client : public CAmazonClient
{
public:
	CAmazonS3Client(CAmazonCredentials, std::string = "us-east-1");

	GetBucketLocationResult GetBucketLocation(const GetBucketLocationRequest&);
	GetObjectResult GetObject(const GetObjectRequest&);
	HeadObjectResult HeadObject(const HeadObjectRequest&);
	ListObjectsResult ListObjects(std::string);
	void PutObject(const PutObjectRequest&);
};
