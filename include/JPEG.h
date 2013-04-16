#pragma once

#include "Stream.h"
#include "BitStream.h"
#include "Bitmap.h"
#include "idct/Interface.h"

namespace Framework
{
	class CJPEG
	{
	public:
		static CBitmap		ReadBitmap(CStream&);

		enum JERROR
		{
			JERROR_SUCCESS				= 0,
			JERROR_QTDEST_INVALID		= 1,
			JERROR_QT16BITS				= 2,
			JERROR_HTDEST_INVALID		= 3,
			JERROR_NOTBASELINE			= 4,
			JERROR_NOT3CHANNELS			= 5,
			JERROR_UNKNMARKER			= 6,
			JERROR_UNSUPPORTED_YSCALING	= 7,
		};

	private:

		struct QUANTIZATIONTABLE
		{
			uint8					nPqTq;
			uint8*					pQ;
		};

		struct FRAMECOMPONENT
		{
			uint8					nC;
			uint8					nHV;
			uint8					nTq;
		};

		struct FRAME
		{
			uint16					nType;
			uint8					nPrecision;
			uint16					nCY;
			uint16					nCX;
			uint8					nComponents;
			FRAMECOMPONENT*			pCompoment;
		};

		struct SCANCOMPONENT
		{
			unsigned char			nCs;
			unsigned char			nTdTa;
		};

		struct SCAN
		{
			unsigned char			nComponents;
			SCANCOMPONENT*			pComponent;
			unsigned char			nStartSpectral;
			unsigned char			nEndSpectral;
			unsigned char			nAhAl;
		};

		struct HUFFMANTABLE
		{
			uint8					nTcTh;
			uint8					nL[16];
			uint8*					pV[16];
			uint16*					nCodeTable;
			int16					nMin[16];
			int16					nMax[16];
		};
									CJPEG(Framework::CStream&);
									~CJPEG();
	
		uint8						HuffGetBit();
		uint8						HuffDecode(HUFFMANTABLE*);
		uint32						HuffReceive(unsigned int);
		uint32						HuffExtend(uint32, unsigned int);
		void						HuffGenerateSubTables(HUFFMANTABLE*);
		uint8*						HuffGenerateSizeTable(HUFFMANTABLE*);
		uint16*						HuffGenerateCodeTable(uint8*);
		void						HuffGenerateMinMaxTables(HUFFMANTABLE*);

		unsigned int				Decode();
		unsigned int				DecodeMCU(int, uint8*, int*);
		void						Draw8x8Block(unsigned int, unsigned int, uint8*, uint8*, uint8*, uint8*);
		uint8						FixRange(double);

		Framework::CBitmap			Process();
		unsigned int				ProcessSOF0();
		unsigned int				ProcessDHT();
		unsigned int				ProcessSOS();
		unsigned int				ProcessDQT();
		void						ProcessAPPx();
		void						ProcessCOM();

		QUANTIZATIONTABLE			m_Qt[4];
		FRAME						m_Frame;
		SCAN						m_Scan;
		HUFFMANTABLE				m_DCHt[4];
		HUFFMANTABLE				m_ACHt[4];

		//Static members
		static IDCT::CInterface*	m_pIDCT;
		static unsigned char		m_nZigZag[64];

		bool						m_nHuffSkipNext;

		Framework::CBitStream*		m_stream;
		Framework::CBitmap			m_bitmap;
	};
}
