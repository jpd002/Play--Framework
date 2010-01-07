#include <string.h>
#include "mpeg2/MacroblockTypeBTable.h"

using namespace MPEG2;

VLCTABLEENTRY CMacroblockTypeBTable::m_pTable[ENTRYCOUNT] =
{
	{ 0x0002,		2,			0x000C	},
	{ 0x0003,		2,			0x000E	},
	{ 0x0002,		3,			0x0004	},
	{ 0x0003,		3,			0x0006	},
	{ 0x0002,		4,			0x0008	},
	{ 0x0003,		4,			0x000A	},
	{ 0x0003,		5,			0x0001	},
	{ 0x0002,		5,			0x001E	},
	{ 0x0003,		6,			0x001A	},
	{ 0x0002,		6,			0x0016	},
	{ 0x0001,		6,			0x0011	},
};

unsigned int CMacroblockTypeBTable::m_pIndexTable[MAXBITS] =
{
	0,
	0,
	2,
	4,
	6,
	8,
};

CVLCTable* CMacroblockTypeBTable::m_pInstance = NULL;

CMacroblockTypeBTable::CMacroblockTypeBTable() :
CVLCTable(MAXBITS, m_pTable, ENTRYCOUNT, m_pIndexTable)
{

}

CVLCTable* CMacroblockTypeBTable::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CMacroblockTypeBTable();
	}

	return m_pInstance;
}
