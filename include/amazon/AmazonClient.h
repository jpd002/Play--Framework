#pragma once

#include <string>
#include <vector>
#include "http/HttpClient.h"

class CAmazonClient
{
public:
	CAmazonClient(std::string, std::string, std::string, std::string);

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
	std::string m_accessKeyId;
	std::string m_secretAccessKey;
	std::string m_region;
};
