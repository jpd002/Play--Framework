#ifndef _MPEG2_DCTCOEFFTABLE1_H_
#define _MPEG2_DCTCOEFFTABLE1_H_

#include "mpeg2/VLCTable.h"
#include "mpeg2/DctCoefficientTable.h"

namespace MPEG2
{
	class CDctCoefficientTable1 : protected CVLCTable, public CDctCoefficientTable
	{
	public:
										CDctCoefficientTable1();
		static CDctCoefficientTable1*	GetInstance();

		enum MAXBITS
		{
			MAXBITS = 16,
		};

		enum ENTRYCOUNT
		{
			ENTRYCOUNT = 112,
		};

		void							GetRunLevelPair(Framework::CBitStream*, RUNLEVELPAIR*, bool);
		void							GetRunLevelPairDc(Framework::CBitStream*, RUNLEVELPAIR*, bool);
		bool							IsEndOfBlock(Framework::CBitStream*);
		void							SkipEndOfBlock(Framework::CBitStream*);

	private:
		static RUNLEVELPAIR				m_pRunLevelTable[ENTRYCOUNT];
		static VLCTABLEENTRY			m_pVLCTable[ENTRYCOUNT];
		static unsigned int				m_pIndexTable[MAXBITS];
		static CDctCoefficientTable1*	m_pInstance;
	};
};

#endif
