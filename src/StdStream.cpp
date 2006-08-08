/*

	Framework - StdStream.cpp
	File Version 1.0.000

*/

#include "StdStream.h"
#include <assert.h>
#include <exception>

using namespace Framework;
using namespace std;

CStdStream::CStdStream(FILE* pFile)
{
	if(pFile == NULL)
	{
		throw exception("Invalid file handle.");
	}
	m_pFile = pFile;
}

CStdStream::~CStdStream()
{
	if(m_pFile != NULL)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}
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
	fseek(m_pFile, (long)nPosition, nDir);
}

bool CStdStream::IsEOF()
{
	return (feof(m_pFile) != 0);
}

uint64 CStdStream::Tell()
{
	assert(m_pFile != NULL);
	return ftell(m_pFile);
}

uint64 CStdStream::Read(void* pBuffer, uint64 nLength)
{
	assert(m_pFile != NULL);
	if(feof(m_pFile) || ferror(m_pFile))
	{
		throw "Can't read after end of file.";
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
