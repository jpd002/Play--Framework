#include <stdlib.h>
#include <assert.h>
#include <stdexcept>
#include <string.h>
#include <algorithm>
#include <cmath>
#include "bitmap/Bitmap.h"

using namespace Framework;

CBitmap::CBitmap(const CBitmap& src)
{
	CopyFrom(src);
}

CBitmap::CBitmap(CBitmap&& src)
{
	MoveFrom(std::move(src));
}

CBitmap::CBitmap(unsigned int nWidth, unsigned int nHeight, unsigned int nBPP)
{
	Allocate(nWidth, nHeight, nBPP);
}

CBitmap::~CBitmap()
{
	Reset();
}

CBitmap& CBitmap::operator =(const CBitmap& src)
{
	if(&src == this)
	{
		return (*this);
	}

	CopyFrom(src);

	return (*this);
}

CBitmap& CBitmap::operator =(CBitmap&& src)
{
	Reset();
	MoveFrom(std::move(src));
	return (*this);
}

void CBitmap::Allocate(unsigned int width, unsigned int height, unsigned int bpp)
{
	assert(m_pixels == nullptr);

	m_width		= width;
	m_height	= height;
	m_bpp		= bpp;
	m_pixels	= new uint8[GetPixelsSize()];
}

void CBitmap::Reset()
{
	delete [] m_pixels;
	m_pixels = nullptr;

	m_width = 0;
	m_height = 0;
	m_bpp = 0;
}

bool CBitmap::IsEmpty() const
{
	return m_pixels == nullptr;
}

uint8* CBitmap::GetPixels() const
{
	assert(m_pixels != nullptr);
	return m_pixels;
}

CColor CBitmap::GetPixel(unsigned int x, unsigned int y) const
{
	if(m_pixels == nullptr)
	{
		return CColor(0, 0, 0, 0);
	}

	if(x > m_width) return CColor(0, 0, 0, 0);
	if(y > m_height) return CColor(0, 0, 0, 0);

	uint8* pixelPtr = (m_pixels + (GetPitch() * y) + (GetPixelSize() * x));
	switch(m_bpp)
	{
	case 8:
		return CColor(pixelPtr[0], 0, 0, 0);
		break;
	case 24:
		return CColor(pixelPtr[0], pixelPtr[1], pixelPtr[2], 0);
		break;
	case 32:
		return CColor(pixelPtr[0], pixelPtr[1], pixelPtr[2], pixelPtr[3]);
		break;
	default:
		throw std::runtime_error("Unknown bit depth.");
		break;
	}
}

void CBitmap::SetPixel(unsigned int x, unsigned int y, const CColor& color)
{
	if(m_pixels == nullptr)
	{
		return;
	}

	if(x > m_width) return;
	if(y > m_height) return;

	uint8* pixelPtr = (m_pixels + (GetPitch() * y) + (GetPixelSize() * x));
	switch(m_bpp)
	{
	case 8:
		pixelPtr[0] = color.r;
		break;
	case 24:
		pixelPtr[0] = color.r;
		pixelPtr[1] = color.g;
		pixelPtr[2] = color.b;
		break;
	case 32:
		pixelPtr[0] = color.r;
		pixelPtr[1] = color.g;
		pixelPtr[2] = color.b;
		pixelPtr[3] = color.a;
		break;
	default:
		throw std::runtime_error("Unknown bit depth.");
		break;
	}
}

unsigned int CBitmap::GetWidth() const
{
	return m_width;
}

unsigned int CBitmap::GetHeight() const
{
	return m_height;
}

unsigned int CBitmap::GetBitsPerPixel() const
{
	return m_bpp;
}

unsigned int CBitmap::GetPixelSize() const
{
	return (m_bpp + 7) / 8;
}

unsigned int CBitmap::GetPixelsSize() const
{
	unsigned int nSize = m_width * m_height * m_bpp;
	return ((nSize + 7) / 8);
}

unsigned int CBitmap::GetPitch() const
{
	return (((m_width * m_bpp) + 7) / 8);
}

void CBitmap::Blit(const CBitmap& Src, unsigned int nLeft, unsigned int nTop)
{
	CBitmap& Dst = (*this);

	unsigned int nWidth		= Src.GetWidth();
	unsigned int nHeight	= Src.GetHeight();

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

	size_t nSrcPitch = Src.GetPitch();
	size_t nDstPitch = Dst.GetPitch();
	uint8* pSrcPtr = Src.GetPixels();
	uint8* pDstPtr = Dst.GetPixels() + (nDstPitch * nTop) + (nLeft * Dst.GetBitsPerPixel() / 8);

	for(unsigned int j = 0; j < nHeight; j++)
	{
		memcpy(pDstPtr, pSrcPtr, nSrcPitch);
		pDstPtr += nDstPitch;
		pSrcPtr += nSrcPitch;
	}
}

CBitmap CBitmap::AddAlphaChannel(uint8 alphaValue) const
{
	assert(m_bpp == 24);
	CBitmap result(m_width, m_height, 32);

	uint32 pixelCount = m_width * m_height;
	for(uint32 i = 0; i < pixelCount; i++)
	{
		result.m_pixels[(i * 4) + 0] = m_pixels[(i * 3) + 0];
		result.m_pixels[(i * 4) + 1] = m_pixels[(i * 3) + 1];
		result.m_pixels[(i * 4) + 2] = m_pixels[(i * 3) + 2];
		result.m_pixels[(i * 4) + 3] = alphaValue;
	}

	return result;
}

CBitmap CBitmap::Resize(unsigned int newWidth, unsigned int newHeight) const
{
	if(IsEmpty()) return CBitmap();

	CBitmap result(newWidth, newHeight, m_bpp);

	unsigned int srcPitch = GetPitch();
	unsigned int dstPitch = result.GetPitch();
	unsigned int pixelSize = GetPixelSize();

	auto dstPtr = result.m_pixels;
	for(unsigned int y = 0; y < newHeight; y++)
	{
		unsigned int sampleY = (y * m_height) / newHeight;
		for(unsigned int x = 0; x < newWidth; x++)
		{
			unsigned int sampleX = (x * m_width) / newWidth;

			for(unsigned int i = 0; i < pixelSize; i++)
			{
				uint8 pixelSrc = m_pixels[(sampleX * pixelSize) + (sampleY * srcPitch) + i];
				dstPtr[(x * pixelSize) + i] = pixelSrc;
			}
		}
		dstPtr += dstPitch;
	}

	return result;
}

CBitmap CBitmap::ResizeCanvas(unsigned int newWidth, unsigned int newHeight) const
{
	if(IsEmpty()) return CBitmap();

	CBitmap result(newWidth, newHeight, m_bpp);

	unsigned int srcPitch = GetPitch();
	unsigned int dstPitch = result.GetPitch();
	unsigned int copyPitch = std::min<unsigned int>(srcPitch, dstPitch);
	unsigned int copyHeight = std::min<unsigned int>(newHeight, m_height);

	auto srcPtr = m_pixels;
	auto dstPtr = result.m_pixels;
	for(unsigned int y = 0; y < copyHeight; y++)
	{
		memcpy(dstPtr, srcPtr, copyPitch);
		srcPtr += srcPitch;
		dstPtr += dstPitch;
	}

	return result;
}

void CBitmap::DrawLine(int x1, int y1, int x2, int y2, const CColor& color)
{
	uint32 convertedColor = (color.r << 0) | (color.g << 8) | (color.b << 16) | (color.a << 24);

	assert(m_bpp == 32);

	if((x1 < 0) && (x2 < 0)) return;
	if((x1 >= m_width) && (x2 >= m_width)) return;

	if((y1 < 0) && (y2 < 0)) return;
	if((y1 >= m_height) && (y2 >= m_height)) return;

	int dx = x2 - x1;
	int dy = y2 - y1;

	if((dx == 0) && (dy == 0)) return;

	float error = 0;

	if(abs(dy) < abs(dx))
	{
		float deltaErr = fabs(static_cast<float>(dy) / static_cast<float>(dx));
		if(x1 > x2) 
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
			dy = -dy;
		}
		int y = y1;
		for(int x = x1; x <= x2; x++)
		{
			if(
				(x >= 0) && (x < m_width) &&
				(y >= 0) && (y < m_height)
				)
			{
				reinterpret_cast<uint32*>(m_pixels)[x + (y * m_width)] = convertedColor;
			}
			error = error + deltaErr;
			if(error >= 0.5)
			{
				y += (dy >= 0) ? 1 : -1;
				error -= 1.0f;
			}
		}
	}
	else
	{
		float deltaErr = fabs(static_cast<float>(dx) / static_cast<float>(dy));
		if(y1 > y2) 
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
			dx = -dx;
		}
		int x = x1;
		for(int y = y1; y <= y2; y++)
		{
			if(
				(x >= 0) && (x < m_width) &&
				(y >= 0) && (y < m_height)
				)
			{
				reinterpret_cast<uint32*>(m_pixels)[x + (y * m_width)] = convertedColor;
			}
			error = error + deltaErr;
			if(error >= 0.5)
			{
				x += (dx >= 0) ? 1 : -1;
				error -= 1.0f;
			}
		}
	}
}

void CBitmap::CopyFrom(const CBitmap& src)
{
	if(src.GetPixelsSize() != GetPixelsSize())
	{
		m_pixels = reinterpret_cast<uint8*>(realloc(m_pixels, src.GetPixelsSize()));
	}

	m_width		= src.GetWidth();
	m_height	= src.GetHeight();
	m_bpp		= src.GetBitsPerPixel();

	if(GetPixelsSize() != 0)
	{
		memcpy(m_pixels, src.GetPixels(), GetPixelsSize());
	}
}

void CBitmap::MoveFrom(CBitmap&& src)
{
	std::swap(src.m_pixels, m_pixels);
	std::swap(src.m_width,  m_width);
	std::swap(src.m_height, m_height);
	std::swap(src.m_bpp,    m_bpp);
}
