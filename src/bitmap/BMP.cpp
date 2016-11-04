#include <stdexcept>
#include "bitmap/BMP.h"

using namespace Framework;

#define BMP_MAGIC (0x4D42)    //BM

void CBMP::WriteBitmap(const CBitmap& bitmap, CStream& stream)
{
	unsigned int bitDepth = bitmap.GetBitsPerPixel();
	bool supported = (bitDepth == 32) || (bitDepth == 24) || (bitDepth == 8);
	if(!supported)
	{
		throw std::runtime_error("Unsupported bit depth.");
	}

	uint32 colorTableEntryCount = (bitDepth == 8) ? 256 : 0;
	uint32 dataOffset = sizeof(BMHEADER) + sizeof(BMINFOHEADER) + (colorTableEntryCount * 4);
	uint32 rowSize = (bitmap.GetPitch() + 3) & ~0x03;
	uint32 paddingSize = rowSize - bitmap.GetPitch();
	uint32 imageDataSize = rowSize * bitmap.GetHeight();

	{
		BMHEADER bmHeader;
		bmHeader.nID         = BMP_MAGIC;
		bmHeader.nFileSize   = dataOffset + imageDataSize;
		bmHeader.nReserved   = 0;
		bmHeader.nDataOffset = dataOffset;
		stream.Write(&bmHeader, sizeof(BMHEADER));
	}

	{
		BMINFOHEADER bmInfoHeader;
		bmInfoHeader.nHeaderSize      = sizeof(BMINFOHEADER);
		bmInfoHeader.nWidth           = bitmap.GetWidth();
		bmInfoHeader.nHeight          = bitmap.GetHeight();
		bmInfoHeader.nPlanes          = 1;
		bmInfoHeader.nBPP             = bitDepth;
		bmInfoHeader.nCompression     = 0;  //BI_RGB
		bmInfoHeader.nDataSize        = 0;
		bmInfoHeader.nHorzResolution  = 0;
		bmInfoHeader.nVertResolution  = 0;
		bmInfoHeader.nColors          = 0;
		bmInfoHeader.nImportantColors = 0;
		stream.Write(&bmInfoHeader, sizeof(BMINFOHEADER));
	}

	if(colorTableEntryCount != 0)
	{
		for(uint32 i = 0; i < colorTableEntryCount; i++)
		{
			uint32 color = (i << 0) | (i << 8) | (i << 16);
			stream.Write32(color);
		}
	}

	unsigned int width = bitmap.GetWidth();
	unsigned int height = bitmap.GetHeight();

	PixelWriterFunction pixelWriter;
	switch(bitDepth)
	{
	case 8:
		pixelWriter = PixelWriter8;
		break;
	case 24:
		pixelWriter = PixelWriter24;
		break;
	case 32:
		pixelWriter = PixelWriter32;
		break;
	}

	uint32 paddingValue = 0;
	for(int y = (height - 1); y >= 0; y--)
	{
		for(int x = 0; x < static_cast<int>(width); x++)
		{
			CColor pixel = bitmap.GetPixel(x, y);
			pixelWriter(stream, pixel);
		}
		if(paddingSize != 0)
		{
			stream.Write(&paddingValue, paddingSize);
		}
	}
}

CBitmap CBMP::ReadBitmap(CStream& stream)
{
	BMHEADER bmHeader;
	stream.Read(&bmHeader, sizeof(BMHEADER));

	if(bmHeader.nID != BMP_MAGIC)
	{
		throw std::runtime_error("Invalid header signature.");
	}

	BMINFOHEADER bmInfoHeader;
	stream.Read(&bmInfoHeader, sizeof(BMINFOHEADER));

	if(bmInfoHeader.nHeaderSize != sizeof(BMINFOHEADER))
	{
		throw std::runtime_error("Invalid header size.");
	}

	if(bmInfoHeader.nBPP != 8)
	{
		throw std::runtime_error("Bit depths other than 8-bits aren't supported.");
	}

	unsigned int nWidth  = bmInfoHeader.nWidth;
	unsigned int nHeight = bmInfoHeader.nHeight;

	stream.Seek(bmHeader.nDataOffset, STREAM_SEEK_SET);

	CBitmap result(nWidth, nHeight, bmInfoHeader.nBPP);
	uint8* pPixels = result.GetPixels();
	for(int i = (nHeight - 1); i >= 0; i--)
	{
		stream.Read(pPixels + (i * nWidth), nWidth);
		stream.Seek(((4 - (nWidth & 3)) & 3), STREAM_SEEK_CUR);
	}

	return result;
}

void CBMP::PixelWriter8(CStream& stream, const CColor& pixel)
{
	stream.Write(&pixel.r, 1);
}

void CBMP::PixelWriter24(CStream& stream, const CColor& pixel)
{
	stream.Write(&pixel.b, 1);
	stream.Write(&pixel.g, 1);
	stream.Write(&pixel.r, 1);
}

void CBMP::PixelWriter32(CStream& stream, const CColor& pixel)
{
	stream.Write(&pixel.b, 1);
	stream.Write(&pixel.g, 1);
	stream.Write(&pixel.r, 1);
	stream.Write(&pixel.a, 1);
}
