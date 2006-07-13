#ifndef _IDCT_TRIVIALC_H_
#define _IDCT_TRIVIALC_H_

#include "idct/Interface.h"

namespace IDCT
{

	class CTrivialC : public CInterface
	{
	public:
								CTrivialC();
		virtual					~CTrivialC();
		static CInterface*		GetInstance();
		virtual void			Transform(int16*, int16*);

	private:
		void					PrepareTables();

		double					m_nCosTable[8][8];
		static CInterface*		m_pInstance;
	};

}

#endif
