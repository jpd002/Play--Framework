#include <stdexcept>
#include "bitmap/BMP.h"

using namespace Framework;

void CBMP::WriteBitmap(const CBitmap& bitmap, CStream& stream)
{
	unsigned int bitDepth = bitmap.GetBitsPerPixel();
	if(bitDepth != 32 && bitDepth != 24)
	{
		throw std::runtime_error("Only 24 or 32-bits bitmaps supported.");
	}

	HEADER header;
	header.nID				= 0x4D42;
	header.nFileSize		= sizeof(HEADER) + bitmap.GetPixelsSize();
	header.nReserved		= 0;
	header.nDataOffset		= 0x36;
	header.nHeaderSize		= 0x28;
	header.nWidth			= bitmap.GetWidth();
	header.nHeight			= bitmap.GetHeight();
	header.nPlanes			= 1;
	header.nBPP				= bitDepth;
	header.nCompression		= 0;
	header.nDataSize		= bitmap.GetPixelsSize();
	header.nHorzResolution	= 0;
	header.nVertResolution	= 0;
	header.nColors			= 0;
	header.nImportantColors	= 0;

	stream.Write(&header, sizeof(HEADER));

	unsigned int width = bitmap.GetWidth();
	unsigned int height = bitmap.GetHeight();

	PixelWriterFunction pixelWriter;
	switch(bitDepth)
	{
	case 32:
		pixelWriter = PixelWriter32;
		break;
	case 24:
		pixelWriter = PixelWriter24;
		break;
	}

	unsigned int paddingSize = (4 - (bitmap.GetPitch() & 3) & 3);
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

CBitmap CBMP::ReadBitmap(CStream& Stream)
{
	HEADER Header;
	Stream.Read(&Header, sizeof(HEADER));

	if(Header.nID != 0x4D42)
	{
		throw std::runtime_error("Invalid header signature.");
	}

	if(Header.nBPP != 8)
	{
		throw std::runtime_error("Bit depths other than 8-bits aren't supported.");
	}

	unsigned int nWidth		= Header.nWidth;
	unsigned int nHeight	= Header.nHeight;

	Stream.Seek(Header.nDataOffset, STREAM_SEEK_SET);

	CBitmap result(nWidth, nHeight, Header.nBPP);
	uint8* pPixels = result.GetPixels();
	for(int i = (nHeight - 1); i >= 0; i--)
	{
		Stream.Read(pPixels + (i * nWidth), nWidth);
		Stream.Seek(((4 - (nWidth & 3)) & 3), STREAM_SEEK_CUR);
	}

	return result;
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
