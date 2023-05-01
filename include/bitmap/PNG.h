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
							~CPNG();

		class CIHDR
		{
		public:
			void			Unserialize(CStream&);
			unsigned int	GetSamplesPerPixel();
			unsigned int	CalculateNeededBufferSize();

			uint32			m_nWidth = 0;
			uint32			m_nHeight = 0;
			uint8			m_nDepth = 0;
			uint8			m_nColorType = 0;
			uint8			m_nCompression = 0;
			uint8			m_nFilter = 0;
			uint8			m_nInterlace = 0;
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
		uint8*				m_pBuffer = nullptr;
		uint8*				m_pIDAT = nullptr;
		unsigned int		m_nIDATSize = 0;
	};

}
