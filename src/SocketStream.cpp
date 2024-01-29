#include "SocketStream.h"
#include <stdexcept>
#include <mutex>
#include <cassert>

using namespace Framework;

void Framework::InitializeSocketSupport()
{
	static std::once_flag initFlag;
	std::call_once(initFlag,
	               []() {
#ifdef _WIN32
		               WSADATA w = {};
		               int result = WSAStartup(MAKEWORD(1, 1), &w);
		               assert(result == 0);
#endif
	               });
}

CSocketRefStream::CSocketRefStream(SOCKET fd)
    : m_fd(fd)
{
}

uint64 CSocketRefStream::Read(void* buffer, uint64 size)
{
	auto result = recv(m_fd, reinterpret_cast<char*>(buffer), size, 0);
	if(result < 0)
	{
		throw std::runtime_error("Socket read failed.");
	}
	if(result == 0)
	{
		m_isEof = true;
	}
	return result;
}

uint64 CSocketRefStream::Write(const void* buffer, uint64 size)
{
	auto result = send(m_fd, reinterpret_cast<const char*>(buffer), size, 0);
	if(result < 0)
	{
		throw std::runtime_error("Socket write failed.");
	}
	return result;
}

uint64 CSocketRefStream::Tell()
{
	throw std::runtime_error("Operation not supported.");
}

void CSocketRefStream::Seek(int64, Framework::STREAM_SEEK_DIRECTION)
{
	throw std::runtime_error("Operation not supported.");
}

bool CSocketRefStream::IsEOF()
{
	return m_isEof;
}

CSocketStream::CSocketStream(SOCKET fd)
    : CSocketRefStream(fd)
{
}

CSocketStream::~CSocketStream()
{
#ifdef _WIN32
	closesocket(m_fd);
#else
	close(m_fd);
#endif
}
