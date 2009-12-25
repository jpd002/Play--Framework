#include <assert.h>
#include "StreamBitStream.h"

using namespace Framework;

CStreamBitStream::CStreamBitStream(CStream& stream) :
m_cursor(0),
m_availableBits(0),
m_stream(stream)
{
	m_buffer[0] = m_buffer[1] = 0;
}

CStreamBitStream::~CStreamBitStream()
{

}

void CStreamBitStream::Advance(uint8 size)
{
	assert(size <= 32);
	m_cursor += size;
	m_cursor %= (BUFFER_SIZE * 8);
	assert(m_availableBits >= size);
	m_availableBits -= size;
}

uint8 CStreamBitStream::GetBitIndex() const
{
	return m_cursor & 7;
}

bool CStreamBitStream::TryPeekBits_LSBF(uint8 size, uint32& result)
{
	assert(0);
	return false;
}

bool CStreamBitStream::TryPeekBits_MSBF(uint8 size, uint32& result)
{
	result = 0;

	assert(size <= 32);
	if(size > 32)
	{
		return false;
	}

	while(size > m_availableBits)
	{
		//Fill thar buffer
		uint8 inputValue = 0;
		if(m_stream.Read(&inputValue, 1) != 1)
		{
			//Not enough bytes to proceed
			return false;
		}
		unsigned int nextByte = ((m_cursor + m_availableBits + 7) / 8) % BUFFER_SIZE;
		m_buffer[nextByte] = inputValue;
		m_availableBits += 8;
	}

	unsigned int tmpCursor = m_cursor;
	for(unsigned int i = 0; i < size; i++)
	{
		unsigned int bytePtr = (tmpCursor / 8) % BUFFER_SIZE;
		unsigned int bitIndex = 7 - (tmpCursor % 8);
		unsigned int bitValue = (m_buffer[bytePtr] >> bitIndex) & 1;
		result <<= 1;
		result |= bitValue;

		tmpCursor++;
	}

	return true;
}