#include "IosIStream.h"

using namespace Framework;
using namespace std;

CIosIStream::CIosIStream(istream& Stream) : 
m_Stream(Stream)
{

}

CIosIStream::~CIosIStream()
{

}

void CIosIStream::Seek(int64 nPosition, STREAM_SEEK_DIRECTION nDirection)
{
    throw exception();
}

uint64 CIosIStream::Read(void* pBuffer, uint64 nSize)
{
    m_Stream.read(reinterpret_cast<char*>(pBuffer), static_cast<streamsize>(nSize));
    return nSize;
}

uint64 CIosIStream::Write(const void* pBuffer, uint64 nSize)
{
    throw exception();
}

uint64 CIosIStream::Tell()
{
    return m_Stream.tellg();
}

bool CIosIStream::IsEOF()
{
    return m_Stream.eof();
}
