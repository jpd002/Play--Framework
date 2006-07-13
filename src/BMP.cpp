#include "BMP.h"

using namespace Framework;

void CBMP::ToBMP(CBitmap* pBitmap, CStream* pStream)
{
	HEADER Header;
	uint32* pData;
	int i;
	unsigned int nWidth, nHeight;

	if(pBitmap->GetBitsPerPixel() != 32) return;

	Header.nID				= 0x4D42;
	Header.nFileSize		= sizeof(HEADER) + pBitmap->GetDataSize();
	Header.nReserved		= 0;
	Header.nDataOffset		= 0x36;
	Header.nHeaderSize		= 0x28;
	Header.nWidth			= pBitmap->GetWidth();
	Header.nHeight			= pBitmap->GetHeight();
	Header.nPlanes			= 1;
	Header.nBPP				= pBitmap->GetBitsPerPixel();
	Header.nCompression		= 0;
	Header.nDataSize		= pBitmap->GetDataSize();
	Header.nHorzResolution	= 0;
	Header.nVertResolution	= 0;
	Header.nColors			= 0;
	Header.nImportantColors	= 0;

	pStream->Write(&Header, sizeof(HEADER));

	pData = (uint32*)pBitmap->GetData();
	nWidth = pBitmap->GetWidth();
	nHeight = pBitmap->GetHeight();
	
	for(i = (nHeight - 1); i >= 0; i--)
	{
		pStream->Write(pData + (i * nWidth), nWidth * 4);
	}
}
