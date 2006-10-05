#include "BMP.h"

using namespace Framework;

void CBMP::ToBMP(CBitmap* pBitmap, CStream* pStream)
{
	HEADER Header;
	uint32* pPixels;
	int i;
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
	
	for(i = (nHeight - 1); i >= 0; i--)
	{
		pStream->Write(pPixels + (i * nWidth), nWidth * 4);
	}
}
