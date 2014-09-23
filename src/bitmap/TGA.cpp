#include "bitmap/TGA.h"
#include <stdexcept>
#include <assert.h>

using namespace Framework;

Framework::CBitmap CTGA::ReadBitmap(CStream& stream)
{
	TGA_HEADER header;
	stream.Read(&header, sizeof(TGA_HEADER));

	if(header.imageType != 0x02)
	{
		throw std::runtime_error("Unsupported TGA file.");
	}
	
	if(header.bits != 32)
	{
		throw std::runtime_error("Unsupported TGA file.");
	}

	bool originIsTop = (header.descriptor & 0x20) != 0;
	bool originIsRight = (header.descriptor & 0x10) != 0;

	assert(!originIsRight);

	CBitmap bitmap(header.width, header.height, 32);

	if(originIsTop)
	{
		stream.Read(bitmap.GetPixels(), bitmap.GetPixelsSize());
	}
	else
	{
		for(unsigned int y = 0; y < header.height; y++)
		{
			uint8* dstLinePtr = bitmap.GetPixels() + bitmap.GetPitch() * (header.height - y - 1);
			stream.Read(dstLinePtr, bitmap.GetPitch());
		}
	}

	{
		uint8* pixelsPtr = bitmap.GetPixels();
		for(unsigned int i = 0; i < bitmap.GetPixelsSize() / 4; i++)
		{
			std::swap(pixelsPtr[0], pixelsPtr[2]);
			pixelsPtr += 4;
		}
	}

	return bitmap;
}
