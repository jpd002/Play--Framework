/////////////////////////////////////////////
//A really dumb IDCT algorithm
//Such a pity...
/////////////////////////////////////////////

#include <math.h>
#include <string.h>
#include "idct/TrivialC.h"

#define INVSQ2  0.70710678118654752440084436210485f
#define PI		3.1415926535897932384626433832795f

using namespace IDCT;

CInterface* CTrivialC::m_pInstance = NULL;

CTrivialC::CTrivialC()
{
	PrepareTables();
}

CTrivialC::~CTrivialC()
{

}

CInterface* CTrivialC::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CTrivialC();
	}

	return m_pInstance;
}

void CTrivialC::PrepareTables()
{
	unsigned int x, y;

	for(y = 0; y < 8; y++)
	{
		for(x = 0; x < 8; x++)
		{
			m_nCosTable[x][y] = cos((((2 * (double)x) + 1) / 16) * (double)y * PI);
		}
	}
}

void CTrivialC::Transform(int16* pUV, int16* pXY)
{
	//IDCT
	//		    1     7   7                      2*x+1                2*y+1
	//f(x,y) = --- * sum sum c(u,v)*F(u,v)*cos (------- *u*PI)* cos (------ *v*PI)
	//	        4    u=0 v=0                      16                   16
	//
	//         { 1/2 when u=v=0
	//c(u,v) = { 1/sqrt(2) when  u  = 0,  v != 0
	//         { 1/sqrt(2) when  u != 0,  v  = 0
	//	       { 1 otherwise

	unsigned int x, y;
	short* pTemp;
	double nSum;
	for(y = 0; y < 8; y++)
	{
		for(x = 0; x < 8; x++)
		{
			nSum = 0;
			pTemp = pUV;

			//V = 0
			nSum += 0.5f   * (double)(*pTemp++);
			nSum += INVSQ2 * (double)(*pTemp++) * m_nCosTable[x][1];
			nSum += INVSQ2 * (double)(*pTemp++) * m_nCosTable[x][2];
			nSum += INVSQ2 * (double)(*pTemp++) * m_nCosTable[x][3];
			nSum += INVSQ2 * (double)(*pTemp++) * m_nCosTable[x][4];
			nSum += INVSQ2 * (double)(*pTemp++) * m_nCosTable[x][5];
			nSum += INVSQ2 * (double)(*pTemp++) * m_nCosTable[x][6];
			nSum += INVSQ2 * (double)(*pTemp++) * m_nCosTable[x][7];

			//V = 1
			nSum += INVSQ2 * (double)(*pTemp++)                     * m_nCosTable[y][1];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][1] * m_nCosTable[y][1];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][2] * m_nCosTable[y][1];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][3] * m_nCosTable[y][1];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][4] * m_nCosTable[y][1];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][5] * m_nCosTable[y][1];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][6] * m_nCosTable[y][1];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][7] * m_nCosTable[y][1];

			//V = 2
			nSum += INVSQ2 * (double)(*pTemp++)                     * m_nCosTable[y][2];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][1] * m_nCosTable[y][2];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][2] * m_nCosTable[y][2];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][3] * m_nCosTable[y][2];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][4] * m_nCosTable[y][2];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][5] * m_nCosTable[y][2];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][6] * m_nCosTable[y][2];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][7] * m_nCosTable[y][2];

			//V = 3
			nSum += INVSQ2 * (double)(*pTemp++)                     * m_nCosTable[y][3];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][1] * m_nCosTable[y][3];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][2] * m_nCosTable[y][3];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][3] * m_nCosTable[y][3];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][4] * m_nCosTable[y][3];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][5] * m_nCosTable[y][3];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][6] * m_nCosTable[y][3];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][7] * m_nCosTable[y][3];

			//V = 4
			nSum += INVSQ2 * (double)(*pTemp++)                     * m_nCosTable[y][4];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][1] * m_nCosTable[y][4];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][2] * m_nCosTable[y][4];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][3] * m_nCosTable[y][4];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][4] * m_nCosTable[y][4];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][5] * m_nCosTable[y][4];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][6] * m_nCosTable[y][4];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][7] * m_nCosTable[y][4];

			//V = 5
			nSum += INVSQ2 * (double)(*pTemp++)                     * m_nCosTable[y][5];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][1] * m_nCosTable[y][5];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][2] * m_nCosTable[y][5];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][3] * m_nCosTable[y][5];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][4] * m_nCosTable[y][5];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][5] * m_nCosTable[y][5];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][6] * m_nCosTable[y][5];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][7] * m_nCosTable[y][5];

			//V = 6
			nSum += INVSQ2 * (double)(*pTemp++)                     * m_nCosTable[y][6];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][1] * m_nCosTable[y][6];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][2] * m_nCosTable[y][6];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][3] * m_nCosTable[y][6];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][4] * m_nCosTable[y][6];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][5] * m_nCosTable[y][6];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][6] * m_nCosTable[y][6];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][7] * m_nCosTable[y][6];

			//V = 7
			nSum += INVSQ2 * (double)(*pTemp++)                     * m_nCosTable[y][7];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][1] * m_nCosTable[y][7];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][2] * m_nCosTable[y][7];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][3] * m_nCosTable[y][7];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][4] * m_nCosTable[y][7];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][5] * m_nCosTable[y][7];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][6] * m_nCosTable[y][7];
			nSum +=	         (double)(*pTemp++) * m_nCosTable[x][7] * m_nCosTable[y][7];

			nSum *= 0.25f;
			pXY[((y * 8) + x)] = (short)nSum;
		}
	}
}
