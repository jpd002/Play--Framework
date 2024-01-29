#include "SocketStream.h"

#include <unistd.h>
#include <sys/socket.h>

using namespace Framework;

CSocketRefStream::CSocketRefStream(int fd)
    : m_fd(fd)
{
	
}
	
uint64 CSocketRefStream::Read(void* buffer, uint64 size)
{
	auto result = recv(m_fd, buffer, size, 0);
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
	auto result = send(m_fd, buffer, size, 0);
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
	
CSocketStream::CSocketStream(int fd)
    : CSocketRefStream(fd)
{
	
}

CSocketStream::~CSocketStream()
{
	close(m_fd);
}
