#pragma once

#include <string>
#include <vector>
#include "http/HttpClient.h"

struct CAmazonConfigs
{
	enum S3PROVIDER
	{
		AWS_S3 = 0,
		CF_R2 = 1
	};

	std::string accessKeyId;
	std::string secretAccessKey;
	std::string sessionToken;
	std::string accountKeyId;
	S3PROVIDER m_provider;
	
	bool IsValid() const
	{
		return !accessKeyId.empty() && !secretAccessKey.empty();
	}
};

class CAmazonClient
{
public:
	CAmazonClient(std::string, CAmazonConfigs, std::string);

protected:
	struct Request
	{
		Framework::Http::HTTP_VERB method;
		std::string host;
		std::string urlHost;
		std::string uri;
		std::string query;
		Framework::Http::ByteArray content;
		Framework::Http::HeaderMap headers;
	};

	Framework::Http::RequestResult ExecuteRequest(const Request&);

	std::string m_service;
	CAmazonConfigs m_configs;
	std::string m_region;
};
