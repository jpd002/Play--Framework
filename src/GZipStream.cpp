#include <stdexcept>
#include "GZipStream.h"

using namespace Framework;
using namespace std;

CGZipStream::CGZipStream(const char* sPath, const char* sMode)
{
	m_File = gzopen(sPath, sMode);
	if(m_File == Z_NULL)
	{
		throw runtime_error("Couldn't open file specified.");
	}
}

CGZipStream::~CGZipStream()
{
	gzclose(m_File);
}

uint64 CGZipStream::Read(void* pData, uint64 nSize)
{
	if(gzeof(m_File))
	{
		throw runtime_error("Can't read after end of file.");
	}
	return gzread(m_File, pData, (unsigned int)nSize);
}

uint64 CGZipStream::Write(const void* pData, uint64 nSize)
{
	return gzwrite(m_File, (const voidp)pData, (unsigned int)nSize);
}

void CGZipStream::Seek(int64 nAmount, STREAM_SEEK_DIRECTION nPosition)
{
	int nWhence;
	switch(nPosition)
	{
	case STREAM_SEEK_CUR:
		nWhence = SEEK_CUR;
		break;
	case STREAM_SEEK_SET:
		nWhence = SEEK_SET;
		break;
	case STREAM_SEEK_END:
		nWhence = SEEK_END;
		break;
	}
	gzseek(m_File, (long)nAmount, nPosition);
}

uint64 CGZipStream::Tell()
{
	return gztell(m_File);
}

bool CGZipStream::IsEOF()
{
	return (gzeof(m_File) != 0);
}
