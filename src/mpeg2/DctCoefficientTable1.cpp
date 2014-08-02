#include <assert.h>
#include <string.h>
#include "mpeg2/DctCoefficientTable1.h"

using namespace MPEG2;
using namespace Framework;

RUNLEVELPAIR CDctCoefficientTable1::m_runLevelTable[ENTRYCOUNT] = 
{
	//Page 134
	{ 0,			1	},
	{ 1,			1	},
	{ 0,			2	},
	{ 2,			1	},
	{ 0,			3	},
	{ 3,			1	},
	{ 4,			1	},
	{ 1,			2	},
	{ 5,			1	},
	{ 6,			1	},
	{ 7,			1	},
	{ 0,			4	},
	{ 2,			2	},
	{ 8,			1	},
	{ 9,			1	},
	{ RUN_ESCAPE,	0	},
	{ 0,			5	},
	{ 0,			6	},
	{ 1,			3	},
	{ 3,			2	},
	{ 10,			1	},
	{ 11,			1	},
	{ 12,			1	},
	{ 13,			1	},
	{ 0,			7	},
	{ 1,			4	},
	{ 2,			3	},
	{ 4,			2	},
	{ 5,			2	},
	{ 14,			1	},
	{ 15,			1	},
	{ 16,			1	},

	//Page 135
	{ 0,			8	},
	{ 0,			9	},
	{ 0,			10	},
	{ 0,			11	},
	{ 1,			5	},
	{ 2,			4	},
	{ 3,			3	},
	{ 4,			3	},
	{ 6,			2	},
	{ 7,			2	},
	{ 8,			2	},
	{ 17,			1	},
	{ 18,			1	},
	{ 19,			1	},
	{ 20,			1	},
	{ 21,			1	},
	{ 0,			12	},
	{ 0,			13	},
	{ 0,			14	},
	{ 0,			15	},
	{ 1,			6	},
	{ 1,			7	},
	{ 2,			5	},
	{ 3,			4	},
	{ 5,			3	},
	{ 9,			2	},
	{ 10,			2	},
	{ 22,			1	},
	{ 23,			1	},
	{ 24,			1	},
	{ 25,			1	},
	{ 26,			1	},

	//Page 132
	{ 0,			16	},
	{ 0,			17	},
	{ 0,			18	},
	{ 0,			19	},
	{ 0,			20	},
	{ 0,			21	},
	{ 0,			22	},
	{ 0,			23	},
	{ 0,			24	},
	{ 0,			25	},
	{ 0,			26	},
	{ 0,			27	},
	{ 0,			28	},
	{ 0,			29	},
	{ 0,			30	},
	{ 0,			31	},
	{ 0,			32	},
	{ 0,			33	},
	{ 0,			34	},
	{ 0,			35	},
	{ 0,			36	},
	{ 0,			37	},
	{ 0,			38	},
	{ 0,			39	},
	{ 0,			40	},
	{ 1,			8	},
	{ 1,			9	},
	{ 1,			10	},
	{ 1,			11	},
	{ 1,			12	},
	{ 1,			13	},
	{ 1,			14	},


	{ 1,			15	},
	{ 1,			16	},
	{ 1,			17	},
	{ 1,			18	},
	{ 6,			3	},
	{ 11,			2	},
	{ 12,			2	},
	{ 13,			2	},
	{ 14,			2	},
	{ 15,			2	},
	{ 16,			2	},
	{ 27,			1	},
	{ 28,			1	},
	{ 29,			1	},
	{ 30,			1	},
	{ 31,			1	},
};

VLCTABLEENTRY CDctCoefficientTable1::m_vlcTable[ENTRYCOUNT] =
{
	//Page 134
	{ 0x0002,		2,			0	},
	{ 0x0002,		3,			1	},
	{ 0x0006,		3,			2	},
	{ 0x0007,		4,			4	},
	{ 0x0005,		5,			3	},
	{ 0x0007,		5,			5	},
	{ 0x0006,		5,			7	},
	{ 0x001C,		5,			11	},
	{ 0x001D,		5,			16	},
	{ 0x0006,		6,			6	},
	{ 0x0007,		6,			8	},
	{ 0x0005,		6,			17	},
	{ 0x0004,		6,			24	},
	{ 0x0001,		6,			15	},
	{ 0x0079,		7,			18	},
	{ 0x007A,		7,			20	},
	{ 0x0007,		7,			12	},
	{ 0x0005,		7,			13	},
	{ 0x0078,		7,			14	},
	{ 0x0006,		7,			9	},
	{ 0x0004,		7,			10	},
	{ 0x007B,		7,			32	},
	{ 0x007C,		7,			33	},
	{ 0x0026,		8,			19	},
	{ 0x0021,		8,			21	},
	{ 0x0025,		8,			22	},
	{ 0x0024,		8,			23	},
	{ 0x0027,		8,			25	},
	{ 0x00FC,		8,			26	},
	{ 0x00FD,		8,			27	},
	{ 0x00FA,		8,			48	},
	{ 0x00FB,		8,			49	},
	{ 0x00FE,		8,			50	},
	{ 0x00FF,		8,			51	},
	{ 0x0023,		8,			34	},
	{ 0x0022,		8,			35	},
	{ 0x0020,		8,			36	},

	//Page 135
	{ 0x0004,		9,			28	},
	{ 0x0005,		9,			29	},
	{ 0x0007,		9,			30	},
	{ 0x000D,		10,			31	},
	{ 0x000C,		10,			37	},
	{ 0x001C,		12,			38	},
	{ 0x0012,		12,			39	},
	{ 0x001E,		12,			40	},
	{ 0x0015,		12,			41	},
	{ 0x0011,		12,			42	},
	{ 0x001F,		12,			43	},
	{ 0x001A,		12,			44	},
	{ 0x0019,		12,			45	},
	{ 0x0017,		12,			46	},
	{ 0x0016,		12,			47	},
	{ 0x0016,		13,			52	},
	{ 0x0015,		13,			53	},
	{ 0x0014,		13,			54	},
	{ 0x0013,		13,			55	},
	{ 0x0012,		13,			56	},
	{ 0x0011,		13,			57	},
	{ 0x0010,		13,			58	},
	{ 0x001F,		13,			59	},
	{ 0x001E,		13,			60	},
	{ 0x001D,		13,			61	},
	{ 0x001C,		13,			62	},
	{ 0x001B,		13,			63	},

	//Page 136
	{ 0x001F,		14,			64	},
	{ 0x001E,		14,			65	},
	{ 0x001D,		14,			66	},
	{ 0x001C,		14,			67	},
	{ 0x001B,		14,			68	},
	{ 0x001A,		14,			69	},
	{ 0x0019,		14,			70	},
	{ 0x0018,		14,			71	},
	{ 0x0017,		14,			72	},
	{ 0x0016,		14,			73	},
	{ 0x0015,		14,			74	},
	{ 0x0014,		14,			75	},
	{ 0x0013,		14,			76	},
	{ 0x0012,		14,			77	},
	{ 0x0011,		14,			78	},
	{ 0x0010,		14,			79	},
	{ 0x0018,		15,			80	},
	{ 0x0017,		15,			81	},
	{ 0x0016,		15,			82	},
	{ 0x0015,		15,			83	},
	{ 0x0014,		15,			84	},
	{ 0x0013,		15,			85	},
	{ 0x0012,		15,			86	},
	{ 0x0011,		15,			87	},
	{ 0x0010,		15,			88	},
	{ 0x001F,		15,			89	},
	{ 0x001E,		15,			90	},
	{ 0x001D,		15,			91	},
	{ 0x001C,		15,			92	},
	{ 0x001B,		15,			93	},
	{ 0x001A,		15,			94	},
	{ 0x0019,		15,			95	},

	//Page 137
	{ 0x0013,		16,			96	},
	{ 0x0012,		16,			97	},
	{ 0x0011,		16,			98	},
	{ 0x0010,		16,			99	},
	{ 0x0014,		16,			100	},
	{ 0x001A,		16,			101	},
	{ 0x0019,		16,			102	},
	{ 0x0018,		16,			103	},
	{ 0x0017,		16,			104	},
	{ 0x0016,		16,			105	},
	{ 0x0015,		16,			106	},
	{ 0x001F,		16,			107	},
	{ 0x001E,		16,			108	},
	{ 0x001D,		16,			109	},
	{ 0x001C,		16,			110	},
	{ 0x001B,		16,			111	},
};

unsigned int CDctCoefficientTable1::m_indexTable[MAXBITS] =
{
	0,
	0,
	1,
	3,		//4
	4,		//5
	9,		//6
	14,		//7
	23,		//8
	37,		//9
	40,		//10
	40,		//11
	42,		//12
	52,		//13
	64,		//14
	80,		//15
	96,		//16
};

CDctCoefficientTable1::CDctCoefficientTable1() 
: CDctCoefficientTable(MAXBITS, m_vlcTable, ENTRYCOUNT, m_indexTable)
{

}

CVLCTable::DECODE_STATUS CDctCoefficientTable1::TryIsEndOfBlock(CBitStream* stream, bool& result)
{
	uint32 eobCode = 0;
	if(!stream->TryPeekBits_MSBF(4, eobCode))
	{
		return DECODE_STATUS_NOTENOUGHDATA;
	}
	result = (eobCode == 6);
	return DECODE_STATUS_SUCCESS;
}

CVLCTable::DECODE_STATUS CDctCoefficientTable1::TrySkipEndOfBlock(CBitStream* stream)
{
	uint32 eobCode = 0;
	if(!stream->TryGetBits_MSBF(4, eobCode))
	{
		return DECODE_STATUS_NOTENOUGHDATA;
	}
	return DECODE_STATUS_SUCCESS;
}

CVLCTable::DECODE_STATUS CDctCoefficientTable1::TryGetRunLevelPair(CBitStream* stream, RUNLEVELPAIR* pairDst, bool isMpeg2)
{
	const VLCTABLEENTRY* entry(nullptr);
	uint8 bitCount = 0;
	auto result = TryPeekSymbol(stream, entry);
	if(result != DECODE_STATUS_SUCCESS)
	{
		return result;
	}

	bitCount += entry->codeLength;
	uint32 index = entry->value;
	RUNLEVELPAIR* pair = &m_runLevelTable[index];

	if(pair->run == RUN_ESCAPE)
	{
		uint32 run = 0;
		if(!TryPeekValueOfs(stream, 6, bitCount, run))
		{
			return DECODE_STATUS_NOTENOUGHDATA;
		}
		pairDst->run = run;

		if(!isMpeg2)
		{
			//Is this even possible?
			assert(0);
		}
		else
		{
			uint32 level = 0;
			if(!TryPeekValueOfs(stream, 12, bitCount, level))
			{
				return DECODE_STATUS_NOTENOUGHDATA;
			}

			if(level & 0x800)
			{
				level |= 0xF000;
				level = static_cast<int16>(level);
			}

			pairDst->level = level;
		}

	}
	else
	{
		uint32 sign = 0;
		if(!TryPeekValueOfs(stream, 1, bitCount, sign))
		{
			return DECODE_STATUS_NOTENOUGHDATA;
		}

		if(pairDst)
		{
			pairDst->run = pair->run;

			if(sign == 1)
			{
				pairDst->level = 0 - pair->level;
			}
			else
			{
				pairDst->level = pair->level;
			}
		}
	}

	stream->Advance(bitCount);
	return DECODE_STATUS_SUCCESS;
}

CVLCTable::DECODE_STATUS CDctCoefficientTable1::TryGetRunLevelPairDc(CBitStream* stream, RUNLEVELPAIR* pairDst, bool isMpeg2)
{
	assert(0);
	return DECODE_STATUS_SYMBOLNOTFOUND;
}