#include "zip/ZipInflateStream.h"
#include <stdexcept>
#include <algorithm>
#include <string.h>
#include <assert.h>

using namespace Framework;

CZipInflateStream::CZipInflateStream(CStream& baseStream, unsigned int compressedLength) :
m_baseStream(baseStream),
m_compressedLength(compressedLength)
{
    m_zStream.zalloc = Z_NULL;
    m_zStream.zfree = Z_NULL;
    m_zStream.opaque = Z_NULL;
    m_zStream.avail_in = 0;
    m_zStream.next_in = Z_NULL;
    if(inflateInit2(&m_zStream, -MAX_WBITS) != Z_OK)
    {
		throw std::runtime_error("zlib stream initialization error.");
    }
}

CZipInflateStream::~CZipInflateStream()
{
    inflateEnd(&m_zStream);
}

void CZipInflateStream::Seek(int64, STREAM_SEEK_DIRECTION)
{
	throw std::runtime_error("Unsupported operation.");
}

uint64 CZipInflateStream::Tell()
{
    throw std::runtime_error("Unsupported operation.");
}

uint64 CZipInflateStream::Read(void* buffer, uint64 length)
{
    Bytef outBuffer[BUFFERSIZE];
    uint8* destBuffer = reinterpret_cast<uint8*>(buffer);
    uint64 sizeCounter = length;
    do
    {
        if(m_zStream.avail_in == 0)
        {
            if(m_compressedLength == 0)
            {
                //EOF
                break;
            }
            FeedBuffer();
        }

		int bufferSize = std::min<int>(BUFFERSIZE, static_cast<int>(sizeCounter));
        m_zStream.avail_out = bufferSize;
        m_zStream.next_out = outBuffer;

        int ret = inflate(&m_zStream, Z_NO_FLUSH);
        switch (ret) {
        case Z_NEED_DICT:
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
			throw std::runtime_error("Error occured while inflating.");
            break;
        }

        int have = bufferSize - m_zStream.avail_out;
        memcpy(destBuffer, outBuffer, have);
        destBuffer += have;
        sizeCounter -= have;
        if(ret == Z_STREAM_END)
        {
            assert(IsEOF());
            break;
        }
    } 
    while (sizeCounter != 0);
    return length - sizeCounter;
}

uint64 CZipInflateStream::Write(const void* buffer, uint64 size)
{
    throw std::runtime_error("Unsupported operation.");
}

bool CZipInflateStream::IsEOF()
{
    return (m_compressedLength == 0) && (m_zStream.avail_in == 0);
}

void CZipInflateStream::FeedBuffer()
{
    assert(m_zStream.avail_in == 0);
	unsigned int toRead = std::min<unsigned int>(BUFFERSIZE, m_compressedLength);
    m_zStream.avail_in = static_cast<uInt>(m_baseStream.Read(m_inputBuffer, toRead));
    m_zStream.next_in = m_inputBuffer;
    m_compressedLength -= m_zStream.avail_in;
}
