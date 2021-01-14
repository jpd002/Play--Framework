#include <cassert>
#include <stdexcept>
#include <sys/types.h>
#include <unistd.h>
#include "PosixFileStream.h"

using namespace Framework;

CPosixFileStream::CPosixFileStream(const char* path, int flags)
{
	m_fd = open(path, flags);
	if(m_fd < 0)
	{
		throw std::runtime_error("Invalid file handle.");
	}
}

CPosixFileStream::~CPosixFileStream()
{
	close(m_fd);
}

void CPosixFileStream::Seek(int64 position, STREAM_SEEK_DIRECTION direction)
{
	int whence = SEEK_SET;
	switch(direction)
	{
	case STREAM_SEEK_SET:
		whence = SEEK_SET;
		break;
	case STREAM_SEEK_CUR:
		whence = SEEK_CUR;
		break;
	case STREAM_SEEK_END:
		whence = SEEK_END;
		break;
	}
	off64_t result = lseek64(m_fd, position, whence);
	if(result == -1)
	{
		throw std::runtime_error("Seek failed.");
	}
	m_isEof = false;
}

bool CPosixFileStream::IsEOF()
{
	return m_isEof;
}

uint64 CPosixFileStream::Tell()
{
	off64_t result = lseek64(m_fd, 0, SEEK_CUR);
	if(result == -1)
	{
		throw std::runtime_error("Tell failed.");
	}
	return result;
}

uint64 CPosixFileStream::Read(void* buffer, uint64 length)
{
	int result = read(m_fd, buffer, length);
	if(result < 0)
	{
		throw std::runtime_error("Read failed.");
	}
	if(result == 0)
	{
		m_isEof = true;
	}
	return result;
}

uint64 CPosixFileStream::Write(const void* pBuffer, uint64 nLength)
{
	throw std::runtime_error("Not implemented.");
}

void CPosixFileStream::Flush()
{
	throw std::runtime_error("Not implemented.");
}
