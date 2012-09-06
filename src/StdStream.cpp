#include "StdStream.h"
#include <assert.h>
#include <stdexcept>

using namespace Framework;

CStdStream::CStdStream(FILE* pFile)
{
	if(pFile == NULL)
	{
		throw std::runtime_error("Invalid file handle.");
	}
	m_pFile = pFile;
}

CStdStream::CStdStream(const char* path, const char* options)
{
	m_pFile = fopen(path, options);
	if(m_pFile == NULL)
	{
		throw std::runtime_error("Invalid file handle.");
	}
}

CStdStream::CStdStream(const wchar_t* path, const wchar_t* options)
{
#ifdef _MSC_VER
	m_pFile = _wfopen(path, options);
#else
	m_pFile = NULL;
#endif
	if(m_pFile == NULL)
	{
		throw std::runtime_error("Invalid file handle.");
	}
}

CStdStream::~CStdStream()
{
	if(m_pFile != NULL)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}
}

CStdStream::operator FILE*() const
{
	return m_pFile;
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
	assert(m_pFile != NULL);
#ifdef WIN32
	_fseeki64(m_pFile, nPosition, nDir);
#else
	fseek(m_pFile, nPosition, nDir);
#endif
}

bool CStdStream::IsEOF()
{
	return (feof(m_pFile) != 0);
}

uint64 CStdStream::Tell()
{
	assert(m_pFile != NULL);
#ifdef WIN32
	return _ftelli64(m_pFile);
#else
	return ftell(m_pFile);
#endif
}

uint64 CStdStream::Read(void* pBuffer, uint64 nLength)
{
	assert(m_pFile != NULL);
	if(feof(m_pFile) || ferror(m_pFile))
	{
		throw std::runtime_error("Can't read after end of file.");
	}
	return fread(pBuffer, 1, (size_t)nLength, m_pFile);
}

uint64 CStdStream::Write(const void* pBuffer, uint64 nLength)
{
	assert(m_pFile != NULL);
	return fwrite(pBuffer, 1, (size_t)nLength, m_pFile);
}

void CStdStream::Flush()
{
	assert(m_pFile != NULL);
	fflush(m_pFile);
}

void CStdStream::Close()
{
	assert(m_pFile != NULL);
	fclose(m_pFile);
	m_pFile = NULL;
}
