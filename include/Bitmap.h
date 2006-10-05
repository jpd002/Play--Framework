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
		unsigned int	GetPixelsSize();
		unsigned int	GetWidth();
		unsigned int	GetHeight();
		unsigned int	GetBitsPerPixel();
		uint8*			GetPixels();

	private:
		unsigned int	m_nWidth;
		unsigned int	m_nHeight;
		unsigned int	m_nBPP;
		uint8*			m_pPixels;
	};

}

#endif
