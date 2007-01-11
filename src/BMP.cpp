#include <exception>
#include "BMP.h"

using namespace Framework;
using namespace std;

void CBMP::ToBMP(CBitmap* pBitmap, CStream* pStream)
{
	HEADER Header;
	uint32* pPixels;
	unsigned int nWidth, nHeight;

	if(pBitmap->GetBitsPerPixel() != 32) return;

	Header.nID				= 0x4D42;
	Header.nFileSize		= sizeof(HEADER) + pBitmap->GetPixelsSize();
	Header.nReserved		= 0;
	Header.nDataOffset		= 0x36;
	Header.nHeaderSize		= 0x28;
	Header.nWidth			= pBitmap->GetWidth();
	Header.nHeight			= pBitmap->GetHeight();
	Header.nPlanes			= 1;
	Header.nBPP				= pBitmap->GetBitsPerPixel();
	Header.nCompression		= 0;
	Header.nDataSize		= pBitmap->GetPixelsSize();
	Header.nHorzResolution	= 0;
	Header.nVertResolution	= 0;
	Header.nColors			= 0;
	Header.nImportantColors	= 0;

	pStream->Write(&Header, sizeof(HEADER));

	pPixels = reinterpret_cast<uint32*>(pBitmap->GetPixels());
	nWidth = pBitmap->GetWidth();
	nHeight = pBitmap->GetHeight();
	
	for(int i = (nHeight - 1); i >= 0; i--)
	{
		pStream->Write(pPixels + (i * nWidth), nWidth * 4);
	}
}

void CBMP::FromBMP(CBitmap& Dst, CStream& Stream)
{
	HEADER Header;
	uint8* pPixels;
	unsigned int nWidth, nHeight;

	Stream.Read(&Header, sizeof(HEADER));

	if(Header.nID != 0x4D42)
	{
		throw exception("Invalid header signature.");
	}

	if(Header.nBPP != 8)
	{
		throw exception("Bit depths other than 8-bits aren't supported.");
	}

	nWidth	= Header.nWidth;
	nHeight	= Header.nHeight;

	Dst.Allocate(nWidth, nHeight, Header.nBPP);

	Stream.Seek(Header.nDataOffset, STREAM_SEEK_SET);

	pPixels = Dst.GetPixels();
	for(int i = (nHeight - 1); i >= 0; i--)
	{
		Stream.Read(pPixels + (i * nWidth), nWidth);
		Stream.Seek(((4 - (nWidth & 3)) & 3), STREAM_SEEK_CUR);
	}
}
