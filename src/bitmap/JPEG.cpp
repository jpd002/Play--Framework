#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bitmap/JPEG.h"
#include "idct/TrivialC.h"
#include "idct/IEEE1180.h"
#include "StreamBitStream.h"
#include "PtrMacro.h"

using namespace Framework;

//IDCT::CInterface*	CJPEG::m_pIDCT = IDCT::CTrivialC::GetInstance();
IDCT::CInterface*	CJPEG::m_pIDCT = IDCT::CIEEE1180::GetInstance();

unsigned char		CJPEG::m_nZigZag[64] =
{
	 0,  1,  8, 16,  9,  2,  3, 10,
	17, 24, 32, 25, 18, 11,  4,  5,
	12, 19, 26, 33, 40, 48, 41, 34,
	27, 20, 13,  6,  7, 14, 21, 28,
	35, 42, 49, 56, 57, 50, 43, 36,
	29, 22, 15, 23, 30, 37, 44, 51,
	58, 59, 52, 45, 38, 31, 39, 46,
	53, 60, 61, 54, 47, 55, 62, 63
};

CJPEG::CJPEG(CStream& pStream)
{
	m_stream = new CStreamBitStream(pStream);

	for(int i = 0; i < 4; i++)
	{
		m_Qt[i].pQ = NULL;

		for(int j = 0; j < 16; j++)
		{
			m_ACHt[i].pV[j] = NULL;
			m_DCHt[i].pV[j] = NULL;
		}

		m_ACHt[i].nCodeTable = NULL;
		m_DCHt[i].nCodeTable = NULL;
	}

	m_Frame.pCompoment = NULL;
	m_Scan.pComponent = NULL;
}

CJPEG::~CJPEG()
{
	for(int i = 0; i < 4; i++)
	{
		if(m_Qt[i].pQ != NULL)
		{
			free(m_Qt[i].pQ);
		}

		for(int j = 0; j < 16; j++)
		{
			if(m_ACHt[i].pV[j] != NULL)
			{
				free(m_ACHt[i].pV[j]);
			}
			if(m_DCHt[i].pV[j] != NULL)
			{
				free(m_DCHt[i].pV[j]);
			}
		}

		if(m_ACHt[i].nCodeTable != NULL)
		{
			free(m_ACHt[i].nCodeTable);
		}

		if(m_DCHt[i].nCodeTable != NULL)
		{
			free(m_DCHt[i].nCodeTable);
		}
	}
	
	if(m_Frame.pCompoment != NULL)
	{
		free(m_Frame.pCompoment);
	}

	if(m_Scan.pComponent != NULL)
	{
		free(m_Scan.pComponent);
	}

	delete m_stream;
}

CBitmap CJPEG::ReadBitmap(CStream& stream)
{
	CJPEG JPEG(stream);
	return JPEG.Process();
}

/////////////////////////////////////////////////////
//Huffman -----------------------------------------//
/////////////////////////////////////////////////////

uint8 CJPEG::HuffGetBit()
{
	if(m_stream->IsOnByteBoundary())
	{
		if(m_nHuffSkipNext)
		{
			uint8 markerEscape = m_stream->GetBits_MSBF(8);
			assert(markerEscape == 0x00);
			m_nHuffSkipNext = false;
		}
		if(m_stream->PeekBits_MSBF(8) == 0xFF)
		{
			//Trap if we want to...
			uint16 fullMarker = m_stream->PeekBits_MSBF(16);
			assert(fullMarker == 0xFF00);
			m_nHuffSkipNext = true;
		}
	}

	return (uint8)m_stream->GetBits_MSBF(1);
}

uint8 CJPEG::HuffDecode(HUFFMANTABLE* t)
{
	int i = 0;
	int16 nCode = HuffGetBit();

	while(nCode > t->nMax[i])
	{
		nCode <<= 1;
		nCode |= HuffGetBit();
		i++;
	}

	int j = nCode - t->nMin[i];
	return t->pV[i][j];
}

uint32 CJPEG::HuffReceive(unsigned int nBits)
{
	uint32 nTemp = 0;
	for(unsigned int i = 0; i < nBits; i++)
	{
		nTemp <<= 1;
		nTemp |= HuffGetBit();
	}

	return nTemp;
}

uint32 CJPEG::HuffExtend(uint32 nV, unsigned int nBits)
{
	uint32 nVt = (1 << (nBits - 1));
	if(nV < nVt)
	{
		nVt = (0xFFFFFFFF << nBits) + 1;
		nV += nVt;
	}
	return nV;
}

uint8* CJPEG::HuffGenerateSizeTable(HUFFMANTABLE* t)
{
	unsigned int nSize = 0;
	for(unsigned int i = 0; i < 16; i++)
	{
		nSize += t->nL[i];
	}

	nSize++;
	unsigned char* pTemp = (unsigned char*)malloc(nSize);
	unsigned int k = 0;
	
	for(unsigned int i = 0; i < 16; i++)
	{
		unsigned int j = 1;
		while(j <= t->nL[i])
		{
			pTemp[k] = (i + 1);
			k++;
			j++;
		}
	}
	
	pTemp[k] = 0;
	return pTemp;
}

uint16* CJPEG::HuffGenerateCodeTable(uint8* pS)
{
	unsigned int nSize = 0;
	while(pS[nSize] != 0)
	{
		nSize++;
	}

	uint16* pTemp = (uint16*)malloc(nSize * 2);
	unsigned int k = 0;
	unsigned int nCode = 0;
	unsigned int s = pS[k];

	while(1)
	{
		while(pS[k] == s)
		{
			pTemp[k] = nCode;
			nCode++;
			k++;
		}
		if(pS[k] == 0) break;
		while(pS[k] != s)
		{
			nCode <<= 1;
			s++;
		}
	}

	return pTemp;
}

void CJPEG::HuffGenerateMinMaxTables(HUFFMANTABLE* t)
{
	memset(t->nMin, 0xFF, 16 * 2); 
	memset(t->nMax, 0xFF, 16 * 2);

	int j = 0;
	for(int i = 0; i < 16; i++)
	{
		if(t->nL[i] == 0)
		{
			t->nMax[i] = -1;
			continue;
		}
		t->nMin[i] = t->nCodeTable[j];
		j = j + t->nL[i] - 1;
		t->nMax[i] = t->nCodeTable[j];
		j++;
	}

}

void CJPEG::HuffGenerateSubTables(HUFFMANTABLE* t)
{
	uint8* pDCS = HuffGenerateSizeTable(t);

	if(t->nCodeTable != NULL)
	{
		free(t->nCodeTable);
	}

	t->nCodeTable = HuffGenerateCodeTable(pDCS);
	HuffGenerateMinMaxTables(t);
	free(pDCS);
}

unsigned int CJPEG::DecodeMCU(int nComponent, uint8* pData, int* nDC)
{
	int16 nBlock[64], nTempBlock[64];
	unsigned int i, t, s, r, z;
	int nDiff;

	i = 0;
	while(m_Frame.pCompoment[nComponent].nC != m_Scan.pComponent[i].nCs)
	{
		i++;
	}

	QUANTIZATIONTABLE* pQt	= &m_Qt[m_Frame.pCompoment[nComponent].nTq];
	HUFFMANTABLE* pACHt		= &m_ACHt[m_Scan.pComponent[i].nTdTa & 0x0F];
	HUFFMANTABLE* pDCHt		= &m_DCHt[(m_Scan.pComponent[i].nTdTa & 0xF0) >> 4];

	memset(nBlock, 0, sizeof(int16) * 64);

	i = HuffDecode(pDCHt);
	nDiff = HuffReceive(i);
	nDiff = HuffExtend(nDiff, i);

	*nDC += nDiff;
	nBlock[0] = *nDC;

	for(i = 1; i < 64; i++)
	{
		t = HuffDecode(pACHt);
		s = t % 16;
		r = t >> 4;
		if(s == 0)
		{
			if(r == 15)
			{
				i += 16 - 1;
			}
			else
			{
				break;
			}
		}
		else
		{
			i += r;
		}
		z = HuffReceive(s);
		z = HuffExtend(z, s);
		if(i < 0x40)
		{
			nBlock[i] = (signed)z;
		}
		else
		{
			assert(0);
			//nBlock[i] = 0;
		}
	}

	//Dequantize
	for(i = 0; i < 64; i++)
	{
		nBlock[i] *= ((int8*)pQt->pQ)[i];
	}

	//Un-ZigZag
	for(i = 0; i < 64; i++)
	{
		nTempBlock[m_nZigZag[i]] = nBlock[i];
	}
	memcpy(nBlock, nTempBlock, sizeof(short) * 64);
	
	m_pIDCT->Transform(nBlock, nTempBlock);

	for(i = 0; i < 64; i++)
	{
		if(nTempBlock[i] > 127)
		{
			nTempBlock[i] = 127;
		}
		if(nTempBlock[i] < -128)
		{
			nTempBlock[i] = -128;
		}
		pData[i] = ((uint8)nTempBlock[i]) - 128;
	}

	return 1;
}

uint8 CJPEG::FixRange(double nNumber)
{
	if(nNumber < 0)
	{
		return 0x00;
	}

	if(nNumber > 255)
	{
		return 0xFF;
	}

	return (uint8)nNumber;
}

void CJPEG::Draw8x8Block(unsigned int nX, unsigned int nY, uint8 *pReMap, uint8* pY, uint8* pCr, uint8* pCb)
{
	uint32* pImage = reinterpret_cast<uint32*>(m_bitmap.GetPixels());

	for(unsigned int y = 0; y < 8; y++)
	{
		for(unsigned int x = 0; x < 8; x++)
		{
			double nYT  = pY[(y * 8) + x];
			double nCrT = pCr[pReMap[(y * 8) + x]];
			double nCbT = pCb[pReMap[(y * 8) + x]];
			
			//R = Y                    + 1.402  *(Cr-128)
			//G = Y - 0.34414*(Cb-128) - 0.71414*(Cr-128)
			//B = Y + 1.772  *(Cb-128)
			
			uint8 nR = FixRange(nYT +                           1.402   * (nCrT - 128));
			uint8 nG = FixRange(nYT - 0.344114 * (nCbT - 128) - 0.71414 * (nCrT - 128));
			uint8 nB = FixRange(nYT + 1.772    * (nCbT - 128));

			unsigned int xofs = (nX + x);
			unsigned int yofs = (nY + y);
			if(xofs >= m_Frame.nCX) continue;
			if(yofs >= m_Frame.nCY) continue;

			pImage[(yofs * m_Frame.nCX) + xofs] = 0xFF000000 | (nB << 16) | (nG << 8) | (nR);
		}
	}
}

unsigned int CJPEG::Decode()
{
	uint8 nY[256], nCb[64], nCr[64];
	uint8 nReMap[256];
	uint8 nTab1[64], nTab2[64], nTab3[64], nTab4[64];
	uint8 nSampX, nBX;
	uint8 nSampY, nBY;
	unsigned int i, j;
	unsigned int nCX, nCY;
	int nYDC, nCrDC, nCbDC;

	m_nHuffSkipNext = false;

	//Validate some stuff
	if(m_Frame.nType != 0xFFC0)
	{
		return JERROR_NOTBASELINE;
	}
	if(m_Frame.nComponents != 3 && m_Scan.nComponents != 3)
	{
		return JERROR_NOT3CHANNELS;
	}
	
	//Y is always 0?
	nSampX = m_Frame.pCompoment[0].nHV & 0x0F;
	nSampY = m_Frame.pCompoment[0].nHV >> 4;
	if(nSampX == 1 && nSampY == 2)
	{
		return JERROR_UNSUPPORTED_YSCALING;
	}
	if(nSampX == 2 && nSampY == 1)
	{
		return JERROR_UNSUPPORTED_YSCALING;
	}

	m_bitmap = CBitmap(m_Frame.nCX, m_Frame.nCY, 32);

	//Allocate some space for the components
	nCX = ((m_Frame.nCX + 15) / 16) * 16;
	nCY = ((m_Frame.nCY + 15) / 16) * 16;

	nBX = nCX / (8 * nSampX);
	nBY = nCY / (8 * nSampY);

	//TODO: Figure that out...
	for(i = 0; i < 16; i++)
	{
		for(j = 0; j < 16; j++)
		{
			nReMap[(i * 16) + j] = ((i / 2) * 8) + j / 2;
		}
	}

	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
			nTab1[(i * 8) + j] = nReMap[(i * 16) + j];
		}
		for(j = 8; j < 16; j++)
		{
			nTab2[(i * 8) + (j - 8)] = nReMap[(i * 16) + j];
		}
	}
	for(i = 8; i < 16; i++)
	{
		for(j = 0; j < 8; j++)
		{
			nTab3[((i - 8) * 8) + j] = nReMap[(i * 16) + j];
		}
		for(j = 8; j < 16; j++)
		{
			nTab4[((i - 8) * 8) + (j - 8)] = nReMap[(i * 16) + j];
		}
	}

	nYDC = 0;
	nCrDC = 0;
	nCbDC = 0;

	if(nSampX == 1 && nSampY == 1)
	{
		for(j = 0; j < nBY; j++)
		{
			for(i = 0; i < nBX; i++)
			{
				DecodeMCU(0,	nY,		&nYDC);
				DecodeMCU(1,	nCb,	&nCbDC);
				DecodeMCU(2,	nCr,	&nCrDC);

				Draw8x8Block((i * 8), (j * 8), nTab1, nY, nCr, nCb);
			}
		}
	}

	if(nSampX == 2 && nSampY == 2)
	{
		for(j = 0; j < nBY; j++)
		{
			for(i = 0; i < nBX; i++)
			{
				DecodeMCU(0,	nY + 0x0000,	&nYDC);
				DecodeMCU(0,	nY + 0x0040,	&nYDC);
				DecodeMCU(0,	nY + 0x0080,	&nYDC);
				DecodeMCU(0,	nY + 0x00C0,	&nYDC);

				DecodeMCU(1,	nCb,			&nCbDC);
			
				DecodeMCU(2,	nCr,			&nCrDC);

				Draw8x8Block((i * 16) + 0, (j * 16) + 0, nTab1, nY + 0x0000, nCr, nCb);
				Draw8x8Block((i * 16) + 8, (j * 16) + 0, nTab2, nY + 0x0040, nCr, nCb);
				Draw8x8Block((i * 16) + 0, (j * 16) + 8, nTab3, nY + 0x0080, nCr, nCb);
				Draw8x8Block((i * 16) + 8, (j * 16) + 8, nTab4, nY + 0x00C0, nCr, nCb);

			}
		}
	}

	return 0;
}

CBitmap CJPEG::Process()
{
	unsigned int nError = 0;
	uint16 nMarker = 0;

	while(nMarker != 0xFFD9 && nError == 0)
	{
		m_stream->SeekToByteAlign();
		nMarker = (uint16)m_stream->GetBits_MSBF(16);
		
		switch(nMarker)
		{
		case 0xFFC0:
			//SOF0 - Start of frame (Baseline DCT)
			nError = ProcessSOF0();
			break;
		case 0xFFC4:
			//DHT - Define Huffman Table
			nError = ProcessDHT();
			break;
		case 0xFFD8:
			//SOI - Start of Image
			break;
		case 0xFFD9:
			//EOI - End of Image
			//Decoding was successful
			break;
		case 0xFFDA:
			//SOS - Start of Scan
			nError = ProcessSOS();
			break;
		case 0xFFDB:
			//DQT - Define Quantization Table
			nError = ProcessDQT();
			break;
		case 0xFFE0:
		case 0xFFEC:
		case 0xFFEE:
			//APPx - Application defined x
			ProcessAPPx();
			break;
		case 0xFFFE:
			//COM - Comment
			ProcessCOM();
			break;
		default:
			nError = JERROR_UNKNMARKER;
			break;
		}
	}

	return m_bitmap;
}

unsigned int CJPEG::ProcessSOF0()
{
	uint16 nLength;
	unsigned int i;

	nLength = (uint16)m_stream->GetBits_MSBF(16);
	
	m_Frame.nType		= 0xFFC0;
	m_Frame.nPrecision	= (uint8)m_stream->GetBits_MSBF(8); 
	m_Frame.nCY			= (uint16)m_stream->GetBits_MSBF(16);
	m_Frame.nCX			= (uint16)m_stream->GetBits_MSBF(16);
	m_Frame.nComponents = (uint8)m_stream->GetBits_MSBF(8);

	if(m_Frame.pCompoment != NULL)
	{
		free(m_Frame.pCompoment);
	}

	m_Frame.pCompoment = (FRAMECOMPONENT*)malloc(sizeof(FRAMECOMPONENT) * m_Frame.nComponents);
	
	for(i = 0; i < m_Frame.nComponents; i++)
	{
		m_Frame.pCompoment[i].nC	= (uint8)m_stream->GetBits_MSBF(8);
		m_Frame.pCompoment[i].nHV	= (uint8)m_stream->GetBits_MSBF(8);
		m_Frame.pCompoment[i].nTq	= (uint8)m_stream->GetBits_MSBF(8);
	}

	return 0;
}

unsigned int CJPEG::ProcessDHT()
{
	uint16 nLength = (uint16)m_stream->GetBits_MSBF(16);
	nLength -= 2;

	while(nLength != 0)
	{
		uint8 nTemp = (uint8)m_stream->GetBits_MSBF(8);
		
		uint16 nHtDst  = nTemp & 0x0F;
		if(nHtDst > 4)
		{
			return JERROR_HTDEST_INVALID;
		}

		HUFFMANTABLE* t(nullptr);
		if(nTemp & 0x10)
		{
			t = &m_ACHt[nHtDst];
		}
		else
		{
			t = &m_DCHt[nHtDst];
		}

		for(unsigned int i = 0; i < 16; i++)
		{
			t->nL[i] = (uint8)m_stream->GetBits_MSBF(8);
		}

		for(unsigned int i = 0; i < 16; i++)
		{
			if(t->pV[i] != NULL)
			{
				free(t->pV[i]);
				t->pV[i] = NULL;
			}

			if(t->nL[i] == 0) continue;

			t->pV[i] = (uint8*)malloc(t->nL[i]);
			for(unsigned int j = 0; j < t->nL[i]; j++)
			{
				t->pV[i][j] = (uint8)m_stream->GetBits_MSBF(8);
			}

			nLength -= t->nL[i];
		}

		t->nTcTh = nTemp;
		HuffGenerateSubTables(t);
		nLength -= 17;
	}

	return 0;
}

unsigned int CJPEG::ProcessSOS()
{
	uint16 nLength;
	unsigned int i;

	nLength = (uint16)m_stream->GetBits_MSBF(16);

	m_Scan.nComponents = (uint8)m_stream->GetBits_MSBF(8);

	FREEPTR(m_Scan.pComponent);

	m_Scan.pComponent = (SCANCOMPONENT*)malloc(sizeof(SCANCOMPONENT) * m_Scan.nComponents);

	for(i = 0; i < m_Scan.nComponents; i++)
	{
		m_Scan.pComponent[i].nCs	= (uint8)m_stream->GetBits_MSBF(8);
		m_Scan.pComponent[i].nTdTa	= (uint8)m_stream->GetBits_MSBF(8);
	}

	m_Scan.nStartSpectral	= (uint8)m_stream->GetBits_MSBF(8);
	m_Scan.nEndSpectral		= (uint8)m_stream->GetBits_MSBF(8);
	m_Scan.nAhAl			= (uint8)m_stream->GetBits_MSBF(8);

	return Decode();
}

unsigned int CJPEG::ProcessDQT()
{
	uint16 nLength = (uint16)m_stream->GetBits_MSBF(16);
	nLength -= 2;

	while(nLength != 0)
	{
		uint8 nTemp8 = (uint8)m_stream->GetBits_MSBF(8);
		uint16 nQtDst = nTemp8 & 0x0F;

		if(nQtDst > 4)
		{
			return JERROR_QTDEST_INVALID;
		}

		FREEPTR(m_Qt[nQtDst].pQ);

		if(nTemp8 & 0x10)
		{
			return JERROR_QT16BITS;
		}

		m_Qt[nQtDst].pQ = (uint8*)malloc(64);

		for(unsigned int i = 0; i < 64; i++)
		{
			m_Qt[nQtDst].pQ[i] = (uint8)m_stream->GetBits_MSBF(8);
		}
		m_Qt[nQtDst].nPqTq = nTemp8;

		nLength -= 0x41;
	}
	
	return 0;
}

void CJPEG::ProcessAPPx()
{
	uint16 nLength = (uint16)m_stream->GetBits_MSBF(16);
	nLength -= 2;

	for(unsigned int i = 0; i < nLength; i++)
	{
		m_stream->GetBits_MSBF(8);
	}
}

void CJPEG::ProcessCOM()
{
	uint16 nLength;
	unsigned int i;

	nLength = (uint16)m_stream->GetBits_MSBF(16);
	nLength -= 2;

	for(i = 0; i < nLength; i++)
	{
		m_stream->GetBits_MSBF(8);
	}

/*
	uint8* pCom;
	pData->Read(&nLenght, 2);
	nLenght = SWAP16(nLenght);
	pCom = (unsigned char*)malloc(nLenght);
	pData->Read(pCom, nLenght - 2);
	//Humm...
	CJPEG::LogPrint("Comment: %s\n", pCom);
	free(pCom);
*/
}
