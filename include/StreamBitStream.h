#ifndef _STREAMBITSTREAM_H_
#define _STREAMBITSTREAM_H_

#include "Stream.h"
#include "BitStream.h"

namespace Framework
{

	class CStreamBitStream : public CBitStream
	{
	public:
						CStreamBitStream(CStream*);
		virtual			~CStreamBitStream();
		uint32			GetBits_LSBF(uint8);
		uint32			GetBits_MSBF(uint8);
		uint32			PeekBits_LSBF(uint8);
		uint32			PeekBits_MSBF(uint8);
		void			SeekToByteAlign();
		bool			IsOnByteBoundary();

	protected:
		enum BUFFERSIZE
		{
			BUFFERSIZE = 8,
		};

		virtual void	SkipBits(uint8);

		CStream*		m_pStream;
		uint8			m_nPointer;
		uint8			m_nBuffer[BUFFERSIZE];
	};

}

#endif
