#pragma once

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

		virtual void			Advance(uint8) override;
		virtual uint8			GetBitIndex() const override;

		virtual bool			TryPeekBits_LSBF(uint8, uint32&) override;
		virtual bool			TryPeekBits_MSBF(uint8, uint32&) override;

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
