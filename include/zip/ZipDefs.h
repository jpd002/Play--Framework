#ifndef _ZIPDEFS_H_
#define _ZIPDEFS_H_

#include "Types.h"

namespace Framework
{
    namespace Zip
    {
        enum FILEHEADER_SIG
        {
            FILEHEADER_SIG = 0x04034B50,
        };

        enum DIRFILEHEADER_SIG
        {
            DIRFILEHEADER_SIG = 0x02014B50,
        };

        enum DIRENDHEADER_SIG
        {
            DIRENDHEADER_SIG = 0x06054B50,
        };

    #pragma pack(push, 1)
        struct ZIPFILEHEADER
        {
            uint32 signature;
            uint16 versionNeeded;
            uint16 flags;
            uint16 compressionMethod;
            uint16 fileTime;
            uint16 fileDate;
            uint32 crc;
            uint32 compressedSize;
            uint32 uncompressedSize;
            uint16 fileNameLength;
            uint16 extraFieldLength;
        };

        struct ZIPDIRFILEHEADER
        {
            uint32 signature;
            uint16 versionMadeBy;
            uint16 versionNeeded;
            uint16 flags;
            uint16 compressionMethod;
            uint16 fileTime;
            uint16 fileDate;
            uint32 crc;
            uint32 compressedSize;
            uint32 uncompressedSize;
            uint16 fileNameLength;
            uint16 extraFieldLength;
            uint16 fileCommentLength;
            uint16 diskNumberStart;
            uint16 internalFileAttributes;
            uint32 externalFileAttributes;
            uint32 fileStartOffset;
        };

        struct ZIPDIRENDHEADER
        {
            uint32 signature;
            uint16 diskNumber;
            uint16 centralDirDiskNumber;
            uint16 dirEntryCount;
            uint16 totalDirEntryCount;
            uint32 dirSize;
            uint32 dirStartOffset;
            uint16 fileCommentLength;
        };

    #pragma pack(pop)
    }
}

#endif
