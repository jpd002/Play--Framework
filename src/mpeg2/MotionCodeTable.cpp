#include <string.h>
#include "mpeg2/MotionCodeTable.h"

using namespace MPEG2;

VLCTABLEENTRY CMotionCodeTable::m_pTable[ENTRYCOUNT] =
{
	{ 0x0001,		1,			0x0000	},
	{ 0x0002,		3,			0x0001	},
	{ 0x0003,		3,			0xFFFF	},
	{ 0x0002,		4,			0x0002	},
	{ 0x0003,		4,			0xFFFE	},
	{ 0x0002,		5,			0x0003	},
	{ 0x0003,		5,			0xFFFD	},
	{ 0x0006,		7,			0x0004	},
	{ 0x0007,		7,			0xFFFC	},
	{ 0x000A,		8,			0x0005	},
	{ 0x000B,		8,			0xFFFB	},
	{ 0x0008,		8,			0x0006	},
	{ 0x0009,		8,			0xFFFA	},
	{ 0x0006,		8,			0x0007	},
	{ 0x0007,		8,			0xFFF9	},
	{ 0x0016,		10,			0x0008	},
	{ 0x0017,		10,			0xFFF8	},
	{ 0x0014,		10,			0x0009	},
	{ 0x0015,		10,			0xFFF7	},
	{ 0x0012,		10,			0x000A	},
	{ 0x0013,		10,			0xFFF6	},
	{ 0x0022,		11,			0x000B	},
	{ 0x0023,		11,			0xFFF5	},
	{ 0x0020,		11,			0x000C	},
	{ 0x0021,		11,			0xFFF4	},
	{ 0x001E,		11,			0x000D	},
	{ 0x001F,		11,			0xFFF3	},
	{ 0x001C,		11,			0x000E	},
	{ 0x001D,		11,			0xFFF2	},
	{ 0x001A,		11,			0x000F	},
	{ 0x001B,		11,			0xFFF1	},
	{ 0x0018,		11,			0x0010	},
	{ 0x0019,		11,			0xFFF0	},
};

unsigned int CMotionCodeTable::m_pIndexTable[MAXBITS] =
{
	0,
	1,
	1,
	3,
	5,
	7,
	7,
	9,
	15,
	15,
	21,
};

CVLCTable* CMotionCodeTable::m_pInstance = NULL;

CMotionCodeTable::CMotionCodeTable() :
CVLCTable(MAXBITS, m_pTable, ENTRYCOUNT, m_pIndexTable)
{

}

CVLCTable* CMotionCodeTable::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CMotionCodeTable();
	}

	return m_pInstance;
}
