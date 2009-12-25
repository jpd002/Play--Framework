#ifndef _STREAMBITSTREAM_H_
#define _STREAMBITSTREAM_H_

#include <stdexcept>
#include "Types.h"
#include "Stream.h"
#include "BitStream.h"

namespace Framework
{
	class CStreamBitStream : public CBitStream
	{
	public:

								CStreamBitStream(Framework::CStream&);
		virtual					~CStreamBitStream();

		virtual void			Advance(uint8);
		virtual uint8			GetBitIndex() const;

		virtual bool			TryPeekBits_LSBF(uint8, uint32&);
		virtual bool			TryPeekBits_MSBF(uint8, uint32&);

	private:
		enum
		{
			BUFFER_SIZE = 16,
		};

		uint8					m_buffer[BUFFER_SIZE];
		unsigned int			m_cursor;
		unsigned int			m_availableBits;

		Framework::CStream&		m_stream;
	};
}

#endif