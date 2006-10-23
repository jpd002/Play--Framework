#ifndef _BITMAP_H_
#define _BITMAP_H_

#include "Types.h"
#include <boost/function.hpp>

namespace Framework
{

	class CBitmap
	{
	public:
		typedef boost::function< void (CBitmap&) > ConstructionFunctionType;

						CBitmap(unsigned int, unsigned int, unsigned int);
						CBitmap(ConstructionFunctionType);
						~CBitmap();
		void			Allocate(unsigned int, unsigned int, unsigned int);
		bool			IsEmpty() const;
		unsigned int	GetPixelsSize() const;
		unsigned int	GetPitch() const;
		unsigned int	GetWidth() const;
		unsigned int	GetHeight() const;
		unsigned int	GetBitsPerPixel() const;
		uint8*			GetPixels() const;
		void			Blit(const CBitmap&, unsigned int, unsigned int);

	private:
						CBitmap(const CBitmap&) {}
		CBitmap&		operator =(const CBitmap&) {}

		unsigned int	m_nWidth;
		unsigned int	m_nHeight;
		unsigned int	m_nBPP;
		uint8*			m_pPixels;
	};

}

#endif
