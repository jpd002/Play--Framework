#pragma once

#include <string>
#include <vector>
#include "http/HttpClient.h"

struct CAmazonCredentials
{
	std::string accessKeyId;
	std::string secretAccessKey;
	std::string sessionToken;
	
	bool IsValid() const
	{
		return !accessKeyId.empty() && !secretAccessKey.empty();
	}
};

class CAmazonClient
{
public:
	CAmazonClient(std::string, CAmazonCredentials, std::string);

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
	CAmazonCredentials m_credentials;
	std::string m_region;
};
