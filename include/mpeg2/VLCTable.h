#pragma once

#include "BitStream.h"

namespace MPEG2
{
	struct VLCTABLEENTRY
	{
		uint32				code;
		unsigned int		codeLength;
		uint32				value;
	};

	class CVLCTable
	{
	public:
		class CVLCTableException : public std::exception
		{

		};

		enum DECODE_STATUS
		{
			DECODE_STATUS_SUCCESS = 0,
			DECODE_STATUS_NOTENOUGHDATA = -1,
			DECODE_STATUS_SYMBOLNOTFOUND = -2,
		};

		virtual			~CVLCTable();

		DECODE_STATUS	TryPeekSymbol(Framework::CBitStream*, const VLCTABLEENTRY*&);
		DECODE_STATUS	TryGetSymbol(Framework::CBitStream*, const VLCTABLEENTRY*&);
		DECODE_STATUS	TryGetSymbol(Framework::CBitStream*, uint32&);

		uint32			GetSymbol(Framework::CBitStream*);
		
	protected:
						CVLCTable(unsigned int, VLCTABLEENTRY*, unsigned int, unsigned int*);

		void			ThrowError(DECODE_STATUS);

	private:
		unsigned int	m_maxBits;
		VLCTABLEENTRY*	m_tableEntry;
		unsigned int	m_entryCount;
		unsigned int*	m_indexTable;
	};

};
