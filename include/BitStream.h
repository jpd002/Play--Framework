#ifndef _BITSTREAM_H_
#define _BITSTREAM_H_

#include "Stream.h"

namespace Framework
{

	class CBitStream
	{
	public:
		virtual			~CBitStream() {};
		virtual uint32	GetBits_LSBF(uint8) = 0;
		virtual uint32	GetBits_MSBF(uint8) = 0;
		virtual uint32	PeekBits_LSBF(uint8) = 0;
		virtual uint32	PeekBits_MSBF(uint8) = 0;
		virtual void	SeekToByteAlign() = 0;
		virtual bool	IsOnByteBoundary() = 0;
	};

}

#endif
