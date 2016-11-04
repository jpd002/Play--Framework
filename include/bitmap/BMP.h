#pragma once

#include <functional>
#include "Stream.h"
#include "Bitmap.h"

namespace Framework
{

	class CBMP
	{
	public:
		static CBitmap		ReadBitmap(CStream&);
		static void			WriteBitmap(const CBitmap&, CStream&);

	private:
		typedef std::function<void (CStream&, const CColor&)> PixelWriterFunction;

#pragma pack(push, 1)
		struct BMHEADER
		{
			uint16		nID;
			uint32		nFileSize;
			uint32		nReserved;
			uint32		nDataOffset;
		};
		static_assert(sizeof(BMHEADER) == 0xE, "sizeof(BMHEADER) must be 14 bytes.");

		struct BMINFOHEADER
		{
			uint32		nHeaderSize;
			uint32		nWidth;
			uint32		nHeight;
			uint16		nPlanes;
			uint16		nBPP;
			uint32		nCompression;
			uint32		nDataSize;
			uint32		nHorzResolution;
			uint32		nVertResolution;
			uint32		nColors;
			uint32		nImportantColors;
		};
		static_assert(sizeof(BMINFOHEADER) == 0x28, "sizeof(HEADER) must be 40 bytes.");
#pragma pack(pop)

		static void PixelWriter8(CStream&, const CColor&);
		static void PixelWriter24(CStream&, const CColor&);
		static void PixelWriter32(CStream&, const CColor&);
	};

}
