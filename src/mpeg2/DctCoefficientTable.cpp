#include <assert.h>
#include "mpeg2/DctCoefficientTable.h"

using namespace Framework;
using namespace MPEG2;

CDctCoefficientTable::CDctCoefficientTable(unsigned int maxBits, VLCTABLEENTRY* tableEntry, unsigned int entryCount, unsigned int* indexTable)
: CVLCTable(maxBits, tableEntry, entryCount, indexTable)
{

}

void CDctCoefficientTable::GetRunLevelPair(CBitStream* stream, RUNLEVELPAIR* pairDst, bool isMpeg2)
{
	auto result = TryGetRunLevelPair(stream, pairDst, isMpeg2);
	if(result != DECODE_STATUS_SUCCESS)
	{
		ThrowError(result);
	}
}

void CDctCoefficientTable::GetRunLevelPairDc(CBitStream* stream, RUNLEVELPAIR* pairDst, bool isMpeg2)
{
	auto result = TryGetRunLevelPairDc(stream, pairDst, isMpeg2);
	if(result != DECODE_STATUS_SUCCESS)
	{
		ThrowError(result);
	}
}

bool CDctCoefficientTable::IsEndOfBlock(Framework::CBitStream* stream)
{
	bool isEob = false;
	auto result = TryIsEndOfBlock(stream, isEob);
	if(result != DECODE_STATUS_SUCCESS)
	{
		ThrowError(result);
	}
	return isEob;
}

void CDctCoefficientTable::SkipEndOfBlock(Framework::CBitStream* stream)
{
	auto result = TrySkipEndOfBlock(stream);
	if(result != DECODE_STATUS_SUCCESS)
	{
		ThrowError(result);
	}
}

bool CDctCoefficientTable::TryPeekValueOfs(CBitStream* stream, uint8 bits, uint8& currentBitCount, uint32& result)
{
	assert((currentBitCount + bits) <= 32);
	result = 0;
	if(!stream->TryPeekBits_MSBF(currentBitCount + bits, result))
	{
		return false;
	}
	uint32 mask = ~(0xFFFFFFFF << bits);
	result &= mask;
	currentBitCount += bits;
	return true;
}
