#ifndef _DEFLATE_H_
#define _DEFLATE_H_

#include "BitStream.h"

namespace Framework
{
	class CDeflate
	{
	private:
		struct LENGHTENTRY
		{
			uint8 nBits;
			uint16 nBaseLenght;
		};

		struct DISTANCEENTRY
		{
			uint8 nBits;
			uint16 nBaseDist;
		};

		struct HUFFMANTREE
		{
			uint8 nL[16];
			uint16* pV[16];
			uint16* pCode;
			int16 nMin[16];
			int16 nMax[16];
		};

	public:
		static int				Decompress(CBitStream*, uint8*);

	private:
		static void				GenerateFixedTrees(HUFFMANTREE*, HUFFMANTREE*);
		static void				GenerateTreeFromTables(unsigned short*, unsigned long, HUFFMANTREE*);
		static void				GenerateVariableTrees(CBitStream*, HUFFMANTREE*, HUFFMANTREE*);
		static void				DecompressLenghtTable(CBitStream*, unsigned short*, unsigned long, HUFFMANTREE*);

		static void				Huffman_InitializeTree(HUFFMANTREE*);
		static void				Huffman_DeleteTree(HUFFMANTREE*);
		static uint16			Huffman_Decode(CBitStream*, HUFFMANTREE*);
		static void				Huffman_GenerateMinMax(HUFFMANTREE*);

		static LENGHTENTRY		m_LenghtTable[];
		static DISTANCEENTRY	m_DistanceTable[];
		static uint8			m_nCodeLenghtOrder[19];

  };
}

#endif
