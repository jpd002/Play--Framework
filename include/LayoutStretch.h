#ifndef _LAYOUTSTRETCH_H_
#define _LAYOUTSTRETCH_H_

#include "LayoutObject.h"

namespace Framework
{

	class CLayoutStretch : public CLayoutObject
	{
	public:
							CLayoutStretch(unsigned int = 1, unsigned int = 1);
		unsigned int		GetPreferredWidth();
		unsigned int		GetPreferredHeight();
		void				RefreshGeometry();

	private:

	};

}

#endif
