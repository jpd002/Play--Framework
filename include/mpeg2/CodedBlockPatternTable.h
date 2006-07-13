#ifndef _MPEG2_CODEDBLOCKPATTERNTABLE_H_
#define _MPEG2_CODEDBLOCKPATTERNTABLE_H_

#include "mpeg2/VLCTable.h"

namespace MPEG2
{
	class CCodedBlockPatternTable : public CVLCTable
	{
	public:
								CCodedBlockPatternTable();
		static CVLCTable*		GetInstance();

		enum MAXBITS
		{
			MAXBITS = 9,
		};

		enum ENTRYCOUNT
		{
			ENTRYCOUNT = 64,
		};

	private:
		static VLCTABLEENTRY	m_pTable[ENTRYCOUNT];
		static unsigned int		m_pIndexTable[MAXBITS];
		static CVLCTable*		m_pInstance;
	};
}

#endif
