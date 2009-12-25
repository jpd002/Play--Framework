#ifndef _MPEG2_VLCTABLE_H_
#define _MPEG2_VLCTABLE_H_

#include "BitStream.h"

namespace MPEG2
{
	struct VLCTABLEENTRY
	{
		uint32				nCode;
		unsigned int		nCodeLength;
		uint32				nValue;
	};

	class CVLCTable
	{
	public:
		class CVLCTableException : public std::exception
		{

		};

		enum DECODE_ERROR
		{
			DECODE_ERROR_NOTENOUGHDATA = -1,
			DECODE_ERROR_SYMBOLNOTFOUND = -2,
		};

		virtual			~CVLCTable();

		int				TryPeekSymbol(Framework::CBitStream*, const VLCTABLEENTRY*&);
		int				TryGetSymbol(Framework::CBitStream*, const VLCTABLEENTRY*&);

		uint32			GetSymbol(Framework::CBitStream*);
		
	protected:
						CVLCTable(unsigned int, VLCTABLEENTRY*, unsigned int, unsigned int*);

		void			ThrowError(int);

	private:
		unsigned int	m_nMaxBits;
		VLCTABLEENTRY*	m_pTableEntry;
		unsigned int	m_nEntryCount;
		unsigned int*	m_pIndexTable;
	};

};

#endif