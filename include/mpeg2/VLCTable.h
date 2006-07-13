#ifndef _MPEG2_VLCTABLE_H_
#define _MPEG2_VLCTABLE_H_

#include "BitStream.h"

namespace MPEG2
{
	struct VLCTABLEENTRY
	{
		uint32				nCode;
		unsigned int		nCodeLength;
		uint32				nValue;
	};

	class CVLCTable
	{
	public:
		virtual			~CVLCTable();
		uint32			Decode(Framework::CBitStream*);

	protected:
						CVLCTable(unsigned int, VLCTABLEENTRY*, unsigned int, unsigned int*);

	private:
		unsigned int	m_nMaxBits;
		VLCTABLEENTRY*	m_pTableEntry;
		unsigned int	m_nEntryCount;
		unsigned int*	m_pIndexTable;
	};

};

#endif
