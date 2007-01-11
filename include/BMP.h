#ifndef _BMP_H_
#define _BMP_H_

#include "Stream.h"
#include "Bitmap.h"

namespace Framework
{

	class CBMP
	{
	public:
		static void		ToBMP(CBitmap*, CStream*);
		static void		FromBMP(CBitmap&, CStream&);

	private:
#pragma pack(push, 1)
		struct HEADER
		{
			uint16		nID;
			uint32		nFileSize;
			uint32		nReserved;
			uint32		nDataOffset;
			uint32		nHeaderSize;
			uint32		nWidth;
			uint32		nHeight;
			uint16		nPlanes;
			uint16		nBPP;
			uint32		nCompression;
			uint32		nDataSize;
			uint32		nHorzResolution;
			uint32		nVertResolution;
			uint32		nColors;
			uint32		nImportantColors;
		};
#pragma pack(pop)
	};

}

#endif
