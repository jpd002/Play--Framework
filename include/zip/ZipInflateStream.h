#ifndef _ZIPINFLATESTREAM_H_
#define _ZIPINFLATESTREAM_H_

#include <zlib.h>
#include "Stream.h"

namespace Framework
{
    class CZipInflateStream : public Framework::CStream
    {
    public:
                                CZipInflateStream(Framework::CStream&, unsigned int);
        virtual                 ~CZipInflateStream();

        virtual void	        Seek(int64, Framework::STREAM_SEEK_DIRECTION);
	    virtual uint64	        Tell();
	    virtual uint64	        Read(void*, uint64);
	    virtual uint64	        Write(const void*, uint64);
	    virtual bool	        IsEOF();

    private:
        enum BUFFERSIZE
        {
            BUFFERSIZE = 0x2000,
        };

        void                    FeedBuffer();
        Framework::CStream&     m_baseStream;
        int                     m_compressedLength;
        z_stream                m_zStream;
        Bytef                   m_inputBuffer[BUFFERSIZE];
    };
}

#endif
