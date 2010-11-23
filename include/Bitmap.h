#ifndef _BITMAP_H_
#define _BITMAP_H_

#include "Types.h"
#include <functional>

namespace Framework
{
	class CColor
	{
	public:
		CColor()
			: r(0), g(0), b(0), a(0)
		{
		
		}

		CColor(uint8 r, uint8 g, uint8 b, uint8 a)
			: r(r), g(g), b(b), a(a)
		{

		}

		uint8	r;
		uint8	g;
		uint8	b;
		uint8	a;
	};

	class CBitmap
	{
	public:
		typedef std::tr1::function< void (CBitmap&) > ConstructionFunctionType;

						CBitmap(unsigned int, unsigned int, unsigned int);
						CBitmap(const ConstructionFunctionType&);
						~CBitmap();

		CBitmap&		operator =(const CBitmap&);

		void			Allocate(unsigned int, unsigned int, unsigned int);
		bool			IsEmpty() const;
		unsigned int	GetPixelSize() const;
		unsigned int	GetPixelsSize() const;
		unsigned int	GetPitch() const;
		unsigned int	GetWidth() const;
		unsigned int	GetHeight() const;
		unsigned int	GetBitsPerPixel() const;
		CColor			GetPixel(unsigned int, unsigned int) const;
		uint8*			GetPixels() const;
		void			Blit(const CBitmap&, unsigned int, unsigned int);

	private:
						CBitmap(const CBitmap&) {}

		unsigned int	m_nWidth;
		unsigned int	m_nHeight;
		unsigned int	m_nBPP;
		uint8*			m_pPixels;
	};

}

#endif
