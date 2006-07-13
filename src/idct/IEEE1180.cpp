/* Taken from mpeg2decode */
/* Copyright (C) 1996, MPEG Software Simulation Group. All Rights Reserved. */

#include <math.h>
#include "PtrMacro.h"
#include "idct/IEEE1180.h"

#ifndef PI
#	ifdef M_PI
#		define PI M_PI
#	else
#		define PI 3.14159265358979323846
#	endif
#endif

using namespace IDCT;

CInterface* CIEEE1180::m_pInstance = NULL;

CIEEE1180::CIEEE1180()
{
	PrepareTable();
}

CIEEE1180::~CIEEE1180()
{

}

CInterface* CIEEE1180::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CIEEE1180();
	}

	return m_pInstance;
}

void CIEEE1180::PrepareTable()
{
	int freq, time;
	double scale;

	for (freq=0; freq < 8; freq++)
	{
		scale = (freq == 0) ? sqrt(0.125) : 0.5;
		for (time=0; time<8; time++)
		{
			m_nC[freq][time] = scale*cos((PI/8.0)*freq*(time + 0.5));
		}
	}
}

void CIEEE1180::Transform(int16* pUV, int16* pXY)
{
	int i, j, k, v;
	double partial_product;
	double tmp[64];

	for (i=0; i<8; i++)
	{
		for (j=0; j<8; j++)
		{
			partial_product = 0.0;

			for (k=0; k<8; k++)
			{
				partial_product+= m_nC[k][j]*pUV[8*i+k];
			}

			tmp[8*i+j] = partial_product;
		}
    }

  /* Transpose operation is integrated into address mapping by switching 
     loop order of i and j */

	for (j=0; j<8; j++)
	{
		for (i=0; i<8; i++)
		{
			partial_product = 0.0;

			for (k=0; k<8; k++)
			{
				partial_product+= m_nC[k][i]*tmp[8*k+j];
			}

			v = (int) floor(partial_product+0.5);
			pXY[8*i+j] = v;
		}
	}
}
