#pragma once

#include "Types.h"
#include "Stream.h"
#include "Bitmap.h"

namespace Framework
{

	class CPNG
	{
	public:
		static CBitmap		ReadBitmap(CStream&);

	private:
							CPNG();
							~CPNG();

		class CIHDR
		{
		public:
			void			Unserialize(CStream&);
			unsigned int	GetSamplesPerPixel();
			unsigned int	CalculateNeededBufferSize();

			uint32			m_nWidth;
			uint32			m_nHeight;
			uint8			m_nDepth;
			uint8			m_nColorType;
			uint8			m_nCompression;
			uint8			m_nFilter;
			uint8			m_nInterlace;
		};

		CBitmap				DoRead(CStream&);
		void				UncompressIDAT();
		void				SubFilter(uint8*, int, unsigned int, unsigned int);
		void				UpFilter(uint8*, int, unsigned int, unsigned int);
		void				AverageFilter(uint8*, int, unsigned int, unsigned int);
		void				PaethFilter(uint8*, int, unsigned int, unsigned int);
		uint8				PaethPredictor(uint8, uint8, uint8);
		CBitmap				CreateBitmap();
		CBitmap				ConvertTo32(const CBitmap&) const;

		CIHDR				m_IHDR;
		uint8				m_nPalette[0x300];
		uint8*				m_pBuffer;
		uint8*				m_pIDAT;
		unsigned int		m_nIDATSize;
	};

}
