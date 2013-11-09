#pragma once

#include "Bitmap.h"
#include "Stream.h"

namespace Framework
{
	class CTGA
	{
	public:
		static CBitmap		ReadBitmap(CStream&);

	private:
		enum TGA_IMAGE_TYPE
		{
			TGA_IMAGE_RGB = 2,
		};

#pragma pack(push, 1)
		struct TGA_HEADER
		{
			uint8	idSize;
			uint8	colorMapType;
			uint8	imageType;
		
			int16	colorMapStart;
			int16	colorMapLength;
			uint8	colorMapBits;
	
			int16	startX;
			int16	startY;
			int16	width;
			int16	height;
	
			uint8	bits;
			uint8	descriptor;
		};
#pragma pack(pop)

		static_assert(sizeof(TGA_HEADER) == 0x12, "TGA Header must be 0x12 bytes.");
	};
}
