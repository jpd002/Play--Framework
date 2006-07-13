#ifndef _MPEG2_DCSIZELUMINANCETABLE_H_
#define _MPEG2_DCSIZELUMINANCETABLE_H_

#include "mpeg2/VLCTable.h"

namespace MPEG2
{
	class CDcSizeLuminanceTable : public CVLCTable
	{
	public:
								CDcSizeLuminanceTable();
		static CVLCTable*		GetInstance();

		enum MAXBITS
		{
			MAXBITS = 9,
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
