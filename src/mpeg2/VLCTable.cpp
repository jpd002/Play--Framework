#include <assert.h>
#include "mpeg2/VLCTable.h"

using namespace MPEG2;
using namespace Framework;

CVLCTable::CVLCTable(unsigned int maxBits, VLCTABLEENTRY* tableEntry, unsigned int entryCount, unsigned int* indexTable)
: m_maxBits(maxBits)
, m_tableEntry(tableEntry)
, m_entryCount(entryCount)
, m_indexTable(indexTable)
{

}

CVLCTable::~CVLCTable()
{

}

CVLCTable::DECODE_STATUS CVLCTable::TryPeekSymbol(CBitStream* stream, const VLCTABLEENTRY*& result)
{
	result = NULL;

	for(unsigned int i = 0; i < m_maxBits; i++)
	{
		uint32 value = 0;
		if(!stream->TryPeekBits_MSBF(i + 1, value))
		{
			return DECODE_STATUS_NOTENOUGHDATA;
		}

		for(unsigned int j = m_indexTable[i]; j < m_entryCount; j++)
		{
			auto entry = &m_tableEntry[j];
			
			if(entry->codeLength != (i + 1)) break;
			if(entry->code != value) continue;

			result = entry;

			return DECODE_STATUS_SUCCESS;
		}
	}

	return DECODE_STATUS_SYMBOLNOTFOUND;
}

CVLCTable::DECODE_STATUS CVLCTable::TryGetSymbol(CBitStream* stream, const VLCTABLEENTRY*& result)
{
	auto opResult = TryPeekSymbol(stream, result);
	if(opResult == DECODE_STATUS_SUCCESS)
	{
		stream->Advance(result->codeLength);
	}
	return opResult;
}

CVLCTable::DECODE_STATUS CVLCTable::TryGetSymbol(CBitStream* stream, uint32& result)
{
	const VLCTABLEENTRY* tableEntry(nullptr);
	auto opResult = TryPeekSymbol(stream, tableEntry);
	if(opResult == DECODE_STATUS_SUCCESS)
	{
		stream->Advance(tableEntry->codeLength);
		result = tableEntry->value;
	}
	return opResult;
}

uint32 CVLCTable::GetSymbol(CBitStream* stream)
{
	const VLCTABLEENTRY* tableEntry = NULL;
	auto result = TryGetSymbol(stream, tableEntry);
	if(result != DECODE_STATUS_SUCCESS)
	{
		ThrowError(result);
	}
	return tableEntry->value;
}

void CVLCTable::ThrowError(DECODE_STATUS errorCode)
{
	assert(errorCode != DECODE_STATUS_SUCCESS);
	if(errorCode == DECODE_STATUS_NOTENOUGHDATA)
	{
		throw CBitStream::CBitStreamException();
	}
	else if(errorCode == DECODE_STATUS_SYMBOLNOTFOUND)
	{
		throw CVLCTableException();
	}
	else
	{
		assert(0);
	}
}
