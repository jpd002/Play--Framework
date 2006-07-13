#include <string.h>
#include "mpeg2/DcSizeLuminanceTable.h"

using namespace MPEG2;

VLCTABLEENTRY CDcSizeLuminanceTable::m_pTable[ENTRYCOUNT] =
{
	{ 0x0000,		2,			1	},
	{ 0x0001,		2,			2	},
	{ 0x0004,		3,			0	},
	{ 0x0005,		3,			3	},
	{ 0x0006,		3,			4	},
	{ 0x000E,		4,			5	},
	{ 0x001E,		5,			6	},
	{ 0x003E,		6,			7	},
	{ 0x007E,		7,			8	},
	{ 0x00FE,		8,			9	},
	{ 0x01FE,		9,			10	},
	{ 0x01FF,		9,			11	},
};

unsigned int CDcSizeLuminanceTable::m_pIndexTable[MAXBITS] =
{
	0,
	0,
	2,
	5,
	6,
	7,
	8,
	9,
	10,
};

CVLCTable* CDcSizeLuminanceTable::m_pInstance = NULL;

CDcSizeLuminanceTable::CDcSizeLuminanceTable() :
CVLCTable(MAXBITS, m_pTable, ENTRYCOUNT, m_pIndexTable)
{

}

CVLCTable* CDcSizeLuminanceTable::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CDcSizeLuminanceTable();
	}

	return m_pInstance;
}
