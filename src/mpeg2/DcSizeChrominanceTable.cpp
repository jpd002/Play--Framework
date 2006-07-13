#include <string.h>
#include "mpeg2/DcSizeChrominanceTable.h"

using namespace MPEG2;

VLCTABLEENTRY CDcSizeChrominanceTable::m_pTable[ENTRYCOUNT] =
{
	{ 0x0000,		2,			0	},
	{ 0x0001,		2,			1	},
	{ 0x0002,		2,			2	},
	{ 0x0006,		3,			3	},
	{ 0x000E,		4,			4	},
	{ 0x001E,		5,			5	},
	{ 0x003E,		6,			6	},
	{ 0x007E,		7,			7	},
	{ 0x00FE,		8,			8	},
	{ 0x01FE,		9,			9	},
	{ 0x03FE,		10,			10	},
	{ 0x03FF,		10,			11	},
};

unsigned int CDcSizeChrominanceTable::m_pIndexTable[MAXBITS] =
{
	0,
	0,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
};

CVLCTable* CDcSizeChrominanceTable::m_pInstance = NULL;

CDcSizeChrominanceTable::CDcSizeChrominanceTable() :
CVLCTable(MAXBITS, m_pTable, ENTRYCOUNT, m_pIndexTable)
{

}

CVLCTable* CDcSizeChrominanceTable::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CDcSizeChrominanceTable();
	}

	return m_pInstance;
}
