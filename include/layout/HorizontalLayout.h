#ifndef _HORIZONTALLAYOUT_H_
#define _HORIZONTALLAYOUT_H_

#include "FlatLayout.h"

namespace Framework
{

	class CHorizontalLayout : public CFlatLayout
	{
	public:	
							CHorizontalLayout(unsigned int = LAYOUT_DEFAULT_SPACING);
		unsigned int		GetPreferredWidth();
		unsigned int		GetPreferredHeight();

	protected:
		CLayoutBaseItem*	CreateLayoutBaseItem(CLayoutObject*);
		void				SetObjectRange(CLayoutObject*, unsigned int, unsigned int);
		unsigned int		GetObjectPreferredSize(CLayoutObject*);
		unsigned int		GetLayoutSize();
	};

}


#endif
