#pragma once

#include "LayoutObject.h"

namespace Framework
{

	class CLayoutStretch : public CLayoutObject
	{
	public:
									CLayoutStretch(unsigned int, unsigned int);

		static LayoutObjectPtr		Create(unsigned int = 1, unsigned int = 1);

		unsigned int				GetPreferredWidth() override;
		unsigned int				GetPreferredHeight() override;
		void						RefreshGeometry() override;
	};

}
