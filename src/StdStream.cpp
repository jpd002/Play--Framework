#include "StdStream.h"
#include <assert.h>
#include <stdexcept>

using namespace Framework;

CStdStream::CStdStream()
{
	
}

CStdStream::CStdStream(CStdStream&& rhs)
{
	std::swap(rhs.m_file, m_file);
}

CStdStream::CStdStream(FILE* file)
{
	if(file == nullptr)
	{
		throw std::runtime_error("Invalid file handle.");
	}
	m_file = file;
}

CStdStream::CStdStream(const char* path, const char* options)
{
	m_file = fopen(path, options);
	if(m_file == nullptr)
	{
		throw std::runtime_error("Invalid file handle.");
	}
}

CStdStream::CStdStream(const wchar_t* path, const wchar_t* options)
{
#ifdef _MSC_VER
	m_file = _wfopen(path, options);
#else
	m_file = nullptr;
#endif
	if(m_file == nullptr)
	{
		throw std::runtime_error("Invalid file handle.");
	}
}

CStdStream::~CStdStream()
{
	Clear();
}

void CStdStream::Clear()
{
	if(m_file != nullptr)
	{
		fclose(m_file);
		m_file = nullptr;
	}
}

bool CStdStream::IsEmpty() const
{
	return (m_file == nullptr);
}

CStdStream::operator FILE*() const
{
	return m_file;
}

CStdStream& CStdStream::operator =(CStdStream&& rhs)
{
	Clear();
	std::swap(rhs.m_file, m_file);
	return (*this);
}

void CStdStream::Seek(int64 nPosition, STREAM_SEEK_DIRECTION nDirection)
{
	int nDir;
	switch(nDirection)
	{
	case STREAM_SEEK_SET:
		nDir = SEEK_SET;
		break;
	case STREAM_SEEK_CUR:
		nDir = SEEK_CUR;
		break;
	case STREAM_SEEK_END:
		nDir = SEEK_END;
		break;
	}
	assert(m_file != nullptr);
#ifdef _WIN32
	_fseeki64(m_file, nPosition, nDir);
#else
	int result = fseeko(m_file, nPosition, nDir);
	assert(result == 0);
	assert((nDirection != STREAM_SEEK_SET) || (ftello(m_file) == nPosition));
#endif
}

bool CStdStream::IsEOF()
{
	return (feof(m_file) != 0);
}

uint64 CStdStream::Tell()
{
	assert(m_file != nullptr);
#ifdef _WIN32
	return _ftelli64(m_file);
#else
	return ftello(m_file);
#endif
}

uint64 CStdStream::Read(void* pBuffer, uint64 nLength)
{
	assert(m_file != nullptr);
	if(feof(m_file) || ferror(m_file))
	{
		throw std::runtime_error("Can't read after end of file.");
	}
	return fread(pBuffer, 1, (size_t)nLength, m_file);
}

uint64 CStdStream::Write(const void* pBuffer, uint64 nLength)
{
	assert(m_file != nullptr);
	return fwrite(pBuffer, 1, (size_t)nLength, m_file);
}

void CStdStream::Flush()
{
	assert(m_file != nullptr);
	fflush(m_file);
}

void CStdStream::Close()
{
	assert(m_file != nullptr);
	Clear();
}
