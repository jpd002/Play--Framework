#include <assert.h>
#include <string.h>
#include "Deflate.h"

using namespace Framework;

CDeflate::LENGHTENTRY CDeflate::m_LenghtTable[] =
{
	{ 0,   3 },
	{ 0,   4 },
	{ 0,   5 },
	{ 0,   6 },
	{ 0,   7 },
	{ 0,   8 },
	{ 0,   9 },
	{ 0,  10 },
	{ 1,  11 },
	{ 1,  13 },
	{ 1,  15 },
	{ 1,  17 },
	{ 2,  19 },
	{ 2,  23 },
	{ 2,  27 },
	{ 2,  31 },
	{ 3,  35 },
	{ 3,  43 },
	{ 3,  51 },
	{ 3,  59 },
	{ 4,  67 },
	{ 4,  83 },
	{ 4,  99 },
	{ 4, 115 },
	{ 5, 131 },
	{ 5, 163 },
	{ 5, 195 },
	{ 5, 227 },
	{ 0, 258 }
};

CDeflate::DISTANCEENTRY CDeflate::m_DistanceTable[] =
{
	{  0,     1 },
	{  0,     2 },
	{  0,     3 },
	{  0,     4 },
	{  1,     5 },
	{  1,     7 },
	{  2,     9 },
	{  2,    13 },
	{  3,    17 },
	{  3,    25 },
	{  4,    33 },
	{  4,    49 },
	{  5,    65 },
	{  5,    97 },
	{  6,   129 },
	{  6,   193 },
	{  7,   257 },
	{  7,   385 },
	{  8,   513 },
	{  8,   769 },
	{  9,  1025 },
	{  9,  1537 },
	{ 10,  2049 },
	{ 10,  3073 },
	{ 11,  4097 },
	{ 11,  6145 },
	{ 12,  8193 },
	{ 12, 12289 },
	{ 13, 16385 },
	{ 13, 24577 }
};

uint8 CDeflate::m_nCodeLenghtOrder[19] =
{
	16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
};

////////////////////////////////////////////////////////
//Huffman Trees Implementation
//------------------------------------------------------

void CDeflate::Huffman_InitializeTree(HUFFMANTREE* pH)
{
	int i;
	pH->pCode = NULL;
	for(i = 0; i < 16; i++)
	{
		pH->pV[i] = NULL;
	}
}

void CDeflate::Huffman_DeleteTree(HUFFMANTREE* pH)
{
	int i;
	if(pH->pCode != NULL)
	{
		free(pH->pCode);
		pH->pCode = NULL;
	}
	for(i = 0; i < 16; i++)
	{
		if(pH->pV[i] != NULL)
		{
			free(pH->pV[i]);
			pH->pV[i] = NULL;
		}
	}
}

uint16 CDeflate::Huffman_Decode(CBitStream* s, HUFFMANTREE* pH)
{
	int i, j;
	short nCode;
	i = 0;
	nCode = (short)s->GetBits_LSBF(1);
	while(nCode > (signed short)pH->nMax[i])
	{
		nCode <<= 1;
		nCode |= (short)s->GetBits_LSBF(1);
		i++;
	}
	j = nCode - pH->nMin[i];
	return pH->pV[i][j];
}

void CDeflate::Huffman_GenerateMinMax(HUFFMANTREE* pH)
{
	int i, j;
	j = 0;
	memset(pH->nMin, 0xFF, 16 * 2); 
	memset(pH->nMax, 0xFF, 16 * 2);
	for(i = 0; i < 16; i++)
	{
		if(pH->nL[i] == 0)
		{
			pH->nMax[i] = -1;
			continue;
		}
		pH->nMin[i] = pH->pCode[j];
		j = j + pH->nL[i] - 1;
		pH->nMax[i] = pH->pCode[j];
		j++;
	}	
}

void CDeflate::GenerateTreeFromTables(unsigned short* pLenght, unsigned long nCount, HUFFMANTREE* pH)
{
	unsigned short nCode;
	unsigned int i, j, k;

	pH->pCode = (unsigned short*)malloc(2 * nCount);

	memset(pH->nL, 0, 16);

	for(i = 0; i < nCount; i++)
	{
		if(pLenght[i] != 0)
		{
			pH->nL[pLenght[i] - 1]++;
		}
	}

	nCode = 0;
	pH->nMin[1] = 0;
	pH->nMax[1] = 0;
	for(i = 2; i < 16; i++)
	{
		pH->nMin[i] = nCode = (nCode + pH->nL[i - 2]) << 1;
		pH->nMax[i] = 0;
	}
	
	for(i = 0; i < 16; i++)
	{
		if(pH->nL[i] != 0)
		{
			pH->pV[i] = (unsigned short*)malloc(pH->nL[i] * 2);
		}
	}

	k = 0;
	for(j = 0; j < 16; j++)
	{
		if(pH->nL[j] == 0) continue;
		for(i = 0; i < nCount; i++)
		{
			if((pLenght[i] - 1) != j) continue;
			pH->pCode[k++] = pH->nMin[pLenght[i]]++;
			pH->pV[j][pH->nMax[pLenght[i]]++] = i;
		}
	}

	Huffman_GenerateMinMax(pH);
}

void CDeflate::DecompressLenghtTable(CBitStream* pStream, unsigned short* pTable, unsigned long nCount, HUFFMANTREE* pH)
{
	unsigned int i, j;
	unsigned short nTemp, nTemp2;
	for(i = 0; i < nCount; i++)
	{
		nTemp = Huffman_Decode(pStream, pH);
		switch(nTemp)
		{
		case 0x10:
			nTemp2 = pTable[i - 1];
			nTemp = (unsigned short)pStream->GetBits_LSBF(2) + 3;
			for(j = 0; j < nTemp; j++)
			{
				pTable[i] = nTemp2;
				i++;
			}
			i--;
			break;
		case 0x11:
			nTemp = (unsigned short)pStream->GetBits_LSBF(3) + 3;
			for(j = 0; j < nTemp; j++)
			{
				pTable[i] = 0;
				i++;
			}
			i--;
			break;
		case 0x12:
			nTemp = (unsigned short)pStream->GetBits_LSBF(7) + 11;
			for(j = 0; j < nTemp; j++)
			{
				pTable[i] = 0;
				i++;
			}
			i--;
			break;
		default:
			assert(nTemp < 16);
			pTable[i] = nTemp;
			break;
		}
	}
}

void CDeflate::GenerateVariableTrees(CBitStream* pStream, HUFFMANTREE* pLitt, HUFFMANTREE* pDist)
{
	unsigned short nLitt, nDist, nCLen;
	unsigned short nCodeLenght[19];
	unsigned short* pLittLenght;
	unsigned short* pDistLenght;
	unsigned int i;
	HUFFMANTREE CodeLenght; 

	Huffman_InitializeTree(&CodeLenght);

	nLitt = (unsigned short)pStream->GetBits_LSBF(5);
	nDist = (unsigned short)pStream->GetBits_LSBF(5);
	nCLen = (unsigned short)pStream->GetBits_LSBF(4);

	nCLen += 4;
	nLitt += 257;
	nDist += 1;

	pLittLenght = (unsigned short*)malloc(nLitt * 2);
	pDistLenght = (unsigned short*)malloc(nDist * 2);

	memset(nCodeLenght, 0, 19 * 2);
	for(i = 0; i < nCLen; i++)
	{
		nCodeLenght[m_nCodeLenghtOrder[i]] = (unsigned short)pStream->GetBits_LSBF(3);
	}
	GenerateTreeFromTables(nCodeLenght, 19, &CodeLenght);

	DecompressLenghtTable(pStream, pLittLenght, nLitt, &CodeLenght);
	GenerateTreeFromTables(pLittLenght, nLitt, pLitt);

	DecompressLenghtTable(pStream, pDistLenght, nDist, &CodeLenght);
	GenerateTreeFromTables(pDistLenght, nDist, pDist);

	free(pLittLenght);
	free(pDistLenght);

}

void CDeflate::GenerateFixedTrees(HUFFMANTREE* pLitt, HUFFMANTREE* pDist)
{

	//Lit Value    Bits  Codes
	//---------    ----	 -----
	//  0 - 143     8	 00110000 through 10111111
	//144 - 255     9	 110010000 through 111111111
	//256 - 279     7	 0000000 through 0010111
	//280 - 287     8	 11000000 through 11000111

	int i, j;
	unsigned short nStartCode;

	memset(pLitt->nL, 0, 16);
	pLitt->pCode	= (unsigned short*)malloc(288 * 2);
	pLitt->pV[6]	= (unsigned short*)malloc( 24 * 2);
	pLitt->pV[7]	= (unsigned short*)malloc(152 * 2);
	pLitt->pV[8]	= (unsigned short*)malloc(112 * 2);

	j = 0;
	nStartCode = 0;
	for(i = 256; i < 280; i++) 
	{
		pLitt->pCode[j++] = nStartCode++;
		pLitt->pV[6][i - 256] = i;
		pLitt->nL[6]++;
	}

	nStartCode = 0x30;
	for(i = 0; i < 144; i++) 
	{
		pLitt->pCode[j++] = nStartCode++;
		pLitt->pV[7][i] = i;
		pLitt->nL[7]++;
	}

	nStartCode = 0xC0;
	for(i = 280; i < 288; i++) 
	{
		pLitt->pCode[j++] = nStartCode++;
		pLitt->pV[7][i - 280 + 144] = i;
		pLitt->nL[7]++;
	}

	nStartCode = 0x190;
	for(i = 144; i < 256; i++)
	{
		pLitt->pCode[j++] = nStartCode++;
		pLitt->pV[8][i - 144] = i;
		pLitt->nL[8]++;
	}


	memset(pDist->nL, 0, 16);
	pDist->pCode	= (unsigned short*)malloc(32 * 2);
	pDist->pV[4]	= (unsigned short*)malloc(32 * 2);

	for(i = 0; i < 32; i++)
	{
		pDist->pCode[i] = i;
		pDist->pV[4][i] = i;
		pDist->nL[4]++;
	}

	Huffman_GenerateMinMax(pLitt);
	Huffman_GenerateMinMax(pDist);

}

int CDeflate::Decompress(CBitStream* pStream, uint8* pOutput)
{
	unsigned char nEOB, nCompType, nTemp, nLastBlock;
	unsigned short nChar, nLenght, i;
	unsigned long nDistance;
	HUFFMANTREE Litt, Dist;
	nLastBlock = 0;
	Huffman_InitializeTree(&Litt);
	Huffman_InitializeTree(&Dist);
	while(!nLastBlock)
	{
		nLastBlock = (unsigned char)pStream->GetBits_LSBF(1);
		nCompType = (unsigned char)pStream->GetBits_LSBF(2);
		if(nCompType == 0x00)
		{
			//Raw data... just copy
			assert(0);
		}
		else if(nCompType == 0x3)
		{
			//Invalid
			assert(0);
		}
		else
		{
			//Clean up the trees
			Huffman_DeleteTree(&Litt);
			Huffman_DeleteTree(&Dist);
			if(nCompType == 1)
			{
				GenerateFixedTrees(&Litt, &Dist);
			}
			else
			{
				GenerateVariableTrees(pStream, &Litt, &Dist);
			}
			//Get the next litteral character
			nEOB = 0;
			while(!nEOB)
			{
				nChar = Huffman_Decode(pStream, &Litt);
				if(nChar == 256)
				{
					//End of block
					nEOB = 1;
				}
				else if(nChar > 256)
				{
					//Lenght, Distance
					unsigned char* pStart;
					unsigned char* pEnd;

					nTemp = (unsigned char)pStream->GetBits_LSBF(m_LenghtTable[nChar - 257].nBits);
					nLenght = nTemp + m_LenghtTable[nChar - 257].nBaseLenght;
					nTemp = (unsigned char)Huffman_Decode(pStream, &Dist);
					nDistance = m_DistanceTable[nTemp].nBaseDist;
					nDistance += pStream->GetBits_LSBF(m_DistanceTable[nTemp].nBits);
					
					pStart = pOutput - nDistance;
					pEnd = pOutput;
					for(i = 0; i < nLenght; i++)
					{
						*pOutput = *pStart;
						pOutput++;
						pStart++;
						if(pStart == pEnd)
						{
							pStart = pEnd - nDistance;
						}
					}
				}
				else
				{
					*pOutput = (unsigned char)nChar;
					pOutput++;
				}
			}
		}
	}
	return 1;
}
