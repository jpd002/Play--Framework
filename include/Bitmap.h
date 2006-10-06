#ifndef _BITMAP_H_
#define _BITMAP_H_

#include "Types.h"

namespace Framework
{

	class CBitmap
	{
	public:
						CBitmap(unsigned int, unsigned int, unsigned int);
						~CBitmap();
		unsigned int	GetPixelsSize() const;
		unsigned int	GetWidth() const;
		unsigned int	GetHeight() const;
		unsigned int	GetBitsPerPixel() const;
		uint8*			GetPixels() const;

	private:
		unsigned int	m_nWidth;
		unsigned int	m_nHeight;
		unsigned int	m_nBPP;
		uint8*			m_pPixels;
	};

}

#endif
