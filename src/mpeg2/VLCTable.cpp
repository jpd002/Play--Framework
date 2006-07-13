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

uint32 CVLCTable::Decode(CBitStream* pStream)
{
	unsigned int i, j;
	uint32 nValue;
	VLCTABLEENTRY* pEntry;

	nValue = 0;
	
	for(i = 0; i < m_nMaxBits; i++)
	{
		nValue <<= 1;
		nValue |= pStream->GetBits_MSBF(1);

		for(j = m_pIndexTable[i]; j < m_nEntryCount; j++)
		{
			pEntry = &m_pTableEntry[j];
			
			if(pEntry->nCodeLength != (i + 1)) break;
			if(pEntry->nCode != nValue) continue;

			return pEntry->nValue;
		}
	}

	//??
	return 0;
}
