#include <malloc.h>
#include "PtrMacro.h"
#include "Bitmap.h"

using namespace Framework;

CBitmap::CBitmap(unsigned int nWidth, unsigned int nHeight, unsigned int nBPP)
{
	m_nWidth	= nWidth;
	m_nHeight	= nHeight;
	m_nBPP		= nBPP;
	m_pPixels	= reinterpret_cast<uint8*>(malloc(GetPixelsSize()));
}

CBitmap::~CBitmap()
{
	FREEPTR(m_pPixels);
}

uint8* CBitmap::GetPixels() const
{
	return m_pPixels;
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

unsigned int CBitmap::GetPixelsSize() const
{
	unsigned int nSize;
	nSize = m_nWidth * m_nHeight * m_nBPP;
	return ((nSize + 7) / 8);
}
