#ifndef _ZIPSTORESTREAM_H_
#define _ZIPSTORESTREAM_H_

#include "Stream.h"

namespace Framework
{
    class CZipStoreStream : public Framework::CStream
    {
    public:
                                CZipStoreStream(Framework::CStream&);
        virtual                 ~CZipStoreStream();

        uint32                  GetCrc() const;
        uint64                  GetLength() const;

        virtual void	        Seek(int64, Framework::STREAM_SEEK_DIRECTION);
	    virtual uint64	        Tell();
	    virtual uint64	        Read(void*, uint64);
	    virtual uint64	        Write(const void*, uint64);
	    virtual bool	        IsEOF();

    private:
        Framework::CStream&     m_baseStream;
        uint32                  m_crc;
        uint64                  m_length;
    };
}

#endif
