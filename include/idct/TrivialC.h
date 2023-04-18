#pragma once

#include "idct/Interface.h"

namespace IDCT
{

	class CTrivialC : public CInterface
	{
	public:
								CTrivialC();
		virtual					~CTrivialC();
		static CInterface*		GetInstance();
		void					Transform(const int16*, int16*) override;

	private:
		void					PrepareTables();

		double					m_nCosTable[8][8];
		static CInterface*		m_pInstance;
	};

}
