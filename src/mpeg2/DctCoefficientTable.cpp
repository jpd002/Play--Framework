#include <assert.h>
#include "MPEG2/DctCoefficientTable.h"

using namespace Framework;
using namespace MPEG2;

uint32 CDctCoefficientTable::TryGetValueOfs(CBitStream* pStream, uint8 bits, uint8& currentBitCount)
{
	assert((currentBitCount + bits) <= 32);
	uint32 result = pStream->PeekBits_MSBF(currentBitCount + bits);
	uint32 mask = ~(0xFFFFFFFF << bits);
	result &= mask;
	currentBitCount += bits;
	return result;
}