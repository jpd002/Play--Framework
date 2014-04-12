#include <cstdlib>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <zlib.h>
#include "bitmap/PNG.h"
#include "Endian.h"
#include "PtrStream.h"
#include "PtrMacro.h"
#include "StreamBitStream.h"

using namespace Framework;

CBitmap CPNG::ReadBitmap(CStream& stream)
{
	return CPNG().DoRead(stream);
}

CPNG::CPNG()
: m_pIDAT(nullptr)
, m_pBuffer(nullptr)
, m_nIDATSize(0)
{
	memset(&m_IHDR, 0, sizeof(m_IHDR));
}

CPNG::~CPNG()
{
	FREEPTR(m_pIDAT);
}

CBitmap CPNG::DoRead(CStream& stream)
{
	CBitmap result;

	stream.Seek(0, STREAM_SEEK_END);
	uint64 nLength = stream.Tell();
	stream.Seek(0, STREAM_SEEK_SET);

	uint8 header[8];
	stream.Read(header, 8);

	if((header[0] != 0x89) && (header[1] != 'P') && (header[2] != 'N') && (header[3] != 'G'))
	{
		throw std::runtime_error("Invalid PNG file.");
	}

	m_nIDATSize = 0;
	m_pIDAT = NULL;

	bool nDone = false;
	while(!nDone)
	{
		if(stream.Tell() >= nLength) break;

		uint32 nChunkSize = CEndian::FromMSBF32(stream.Read32());
		uint32 nChunkType = CEndian::FromMSBF32(stream.Read32());

		switch(nChunkType)
		{
		case 0x49484452:
			//IHDR
			{
				m_IHDR.Unserialize(stream);
				unsigned int nBufferSize = m_IHDR.CalculateNeededBufferSize();
				m_pBuffer = reinterpret_cast<uint8*>(malloc(nBufferSize));
			}
			break;
		case 0x49444154:
			//IDAT
			{
				unsigned int nIDATPos = m_nIDATSize;
				m_nIDATSize += nChunkSize;
				m_pIDAT = (uint8*)realloc(m_pIDAT, m_nIDATSize);
				stream.Read(m_pIDAT + nIDATPos, nChunkSize);
			}
			break;
		case 0x49454E44:
			//IEND
			UncompressIDAT();
			result = CreateBitmap();
			break;
		case 0x504C5445:
			//PLTE
			stream.Read(m_nPalette, nChunkSize);
			break;
		default:
			stream.Seek(nChunkSize, STREAM_SEEK_CUR);
			break;
		}

		//Skip CRC
		stream.Seek(4, STREAM_SEEK_CUR);
	}

	return result;
}

void CPNG::UncompressIDAT()
{
	uLongf dstLength = m_IHDR.CalculateNeededBufferSize();
	int result = uncompress(m_pBuffer, &dstLength, m_pIDAT, m_nIDATSize);
	if(result != Z_OK)
	{
		throw std::runtime_error("Couldn't uncompress IDAT stream.");
	}
}

void CPNG::SubFilter(uint8* pRaw, int nPitch, unsigned int nScanline, unsigned int nBPP)
{
	int nDist = (nBPP / 8);

	for(int i = 0; i < nPitch; i++)
	{
		uint8 nPredictor = 0;
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

void CPNG::UpFilter(uint8* pRaw, int nPitch, unsigned int nScanline, unsigned int nBPP)
{
	for(int i = 0; i < nPitch; i++)
	{
		uint8 nPredictor = 0;
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

void CPNG::AverageFilter(uint8* pRaw, int nPitch, unsigned int nScanline, unsigned int nBPP)
{
	int nDist = (nBPP / 8);

	for(int i = 0; i < nPitch; i++)
	{
		unsigned int nAbove = 0;
		if(nScanline == 0)
		{
			nAbove = 0;
		}
		else
		{
			nAbove = pRaw[i - nPitch];
		}

		unsigned int nLeft = 0;
		if((i - nDist) < 0)
		{
			nLeft = 0;
		}
		else
		{
			nLeft = pRaw[i - nDist];
		}

		uint8 nPredictor = (uint8)((nLeft + nAbove) / 2);
		pRaw[i] += nPredictor;
	}
}

uint8 CPNG::PaethPredictor(uint8 a, uint8 b, uint8 c)
{
	int p = a + b - c;
	int pa = abs(p - a);
	int pb = abs(p - b);
	int pc = abs(p - c);

	if((pa <= pb) && (pa <= pc)) return a;
	if((pb <= pc)) return b;
	return c;
}

void CPNG::PaethFilter(uint8* pRaw, int nPitch, unsigned int nScanline, unsigned int nBPP)
{
	int nDist = (nBPP / 8);

	for(int i = 0; i < static_cast<int>(nPitch); i++)
	{
		uint8 nLeft = 0;
		uint8 nUpperLeft = 0;
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

		uint8 nAbove = 0;
		if(nScanline == 0)
		{
			nAbove = 0;
		}
		else
		{
			nAbove = pRaw[i - nPitch];
		}
		uint8 nPredictor = PaethPredictor(nLeft, nAbove, nUpperLeft);
		pRaw[i] += nPredictor;
	}
}

CBitmap CPNG::CreateBitmap()
{
	unsigned int nBPP = m_IHDR.GetSamplesPerPixel() * m_IHDR.m_nDepth;

	CBitmap bitmap = CBitmap(m_IHDR.m_nWidth, m_IHDR.m_nHeight, nBPP);

	uint8* pSrc = m_pBuffer;
	uint8* pDst = bitmap.GetPixels();

	unsigned int nScanBits = nBPP * m_IHDR.m_nWidth;
	unsigned int nScanSize = (nScanBits + 7) / 8;

	for(unsigned int i = 0; i < m_IHDR.m_nHeight; i++)
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
		bitmap = ConvertTo32(bitmap);
	}

	return bitmap;
}

CBitmap CPNG::ConvertTo32(const CBitmap& srcBitmap) const
{
	CBitmap dstBitmap = CBitmap(srcBitmap.GetWidth(), srcBitmap.GetHeight(), 32);
	unsigned int nPixels = srcBitmap.GetWidth() * srcBitmap.GetHeight();

	uint8* pDst = dstBitmap.GetPixels();
	uint8* pSrc = srcBitmap.GetPixels();
	
	for(unsigned int i = 0, j = 0; i < nPixels; i++, j += 4)
	{
		unsigned int nColor = pSrc[i] * 3;
		pDst[j + 0] = m_nPalette[nColor + 0];
		pDst[j + 1] = m_nPalette[nColor + 1];
		pDst[j + 2] = m_nPalette[nColor + 2];
		pDst[j + 3] = 0;
	}

	return dstBitmap;
}

void CPNG::CIHDR::Unserialize(CStream& pStream)
{
	m_nWidth = CEndian::FromMSBF32(pStream.Read32());
	m_nHeight = CEndian::FromMSBF32(pStream.Read32());
	pStream.Read(&m_nDepth, 1);
	pStream.Read(&m_nColorType, 1);
	pStream.Read(&m_nCompression, 1);
	pStream.Read(&m_nFilter, 1);
	pStream.Read(&m_nInterlace, 1);
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
	unsigned int nBitsPerPixel = (GetSamplesPerPixel() * m_nDepth);
	unsigned int nScanline = (nBitsPerPixel * m_nWidth) / 8;
	if((nBitsPerPixel * m_nWidth) % 8) nScanline++;
	nScanline++;
	return (nScanline * m_nHeight);
}
