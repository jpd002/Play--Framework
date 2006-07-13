#ifndef _MPEG2_DCTCOEFFTABLE0_H_
#define _MPEG2_DCTCOEFFTABLE0_H_

#include "mpeg2/VLCTable.h"
#include "mpeg2/DctCoefficientTable.h"

namespace MPEG2
{
	class CDctCoefficientTable0 : protected CVLCTable, public CDctCoefficientTable
	{
	public:
										CDctCoefficientTable0();
		static CDctCoefficientTable0*	GetInstance();

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
		static CDctCoefficientTable0*	m_pInstance;
	};
};

#endif
