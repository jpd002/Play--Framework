#include "http/HttpServer.h"
#include <cassert>
#include <stdexcept>
#include <cstdarg>
#include "StringUtils.h"
#include "SocketStream.h"
#include "StdStreamUtils.h"

using namespace Framework;

CHttpServer::CHttpServer(uint16 port, const RequestHandler& requestHandler, const fs::path& logPath)
    : m_requestHandler(requestHandler)
{
	if(!logPath.empty())
	{
		try
		{
			m_logStream = std::make_unique<CStdStream>(logPath.native().c_str(), GetAppendStdStreamMode<fs::path::string_type>());
		}
		catch(...)
		{
		}
	}
	InitializeSocketSupport();
	Start(port);
}

CHttpServer::~CHttpServer()
{
	if(m_serverSock != INVALID_SOCKET)
	{
#ifdef _WIN32
		closesocket(m_serverSock);
#else
		close(m_serverSock);
#endif
	}
	m_serverThread.join();
}

void CHttpServer::Start(uint16 port)
{
	assert(m_serverSock == INVALID_SOCKET);
	m_serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	assert(m_serverSock != INVALID_SOCKET);
	if(m_serverSock == INVALID_SOCKET)
	{
		Log("Failed to create socket (error: %d).\r\n", errno);
	}

	sockaddr_in sa = {};
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	int result = bind(m_serverSock, reinterpret_cast<sockaddr*>(&sa), sizeof(sockaddr_in));
	assert(result == 0);
	if(result != 0)
	{
		Log("Failed to bind socket to port %d (error: %d).\r\n", port, errno);
	}

	result = listen(m_serverSock, SOMAXCONN);
	assert(result == 0);
	if(result != 0)
	{
		Log("Failed to listen (error: %d).\r\n", errno);
	}
	else
	{
		Log("Server ready and listening on port %d.\r\n", port);
	}

	m_serverThread = std::thread([this]() { ServerThreadProc(); });
}

void CHttpServer::ServerThreadProc()
{
	while(1)
	{
		sockaddr_in sa = {};
		socklen_t addrLength = sizeof(sockaddr_in);
		SOCKET clientSocket = accept(m_serverSock, reinterpret_cast<sockaddr*>(&sa), &addrLength);
		if(clientSocket == INVALID_SOCKET)
		{
			Log("Failed to accept (error: %d). Terminating server.\r\n", errno);
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
		Log("Processing request %s '%s'.\r\n", parts[0].c_str(), request.url.c_str());

		m_requestHandler(request);

		std::string response;
		response += "HTTP/1.1 200 OK\r\n";
		//TODO: Append some body here
		response += "\r\n";

		clientStream.Write(response.c_str(), response.size());
	}
	catch(...)
	{
		Log("Failed to process request from client.\r\n");
	}
}

void CHttpServer::Log(const char* format, ...)
{
	if(!m_logStream) return;
	va_list args;
	va_start(args, format);
	vfprintf(*m_logStream, format, args);
	va_end(args);
	m_logStream->Flush();
}
