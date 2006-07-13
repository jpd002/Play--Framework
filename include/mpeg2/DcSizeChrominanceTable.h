#ifndef _MPEG2_DCSIZECHROMINANCETABLE_H_
#define _MPEG2_DCSIZECHROMINANCETABLE_H_

#include "mpeg2/VLCTable.h"

namespace MPEG2
{
	class CDcSizeChrominanceTable : public CVLCTable
	{
	public:
								CDcSizeChrominanceTable();
		static CVLCTable*		GetInstance();

		enum MAXBITS
		{
			MAXBITS = 10,
		};

		enum ENTRYCOUNT
		{
			ENTRYCOUNT = 12,
		};

	private:
		static VLCTABLEENTRY	m_pTable[ENTRYCOUNT];
		static unsigned int		m_pIndexTable[MAXBITS];
		static CVLCTable*		m_pInstance;
	};
};

#endif
