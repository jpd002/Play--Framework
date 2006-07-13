#include <string.h>
#include "mpeg2/CodedBlockPatternTable.h"

using namespace MPEG2;

VLCTABLEENTRY CCodedBlockPatternTable::m_pTable[ENTRYCOUNT] =
{
	{ 0x0007,		3,			60	},
	{ 0x000D,		4,			4	},
	{ 0x000C,		4,			8	},
	{ 0x000B,		4,			16	},
	{ 0x000A,		4,			32	},
	{ 0x0013,		5,			12	},
	{ 0x0012,		5,			48	},
	{ 0x0011,		5,			20	},
	{ 0x0010,		5,			40	},
	{ 0x000F,		5,			28	},
	{ 0x000E,		5,			44	},
	{ 0x000D,		5,			52	},
	{ 0x000C,		5,			56	},
	{ 0x000B,		5,			1	},
	{ 0x000A,		5,			61	},
	{ 0x0009,		5,			2	},
	{ 0x0008,		5,			62	},
	{ 0x000F,		6,			24	},
	{ 0x000E,		6,			36	},
	{ 0x000D,		6,			3	},
	{ 0x000C,		6,			63	},
	{ 0x0017,		7,			5	},
	{ 0x0016,		7,			9	},
	{ 0x0015,		7,			17	},
	{ 0x0014,		7,			33	},
	{ 0x0013,		7,			6	},
	{ 0x0012,		7,			10	},
	{ 0x0011,		7,			18	},
	{ 0x0010,		7,			34	},
	{ 0x001F,		8,			7	},
	{ 0x001E,		8,			11	},
	{ 0x001D,		8,			19	},
	{ 0x001C,		8,			35	},
	{ 0x001B,		8,			13	},
	{ 0x001A,		8,			49	},
	{ 0x0019,		8,			21	},
	{ 0x0018,		8,			41	},
	{ 0x0017,		8,			14	},
	{ 0x0016,		8,			50	},
	{ 0x0015,		8,			22	},
	{ 0x0014,		8,			42	},
	{ 0x0013,		8,			15	},
	{ 0x0012,		8,			51	},
	{ 0x0011,		8,			23	},
	{ 0x0010,		8,			43	},
	{ 0x000F,		8,			25	},
	{ 0x000E,		8,			37	},
	{ 0x000D,		8,			26	},
	{ 0x000C,		8,			38	},
	{ 0x000B,		8,			29	},
	{ 0x000A,		8,			45	},
	{ 0x0009,		8,			53	},
	{ 0x0008,		8,			57	},
	{ 0x0007,		8,			30	},
	{ 0x0006,		8,			46	},
	{ 0x0005,		8,			54	},
	{ 0x0004,		8,			58	},
	{ 0x0007,		9,			31	},
	{ 0x0006,		9,			47	},
	{ 0x0005,		9,			55	},
	{ 0x0004,		9,			59	},
	{ 0x0003,		9,			27	},
	{ 0x0002,		9,			39	},
	{ 0x0001,		9,			0	},
};

unsigned int CCodedBlockPatternTable::m_pIndexTable[MAXBITS] =
{
	0,
	0,
	0,
	1,
	5,
	17,
	21,
	29,
	57,
};

CVLCTable* CCodedBlockPatternTable::m_pInstance = NULL;

CCodedBlockPatternTable::CCodedBlockPatternTable() :
CVLCTable(MAXBITS, m_pTable, ENTRYCOUNT, m_pIndexTable)
{

}

CVLCTable* CCodedBlockPatternTable::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CCodedBlockPatternTable();
	}

	return m_pInstance;
}
