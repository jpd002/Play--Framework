#ifndef _IDCT_IEEE1180_H_
#define _IDCT_IEEE1180_H_

#include "idct/Interface.h"

namespace IDCT
{

	class CIEEE1180 : public CInterface
	{
	public:
								CIEEE1180();
		virtual					~CIEEE1180();
		static CInterface*		GetInstance();
		virtual void			Transform(int16*, int16*);

	private:
		void					PrepareTable();

		double					m_nC[8][8];
		static CInterface*		m_pInstance;
	};

};

#endif
