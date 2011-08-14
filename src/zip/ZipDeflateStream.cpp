#include "zip/ZipDeflateStream.h"
#include <stdexcept>
#include <assert.h>

using namespace Framework;

CZipDeflateStream::CZipDeflateStream(CStream& baseStream) :
m_baseStream(baseStream),
m_crc(0),
m_uncompressedLength(0),
m_compressedLength(0)
{
    m_zStream.zalloc = Z_NULL;
    m_zStream.zfree = Z_NULL;
    m_zStream.opaque = Z_NULL;
    if(deflateInit2(&m_zStream, Z_DEFAULT_COMPRESSION, 
        Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY) != Z_OK)
    {
		throw std::runtime_error("Error initializing deflate stream.");
    }
}

CZipDeflateStream::~CZipDeflateStream()
{
    deflateEnd(&m_zStream);
}

uint32 CZipDeflateStream::GetCrc() const
{
    return m_crc;
}

uint64 CZipDeflateStream::GetCompressedLength() const
{
    return m_compressedLength;
}

uint64 CZipDeflateStream::GetUncompressedLength() const
{
    return m_uncompressedLength;
}

void CZipDeflateStream::Seek(int64, STREAM_SEEK_DIRECTION)
{
    throw std::runtime_error("Unsupported operation.");
}

uint64 CZipDeflateStream::Tell()
{
    return m_baseStream.Tell();
}

uint64 CZipDeflateStream::Read(void*, uint64)
{
    throw std::runtime_error("Unsupported operation.");
}

uint64 CZipDeflateStream::Write(const void* buffer, uint64 size)
{
    m_uncompressedLength += size;
    m_crc = crc32(m_crc, reinterpret_cast<const Bytef*>(buffer), static_cast<uInt>(size));

    m_zStream.avail_in = static_cast<uInt>(size);
    m_zStream.next_in = const_cast<Bytef*>(reinterpret_cast<const Bytef*>(buffer));

    do
    {
        Bytef outBuffer[BUFFERSIZE];
        m_zStream.avail_out = BUFFERSIZE;
        m_zStream.next_out = outBuffer;

        int ret = deflate(&m_zStream, Z_NO_FLUSH);
        assert(ret != Z_STREAM_ERROR);

        uint64 have = BUFFERSIZE - m_zStream.avail_out;
        m_compressedLength += have;
        m_baseStream.Write(outBuffer, have);
    } 
    while(m_zStream.avail_out == 0);
    assert(m_zStream.avail_in == 0);

    return size;
}

bool CZipDeflateStream::IsEOF()
{
    return m_baseStream.IsEOF();
}

void CZipDeflateStream::Flush()
{
    do 
    {
        Bytef outBuffer[BUFFERSIZE];
        m_zStream.avail_out = BUFFERSIZE;
        m_zStream.next_out = outBuffer;

        int ret = deflate(&m_zStream, Z_FINISH);
        assert(ret != Z_STREAM_ERROR);

        uint64 have = BUFFERSIZE - m_zStream.avail_out;
        m_compressedLength += have;
        m_baseStream.Write(outBuffer, have);
    } 
    while(m_zStream.avail_out == 0);
    assert(m_zStream.avail_in == 0);     /* all input will be used */   
}
