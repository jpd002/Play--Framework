#pragma once

#include "BitStream.h"
#include "VLCTable.h"

namespace MPEG2
{
	struct RUNLEVELPAIR
	{
		unsigned int				run;
		unsigned int				level;
	};

	enum RUNSPECIAL
	{
		RUN_ESCAPE	= 102,
	};

	class CDctCoefficientTable : protected CVLCTable
	{
	public:
		virtual					~CDctCoefficientTable() {}

		virtual DECODE_STATUS	TryGetRunLevelPair(Framework::CBitStream*, RUNLEVELPAIR*, bool) = 0;
		virtual DECODE_STATUS	TryGetRunLevelPairDc(Framework::CBitStream*, RUNLEVELPAIR*, bool) = 0;

		virtual DECODE_STATUS	TryIsEndOfBlock(Framework::CBitStream*, bool&) = 0;
		virtual DECODE_STATUS	TrySkipEndOfBlock(Framework::CBitStream*) = 0;

		void					GetRunLevelPair(Framework::CBitStream*, RUNLEVELPAIR*, bool);
		void					GetRunLevelPairDc(Framework::CBitStream*, RUNLEVELPAIR*, bool);

		bool					IsEndOfBlock(Framework::CBitStream*);
		void					SkipEndOfBlock(Framework::CBitStream*);

	protected:
								CDctCoefficientTable(unsigned int, VLCTABLEENTRY*, unsigned int, unsigned int*);

		static bool				TryPeekValueOfs(Framework::CBitStream*, uint8, uint8&, uint32&);
	};
};
