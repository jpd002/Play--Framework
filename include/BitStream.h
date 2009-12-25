#ifndef _BITSTREAM_H_
#define _BITSTREAM_H_

#include "Types.h"
#include <stdexcept>

namespace Framework
{
	class CBitStream
	{
	public:
		class CBitStreamException : public std::exception
		{
		public:

		private:

		};

		virtual				~CBitStream() {};

		virtual void		Advance(uint8)						= 0;
		virtual uint8		GetBitIndex() const					= 0;

		virtual bool		TryPeekBits_LSBF(uint8, uint32&)	= 0;
		virtual bool		TryPeekBits_MSBF(uint8, uint32&)	= 0;

		bool				TryGetBits_LSBF(uint8, uint32&);
		bool				TryGetBits_MSBF(uint8, uint32&);

		uint32				GetBits_LSBF(uint8);
		uint32				GetBits_MSBF(uint8);

		uint32				PeekBits_LSBF(uint8);
		uint32				PeekBits_MSBF(uint8);

		void				SeekToByteAlign();
		bool				IsOnByteBoundary() const;
	};
}

#endif