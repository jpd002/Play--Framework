#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>
#include "PNG.h"
#include "Endian.h"
#include "Deflate.h"
#include "PtrStream.h"
#include "PtrMacro.h"
#include "StreamBitStream.h"

using namespace Framework;

CBitmap* CPNG::FromPNG(CStream* pStream)
{
	CBitmap* pBitmap;
	CPNG PNG(pStream, &pBitmap);
	return pBitmap;
}

CPNG::CPNG(CStream* pStream, CBitmap** pBitmap)
{
	uint8 pHeader[8];
	unsigned int nBufferSize, nIDATPos;
	bool nDone;
	uint64 nLenght;
	uint32 nChunkType, nChunkSize;

	(*pBitmap) = NULL;

	pStream->Seek(0, STREAM_SEEK_END);
	nLenght = pStream->Tell();
	pStream->Seek(0, STREAM_SEEK_SET);

	pStream->Read(pHeader, 8);

	if((pHeader[0] != 0x89) && (pHeader[1] != 'P') && (pHeader[2] != 'N') && (pHeader[3] != 'G'))
	{
		return;
	}

	m_nIDATSize = 0;
	m_pIDAT = NULL;

	nDone = false;
	while(!nDone)
	{
		if(pStream->Tell() >= nLenght) break;

		nChunkSize = FromMSBF32(pStream->Read32());
		nChunkType = FromMSBF32(pStream->Read32());

		switch(nChunkType)
		{
		case 0x49484452:
			//IHDR
			m_IHDR.Unserialize(pStream);
			nBufferSize = m_IHDR.CalculateNeededBufferSize();
			m_pBuffer = (uint8*)malloc(nBufferSize);
			break;
		case 0x49444154:
			//IDAT
			nIDATPos = m_nIDATSize;
			m_nIDATSize += nChunkSize;
			m_pIDAT = (uint8*)realloc(m_pIDAT, m_nIDATSize);
			pStream->Read(m_pIDAT + nIDATPos, nChunkSize);
			break;
		case 0x49454E44:
			//IEND
			UncompressIDAT();
			(*pBitmap) = CreateBitmap();
			break;
		case 0x504C5445:
			//PLTE
			pStream->Read(m_nPalette, nChunkSize);
			break;
		default:
			pStream->Seek(nChunkSize, STREAM_SEEK_CUR);
			break;
		}

		//Skip CRC
		pStream->Seek(4, STREAM_SEEK_CUR);
	}
}

CPNG::~CPNG()
{
	FREEPTR(m_pIDAT);
}

void CPNG::UncompressIDAT()
{
	uint8 nMethod;
	uint8 nFlags;
	CPtrStream p(m_pIDAT, m_nIDATSize);
	p.Read(&nMethod, 1);
	p.Read(&nFlags, 1);
	CStreamBitStream s(&p);
	CDeflate::Decompress(&s, m_pBuffer);
}

void CPNG::SubFilter(uint8* pRaw, unsigned int nPitch, unsigned int nScanline, unsigned int nBPP)
{
	uint8 nPredictor;
	int i;
	int nDist;

	nDist = (nBPP / 8);

	for(i = 0; i < (int)nPitch; i++)
	{
		if((i - nDist) < 0)
		{
			nPredictor = 0;
		}
		else
		{
			nPredictor = pRaw[i - nDist];
		}
		pRaw[i] += nPredictor;
	}

}

void CPNG::UpFilter(uint8* pRaw, unsigned int nPitch, unsigned int nScanline, unsigned int nBPP)
{
	uint8 nPredictor;
	int i;

	for(i = 0; i < (int)nPitch; i++)
	{
		if(nScanline == 0)
		{
			nPredictor = 0;
		}
		else
		{
			nPredictor = pRaw[i - nPitch];
		}
		pRaw[i] += nPredictor;
	}
}

void CPNG::AverageFilter(uint8* pRaw, unsigned int nPitch, unsigned int nScanline, unsigned int nBPP)
{
	uint8 nPredictor;
	unsigned int nLeft, nAbove;
	int i;
	int nDist;

	nDist = (nBPP / 8);

	for(i = 0; i < (int)nPitch; i++)
	{
		if(nScanline == 0)
		{
			nAbove = 0;
		}
		else
		{
			nAbove = pRaw[i - nPitch];
		}
		if((i - nDist) < 0)
		{
			nLeft = 0;
		}
		else
		{
			nLeft = pRaw[i - nDist];
		}
		nPredictor = (uint8)((nLeft + nAbove) / 2);
		pRaw[i] += nPredictor;
	}
}

uint8 CPNG::PaethPredictor(uint8 a, uint8 b, uint8 c)
{
	int p, pa, pb, pc;

	p = a + b - c;
	pa = abs(p - a);
	pb = abs(p - b);
	pc = abs(p - c);

	if((pa <= pb) && (pa <= pc)) return a;
	if((pb <= pc)) return b;
	return c;
}

void CPNG::PaethFilter(uint8* pRaw, unsigned int nPitch, unsigned int nScanline, unsigned int nBPP)
{
	uint8 nPredictor;
	uint8 nLeft, nAbove, nUpperLeft;
	int nDist;
	int i;

	nDist = (nBPP / 8);

	for(i = 0; i < (int)nPitch; i++)
	{
		if((i - nDist) < 0)
		{
			nLeft = 0;
			nUpperLeft = 0;
		}
		else
		{
			nLeft = pRaw[i - nDist];
			if(nScanline == 0)
			{
				nUpperLeft = 0;
			}
			else
			{
				nUpperLeft = pRaw[(i - nDist) - nPitch];
			}
		}
		if(nScanline == 0)
		{
			nAbove = 0;
		}
		else
		{
			nAbove = pRaw[i - nPitch];
		}
		nPredictor = PaethPredictor(nLeft, nAbove, nUpperLeft);
		pRaw[i] += nPredictor;
	}
}

CBitmap* CPNG::CreateBitmap()
{
	unsigned int i, nScanSize, nScanBits, nBPP;
	CBitmap* pBitmap;
	uint8* pSrc;
	uint8* pDst;

	nBPP = m_IHDR.GetSamplesPerPixel() * m_IHDR.m_nDepth;

	pBitmap = new CBitmap(m_IHDR.m_nWidth, m_IHDR.m_nHeight, nBPP);

	pSrc = m_pBuffer;
	pDst = pBitmap->GetPixels();

	nScanBits = nBPP * m_IHDR.m_nWidth;
	nScanSize = (nScanBits + 7) / 8;

	for(i = 0; i < m_IHDR.m_nHeight; i++)
	{
		
		memcpy(pDst, pSrc + 1, nScanSize);
		switch(pSrc[0])
		{
		case 0x00:
			break;
		case 0x01:
			SubFilter(pDst, nScanSize, i, nBPP);
			break;
		case 0x02:
			UpFilter(pDst, nScanSize, i, nBPP);
			break;
		case 0x03:
			AverageFilter(pDst, nScanSize, i, nBPP);
			break;
		case 0x04:
			PaethFilter(pDst, nScanSize, i, nBPP);
			break;
		default:
			assert(0);
			break;
		}

		pSrc += nScanSize + 1;
		pDst += nScanSize;
	}

	if(m_IHDR.m_nColorType == 3)
	{
		pBitmap = ConvertTo32(pBitmap);
	}

	return pBitmap;
}

CBitmap* CPNG::ConvertTo32(CBitmap* pSrcBitmap)
{
	CBitmap* pDstBitmap;
	unsigned int nPixels, i, j;
	unsigned int nColor;
	uint8* pSrc;
	uint8* pDst;

	pDstBitmap = new CBitmap(pSrcBitmap->GetWidth(), pSrcBitmap->GetHeight(), 32);
	nPixels = pSrcBitmap->GetWidth() * pSrcBitmap->GetHeight();

	pDst = pDstBitmap->GetPixels();
	pSrc = pSrcBitmap->GetPixels();
	
	for(i = 0, j = 0; i < nPixels; i++, j += 4)
	{
		nColor = pSrc[i] * 3;
		pDst[j + 0] = m_nPalette[nColor + 0];
		pDst[j + 1] = m_nPalette[nColor + 1];
		pDst[j + 2] = m_nPalette[nColor + 2];
		pDst[j + 3] = 0;
	}

	delete pSrcBitmap;

	return pDstBitmap;
}

void CPNG::CIHDR::Unserialize(CStream* pStream)
{
	m_nWidth = FromMSBF32(pStream->Read32());
	m_nHeight = FromMSBF32(pStream->Read32());
	pStream->Read(&m_nDepth, 1);
	pStream->Read(&m_nColorType, 1);
	pStream->Read(&m_nCompression, 1);
	pStream->Read(&m_nFilter, 1);
	pStream->Read(&m_nInterlace, 1);
}

unsigned int CPNG::CIHDR::GetSamplesPerPixel()
{
	switch(m_nColorType)
	{
	case 0:
	case 3:
		return 1;
		break;
	case 2:
		return 3;
		break;
	case 4:
		return 2;
		break;
	case 6:
		return 4;
		break;
	}
	assert(0);
	return 0;
}

unsigned int CPNG::CIHDR::CalculateNeededBufferSize()
{
	unsigned int nBitsPerPixel, nScanline;
	nBitsPerPixel = (GetSamplesPerPixel() * m_nDepth);
	nScanline = (nBitsPerPixel * m_nWidth) / 8;
	if((nBitsPerPixel * m_nWidth) % 8) nScanline++;
	nScanline++;
	return (nScanline * m_nHeight);
}
