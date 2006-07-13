#ifndef _MPEG2_DCTCOEFFICIENTTABLE_H_
#define _MPEG2_DCTCOEFFICIENTTABLE_H_

#include "BitStream.h"

namespace MPEG2
{
	struct RUNLEVELPAIR
	{
		unsigned int				nRun;
		unsigned int				nLevel;
	};

	enum RUNSPECIAL
	{
		RUN_ESCAPE	= 102,
	};

	class CDctCoefficientTable
	{
	public:
		virtual				~CDctCoefficientTable() {}
		virtual void		GetRunLevelPair(Framework::CBitStream*, RUNLEVELPAIR*, bool) = 0;
		virtual void		GetRunLevelPairDc(Framework::CBitStream*, RUNLEVELPAIR*, bool) = 0;
		virtual bool		IsEndOfBlock(Framework::CBitStream*) = 0;
		virtual void		SkipEndOfBlock(Framework::CBitStream*) = 0;
	};
};

#endif
