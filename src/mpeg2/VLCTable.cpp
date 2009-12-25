#include <assert.h>
#include "mpeg2/VLCTable.h"

using namespace MPEG2;
using namespace Framework;

CVLCTable::CVLCTable(unsigned int nMaxBits, VLCTABLEENTRY* pTableEntry, unsigned int nEntryCount, unsigned int* pIndexTable)
{
	m_nMaxBits		= nMaxBits;
	m_pTableEntry	= pTableEntry;
	m_nEntryCount	= nEntryCount;
	m_pIndexTable	= pIndexTable;
}

CVLCTable::~CVLCTable()
{

}

int CVLCTable::TryPeekSymbol(CBitStream* stream, const VLCTABLEENTRY*& result)
{
	result = NULL;

	for(unsigned int i = 0; i < m_nMaxBits; i++)
	{
		uint32 value = 0;
		if(!stream->TryPeekBits_MSBF(i + 1, value))
		{
			return DECODE_ERROR_NOTENOUGHDATA;
		}

		for(unsigned int j = m_pIndexTable[i]; j < m_nEntryCount; j++)
		{
			VLCTABLEENTRY* entry = &m_pTableEntry[j];
			
			if(entry->nCodeLength != (i + 1)) break;
			if(entry->nCode != value) continue;

			result = entry;

			return 0;
		}
	}

	return DECODE_ERROR_SYMBOLNOTFOUND;
}

int CVLCTable::TryGetSymbol(CBitStream* stream, const VLCTABLEENTRY*& result)
{
	int opResult = TryPeekSymbol(stream, result);
	if(opResult == 0)
	{
		stream->Advance(result->nCodeLength);
	}
	return opResult;
}

uint32 CVLCTable::GetSymbol(CBitStream* stream)
{
	const VLCTABLEENTRY* tableEntry = NULL;
	int result = TryGetSymbol(stream, tableEntry);
	if(result < 0)
	{
		ThrowError(result);
	}
	return tableEntry->nValue;
}

void CVLCTable::ThrowError(int errorCode)
{
	assert(errorCode != 0);
	if(errorCode == DECODE_ERROR_NOTENOUGHDATA)
	{
		throw CBitStream::CBitStreamException();
	}
	else if(errorCode == DECODE_ERROR_SYMBOLNOTFOUND)
	{
		throw CVLCTableException();
	}
	else
	{
		assert(0);
	}
}

//uint32 CVLCTable::Decode(CBitStream* pStream)
//{
//	uint32 nValue = 0;
//	
//	for(unsigned int i = 0; i < m_nMaxBits; i++)
//	{
//		nValue <<= 1;
//		nValue |= pStream->GetBits_LSBF(1);
//
//		for(unsigned int j = m_pIndexTable[i]; j < m_nEntryCount; j++)
//		{
//			VLCTABLEENTRY* pEntry = &m_pTableEntry[j];
//			
//			if(pEntry->nCodeLength != (i + 1)) break;
//			if(pEntry->nCode != nValue) continue;
//
//			return pEntry->nValue;
//		}
//	}
//
//	//??
//	return 0;
//}