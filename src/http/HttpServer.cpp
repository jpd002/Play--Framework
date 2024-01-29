#include "http/HttpServer.h"
#include <cassert>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "StringUtils.h"
#include "SocketStream.h"

using namespace Framework;

CHttpServer::CHttpServer(uint16 port, const RequestHandler& requestHandler)
    : m_requestHandler(requestHandler)
{
	Start(port);
}

CHttpServer::~CHttpServer()
{
	if(m_serverSock != -1)
	{
		close(m_serverSock);
	}
	m_serverThread.join();
}

void CHttpServer::Start(uint16 port)
{
	assert(m_serverSock == -1);
	m_serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in sa = {};
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	int result = bind(m_serverSock, reinterpret_cast<sockaddr*>(&sa), sizeof(sockaddr_in));
	assert(result == 0);
	
	result = listen(m_serverSock, SOMAXCONN);
	assert(result == 0);
	
	m_serverThread = std::thread([this](){ ServerThreadProc(); });
}

void CHttpServer::ServerThreadProc()
{
	while(1)
	{
		sockaddr_in sa = {};
		socklen_t addrLength = sizeof(sockaddr_in);
		int clientSocket = accept(m_serverSock, reinterpret_cast<sockaddr*>(&sa), &addrLength);
		if(clientSocket == -1)
		{
			break;
		}
		ProcessRequest(clientSocket);
	}
}

void CHttpServer::ProcessRequest(int clientSocket)
{
	try
	{
		auto clientStream = CSocketStream(clientSocket);
		auto line = clientStream.ReadLine();
		auto parts = StringUtils::Split(line);
		
		if(parts.size() != 3)
		{
			throw std::runtime_error("Bad request.");
		}
		
		Request request;

		//Read headers
		while(1)
		{
			auto line = clientStream.ReadLine();
			if(line.empty()) break;
			auto delimit = line.find(':');
			if(delimit == std::string::npos)
			{
				//Invalid header
				continue;
			}
			auto headerName = StringUtils::TrimEnd(std::string(line.begin(), line.begin() + delimit));
			auto headerValue = StringUtils::TrimStart(std::string(line.begin() + delimit + 1, line.end()));
			request.headers.insert(std::make_pair(headerName, headerValue));
		}
		
		auto contentLenghtHeaderIterator = request.headers.find("Content-Length");
		if(contentLenghtHeaderIterator != std::end(request.headers))
		{
			uint64 contentLength = atoll(contentLenghtHeaderIterator->second.c_str());
			request.body.resize(contentLength);
			while(contentLength != 0)
			{
				uint64 readAmount = clientStream.Read(request.body.data(), contentLength);
				contentLength -= readAmount;
			}
		}
		
		request.url = parts[1];
		m_requestHandler(request);

		std::string response;
		response += "HTTP/1.1 200 OK\r\n";
		//TODO: Append some body here
		response += "\r\n";
		
		clientStream.Write(response.c_str(), response.size());
	}
	catch(...)
	{
		//Abort
	}
}
