#include <string.h>
#include "StreamBitStream.h"

using namespace Framework;

CStreamBitStream::CStreamBitStream(CStream* pStream)
{
	m_pStream = pStream;
	m_nPointer = 0;

	//Initialize buffer
	pStream->Read(m_nBuffer, BUFFERSIZE);
}

CStreamBitStream::~CStreamBitStream()
{

}

uint32 CStreamBitStream::GetBits_LSBF(uint8 nCount)
{
	uint32 nValue;

	nValue = PeekBits_LSBF(nCount);
	SkipBits(nCount);

	return nValue;
}

uint32 CStreamBitStream::GetBits_MSBF(uint8 nCount)
{
	uint32 nValue;

	nValue = PeekBits_MSBF(nCount);
	SkipBits(nCount);

	return nValue;
}

uint32 CStreamBitStream::PeekBits_LSBF(uint8 nCount)
{
	unsigned int i, nPointer;
	uint8 nByte, nBit;
	uint32 nTemp;

	if(nCount > 32)
	{
		nCount = 32;
	}

	nPointer = m_nPointer;
	nTemp = 0;

	for(i = 0; i < nCount; i++)
	{
		nByte	  = *(m_nBuffer + (nPointer / 8));
		nBit	  = (nByte >> (nPointer & 0x07)) & 1;
		nTemp	 |= (nBit << i);

		nPointer++;
	}

	return nTemp;
}

uint32 CStreamBitStream::PeekBits_MSBF(uint8 nCount)
{
	unsigned int i, nPointer;
	uint8 nByte, nBit;
	uint32 nTemp;

	if(nCount > 32)
	{
		nCount = 32;
	}

	nPointer = m_nPointer;
	nTemp = 0;

	for(i = 0; i < nCount; i++)
	{
		nTemp	<<= 1;
		nByte	  = *(m_nBuffer + (nPointer / 8));
		nBit	  = (nByte >> (7 - (nPointer & 7))) & 1;
		nTemp	 |= nBit;

		nPointer++;
	}

	return nTemp;
}

void CStreamBitStream::SeekToByteAlign()
{
	if((m_nPointer & 7) != 0)
	{
		SkipBits(8 - (m_nPointer & 7));
	}
}

bool CStreamBitStream::IsOnByteBoundary()
{
	return (m_nPointer & 7) == 0;
}

void CStreamBitStream::SkipBits(uint8 nCount)
{
	m_nPointer += nCount;

	while(m_nPointer >= 32)
	{
		//Discard the read bytes
		memmove(m_nBuffer, m_nBuffer + 4, BUFFERSIZE - 4);

		//Refill buffer
		m_pStream->Read(m_nBuffer + (BUFFERSIZE - 4), 4);

		m_nPointer -= 32;
	}
}
