#pragma once

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

		enum DIRENDHEADER64_SIG
		{
			DIRENDHEADER64_SIG = 0x06064B50,
		};

		enum COMPRESSION_METHOD
		{
			STORE = 0,
			DEFLATE = 8,
			ZSTD = 93
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
		static_assert(sizeof(ZIPFILEHEADER) == 30);

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
		static_assert(sizeof(ZIPDIRFILEHEADER) == 46);

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
		static_assert(sizeof(ZIPDIRENDHEADER) == 22);

		struct ZIPDIRENDHEADER64
		{
			uint32 signature;
			uint64 size;
			uint16 versionMadeBy;
			uint16 versionNeeded;
			uint32 diskNumber;
			uint32 centralDirDiskNumber;
			uint64 dirEntryCount;
			uint64 totalDirEntryCount;
			uint64 dirSize;
			uint64 dirStartOffset;
		};
		static_assert(sizeof(ZIPDIRENDHEADER64) == 56);
#pragma pack(pop)
	}
}
