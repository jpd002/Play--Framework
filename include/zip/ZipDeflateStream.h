#pragma once

#include <zstd_zlibwrapper.h>
#include "Stream.h"

namespace Framework
{
    class CZipDeflateStream : public Framework::CStream
    {
    public:
                        CZipDeflateStream(Framework::CStream&);
        virtual         ~CZipDeflateStream();

        uint32          GetCrc() const;
        uint64          GetCompressedLength() const;
        uint64          GetUncompressedLength() const;

        void            Seek(int64, Framework::STREAM_SEEK_DIRECTION) override;
        uint64          Tell() override;
        uint64          Read(void*, uint64) override;
        uint64          Write(const void*, uint64) override;
        bool            IsEOF() override;
        void            Flush() override;

    private:
        enum BUFFERSIZE
        {
            BUFFERSIZE = 0x2000,
        };

        Framework::CStream&     m_baseStream;
        uint32                  m_crc = 0;
        uint64                  m_compressedLength = 0;
        uint64                  m_uncompressedLength = 0;
        z_stream                m_zStream;
    };
}
