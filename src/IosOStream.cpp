#include "IosOStream.h"

using namespace Framework;
using namespace std;

CIosOStream::CIosOStream(ostream& Stream) : 
m_Stream(Stream)
{

}

CIosOStream::~CIosOStream()
{

}

void CIosOStream::Seek(int64 nPosition, STREAM_SEEK_DIRECTION nDirection)
{
    throw exception();
}

uint64 CIosOStream::Read(void* pBuffer, uint64 nSize)
{
    throw exception();
}

uint64 CIosOStream::Write(const void* pBuffer, uint64 nSize)
{
    m_Stream.write(reinterpret_cast<const char*>(pBuffer), static_cast<streamsize>(nSize));
    return nSize;
}

uint64 CIosOStream::Tell()
{
    return m_Stream.tellp();
}

bool CIosOStream::IsEOF()
{
    return m_Stream.eof();
}
