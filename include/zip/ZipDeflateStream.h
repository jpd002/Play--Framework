#ifndef _ZIPDEFLATESTREAM_H_
#define _ZIPDEFLATESTREAM_H_

#include <zlib.h>
#include "Stream.h"

namespace Framework
{
    class CZipDeflateStream : public Framework::CStream
    {
    public:
                                CZipDeflateStream(Framework::CStream&);
        virtual                 ~CZipDeflateStream();

        uint32                  GetCrc() const;
        uint64                  GetCompressedLength() const;
        uint64                  GetUncompressedLength() const;

        virtual void	        Seek(int64, Framework::STREAM_SEEK_DIRECTION);
	    virtual uint64	        Tell();
	    virtual uint64	        Read(void*, uint64);
	    virtual uint64	        Write(const void*, uint64);
	    virtual bool	        IsEOF();
        virtual void            Flush();

    private:
        enum BUFFERSIZE
        {
            BUFFERSIZE = 0x2000,
        };

        Framework::CStream&     m_baseStream;
        uint32                  m_crc;
        uint64                  m_compressedLength;
        uint64                  m_uncompressedLength;
        z_stream                m_zStream;
    };
}

#endif
