#include <stdlib.h>
#include <assert.h>
#include <stdexcept>
#include "PtrMacro.h"
#include "Bitmap.h"

using namespace Framework;

CBitmap::CBitmap(unsigned int nWidth, unsigned int nHeight, unsigned int nBPP)
{
	m_pPixels	= NULL;
	m_nWidth	= 0;
	m_nHeight	= 0;
	m_nBPP		= 0;
	Allocate(nWidth, nHeight, nBPP);
}

CBitmap::CBitmap(const ConstructionFunctionType& ConstructionFunction)
{
	m_pPixels = NULL;
	ConstructionFunction(*this);
}

CBitmap::~CBitmap()
{
	FREEPTR(m_pPixels);
}

CBitmap& CBitmap::operator =(const CBitmap& Src)
{
	if(&Src == this)
	{
		return (*this);
	}

	if(Src.GetPixelsSize() != GetPixelsSize())
	{
		m_pPixels = reinterpret_cast<uint8*>(realloc(m_pPixels, Src.GetPixelsSize()));
	}

	m_nWidth	= Src.GetWidth();
	m_nHeight	= Src.GetHeight();
	m_nBPP		= Src.GetBitsPerPixel();

	memcpy(m_pPixels, Src.GetPixels(), GetPixelsSize());

	return (*this);
}

void CBitmap::Allocate(unsigned int nWidth, unsigned int nHeight, unsigned int nBPP)
{
	assert(m_pPixels == NULL);

	m_nWidth	= nWidth;
	m_nHeight	= nHeight;
	m_nBPP		= nBPP;
	m_pPixels	= reinterpret_cast<uint8*>(malloc(GetPixelsSize()));
}

bool CBitmap::IsEmpty() const
{
	return m_pPixels == NULL;
}

uint8* CBitmap::GetPixels() const
{
	assert(m_pPixels != NULL);
	return m_pPixels;
}

CColor CBitmap::GetPixel(unsigned int x, unsigned int y) const
{
	if(m_pPixels == NULL)
	{
		return CColor(0, 0, 0, 0);
	}

	if(x > m_nWidth) return CColor(0, 0, 0, 0);
	if(y > m_nHeight) return CColor(0, 0, 0, 0);

	uint8* pixelPtr = (m_pPixels + (GetPitch() * y) + (GetPixelSize() * x));
	switch(m_nBPP)
	{
	case 32:
		return CColor(pixelPtr[0], pixelPtr[1], pixelPtr[2], pixelPtr[3]);
		break;
	case 24:
		return CColor(pixelPtr[0], pixelPtr[1], pixelPtr[2], 0);
		break;
	default:
		throw std::runtime_error("Unknown bit depth.");
		break;
	}
}

unsigned int CBitmap::GetWidth() const
{
	return m_nWidth;
}

unsigned int CBitmap::GetHeight() const
{
	return m_nHeight;
}

unsigned int CBitmap::GetBitsPerPixel() const
{
	return m_nBPP;
}

unsigned int CBitmap::GetPixelSize() const
{
	return (m_nBPP + 7) / 8;
}

unsigned int CBitmap::GetPixelsSize() const
{
	unsigned int nSize = m_nWidth * m_nHeight * m_nBPP;
	return ((nSize + 7) / 8);
}

unsigned int CBitmap::GetPitch() const
{
	return (((m_nWidth * m_nBPP) + 7) / 8);
}

void CBitmap::Blit(const CBitmap& Src, unsigned int nLeft, unsigned int nTop)
{
	unsigned int nWidth, nHeight;
	CBitmap& Dst = (*this);

	nWidth	= Src.GetWidth();
	nHeight	= Src.GetHeight();

	if(&Dst == &Src)
	{
		throw std::exception();
	}

	if((nWidth + nLeft) > Dst.GetWidth())
	{
		throw std::exception();
	}

	if((nHeight + nTop) > Dst.GetHeight())
	{
		throw std::exception();
	}

	if(Dst.GetBitsPerPixel() != Src.GetBitsPerPixel())
	{
		throw std::exception();
	}

	size_t nSrcPitch;
	size_t nDstPitch;
	uint8* pSrcPtr;
	uint8* pDstPtr;

	nSrcPitch = Src.GetPitch();
	nDstPitch = Dst.GetPitch();
	pSrcPtr = Src.GetPixels();
	pDstPtr = Dst.GetPixels() + (nDstPitch * nTop) + (nLeft * Dst.GetBitsPerPixel() / 8);

	for(unsigned int j = 0; j < nHeight; j++)
	{
		memcpy(pDstPtr, pSrcPtr, nSrcPitch);
		pDstPtr += nDstPitch;
		pSrcPtr += nSrcPitch;
	}
}
