#include "BitStream.h"

using namespace Framework;

bool CBitStream::TryGetBits_LSBF(uint8 size, uint32& result)
{
	if(!TryPeekBits_LSBF(size, result)) return false;
	Advance(size);
	return true;
}

bool CBitStream::TryGetBits_MSBF(uint8 size, uint32& result)
{
	if(!TryPeekBits_MSBF(size, result)) return false;
	Advance(size);
	return true;
}

uint32 CBitStream::GetBits_LSBF(uint8 size)
{
	uint32 result = 0;
	if(!TryGetBits_LSBF(size, result))
	{
		throw CBitStreamException();
	}
	return result;
}

uint32 CBitStream::GetBits_MSBF(uint8 size)
{
	uint32 result = 0;
	if(!TryGetBits_MSBF(size, result))
	{
		throw CBitStreamException();
	}
	return result;
}

uint32 CBitStream::PeekBits_LSBF(uint8 size)
{
	uint32 result = 0;
	if(!TryPeekBits_LSBF(size, result))
	{
		throw CBitStreamException();
	}
	return result;
}

uint32 CBitStream::PeekBits_MSBF(uint8 size)
{
	uint32 result = 0;
	if(!TryPeekBits_MSBF(size, result))
	{
		throw CBitStreamException();
	}
	return result;
}

void CBitStream::SeekToByteAlign()
{
	unsigned int remainder = GetBitIndex() & 0x07;
	if(remainder == 0) return;
	Advance(8 - remainder);
}

bool CBitStream::IsOnByteBoundary() const
{
	return (GetBitIndex() == 0);
}