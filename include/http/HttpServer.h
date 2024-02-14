#pragma once

#include <thread>
#include <functional>
#include <map>
#include <vector>
#include <string>
#include "Types.h"
#include "SocketDef.h"

namespace Framework
{
	class CHttpServer
	{
	public:
		struct Request
		{
			std::string url;
			std::map<std::string, std::string> headers;
			std::vector<uint8> body;
		};

		using RequestHandler = std::function<void(const Request&)>;

		CHttpServer(uint16, const RequestHandler&);
		CHttpServer(CHttpServer&) = delete;
		~CHttpServer();

		CHttpServer& operator=(const CHttpServer&) = delete;

	private:
		void Start(uint16);
		void ServerThreadProc();
		void ProcessRequest(int);

		RequestHandler m_requestHandler;
		SOCKET m_serverSock = INVALID_SOCKET;
		std::thread m_serverThread;
	};
}
