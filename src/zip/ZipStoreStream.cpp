#include "zip/ZipStoreStream.h"
#include <zlib.h>
#include <stdexcept>
#include <algorithm>

using namespace Framework;

CZipStoreStream::CZipStoreStream(CStream& baseStream, unsigned int length)
: m_baseStream(baseStream)
, m_length(length)
{

}

void CZipStoreStream::Seek(int64, STREAM_SEEK_DIRECTION)
{
	throw std::runtime_error("Unsupported operation.");
}

uint64 CZipStoreStream::Tell()
{
	throw std::runtime_error("Unsupported operation.");
}

uint64 CZipStoreStream::Read(void* buffer, uint64 size)
{
	uint64 readSize = std::min<uint64>(size, m_length);
	uint64 resultSize = m_baseStream.Read(buffer, readSize);
	m_length -= static_cast<uint32>(resultSize);
	return resultSize;
}

uint64 CZipStoreStream::Write(const void* buffer, uint64 size)
{
	throw std::runtime_error("Unsupported operation.");
}

bool CZipStoreStream::IsEOF()
{
	return (m_length == 0);
}
