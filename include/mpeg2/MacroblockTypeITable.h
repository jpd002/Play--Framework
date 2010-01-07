#ifndef _MPEG2_MACROBLOCKTYPEITABLE_H_
#define _MPEG2_MACROBLOCKTYPEITABLE_H_

#include "mpeg2/VLCTable.h"

namespace MPEG2
{
	
	class CMacroblockTypeITable : public MPEG2::CVLCTable
	{
	public:
									CMacroblockTypeITable();
		static MPEG2::CVLCTable*	GetInstance();

		enum MAXBITS
		{
			MAXBITS = 2,
		};

		enum ENTRYCOUNT
		{
			ENTRYCOUNT = 2,
		};

	private:
		static MPEG2::VLCTABLEENTRY	m_pTable[ENTRYCOUNT];
		static unsigned int			m_pIndexTable[MAXBITS];
		static MPEG2::CVLCTable*	m_pInstance;
	};

}

#endif
