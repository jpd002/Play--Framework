#include "zip/ZipStoreStream.h"
#include <zlib.h>
#include <stdexcept>

using namespace std;
using namespace Framework;

CZipStoreStream::CZipStoreStream(CStream& baseStream) :
m_baseStream(baseStream),
m_crc(0),
m_length(0)
{

}

CZipStoreStream::~CZipStoreStream()
{

}

uint32 CZipStoreStream::GetCrc() const
{
    return m_crc;
}

uint64 CZipStoreStream::GetLength() const
{
    return m_length;
}

void CZipStoreStream::Seek(int64, STREAM_SEEK_DIRECTION)
{
    throw runtime_error("Unsupported operation.");
}

uint64 CZipStoreStream::Tell()
{
    return m_baseStream.Tell();
}

uint64 CZipStoreStream::Read(void*, uint64)
{
    throw runtime_error("Unsupported operation.");
}

uint64 CZipStoreStream::Write(const void* buffer, uint64 size)
{
    m_length += size;
    m_crc = crc32(m_crc, reinterpret_cast<const Bytef*>(buffer), static_cast<uInt>(size));
    return m_baseStream.Write(buffer, size);
}

bool CZipStoreStream::IsEOF()
{
    return m_baseStream.IsEOF();
}

