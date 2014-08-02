#pragma once

#include "Singleton.h"
#include "mpeg2/DctCoefficientTable.h"

namespace MPEG2
{
	class CDctCoefficientTable1 : public CDctCoefficientTable, public CSingleton<CDctCoefficientTable1>
	{
	public:
										CDctCoefficientTable1();

		enum MAXBITS
		{
			MAXBITS = 16,
		};

		enum ENTRYCOUNT
		{
			ENTRYCOUNT = 112,
		};

		DECODE_STATUS					TryGetRunLevelPair(Framework::CBitStream*, RUNLEVELPAIR*, bool) override;
		DECODE_STATUS					TryGetRunLevelPairDc(Framework::CBitStream*, RUNLEVELPAIR*, bool) override;

		DECODE_STATUS					TryIsEndOfBlock(Framework::CBitStream*, bool&) override;
		DECODE_STATUS					TrySkipEndOfBlock(Framework::CBitStream*) override;

	private:
		static RUNLEVELPAIR				m_runLevelTable[ENTRYCOUNT];
		static VLCTABLEENTRY			m_vlcTable[ENTRYCOUNT];
		static unsigned int				m_indexTable[MAXBITS];
	};
};
