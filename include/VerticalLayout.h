#ifndef _VERTICALLAYOUT_H_
#define _VERTICALLAYOUT_H_

#include "FlatLayout.h"

namespace Framework
{

	class CVerticalLayout : public CFlatLayout
	{
	public:
							CVerticalLayout(unsigned int = LAYOUT_DEFAULT_SPACING);
		unsigned int		GetPreferredWidth();
		unsigned int		GetPreferredHeight();

	protected:
		CLayoutBaseItem*	CreateLayoutBaseItem(CLayoutObject*);
		void				SetObjectRange(CLayoutObject*, unsigned int, unsigned int);
		unsigned int		GetObjectPreferredSize(CLayoutObject*);
		unsigned int		GetLayoutSize();
		

	private:


	};

}

#endif
