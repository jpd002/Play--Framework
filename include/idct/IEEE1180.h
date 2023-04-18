#pragma once

#include "idct/Interface.h"

namespace IDCT
{

	class CIEEE1180 : public CInterface
	{
	public:
								CIEEE1180();
		virtual					~CIEEE1180();
		static CInterface*		GetInstance();
		void					Transform(const int16*, int16*) override;

	private:
		void					PrepareTable();

		double					m_nC[8][8];
		static CInterface*		m_pInstance;
	};

};
