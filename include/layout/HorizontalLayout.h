#ifndef _HORIZONTALLAYOUT_H_
#define _HORIZONTALLAYOUT_H_

#include "FlatLayout.h"

namespace Framework
{

	class CHorizontalLayout : public CFlatLayout
	{
	public:	
        static FlatLayoutPtr    Create(unsigned int = LAYOUT_DEFAULT_SPACING); 
		unsigned int		    GetPreferredWidth();
		unsigned int		    GetPreferredHeight();

	protected:
							    CHorizontalLayout(unsigned int);
		CLayoutBaseItem*	    CreateLayoutBaseItem(const LayoutObjectPtr&);
		void				    SetObjectRange(const LayoutObjectPtr&, unsigned int, unsigned int);
		unsigned int		    GetObjectPreferredSize(const LayoutObjectPtr&);
		unsigned int		    GetLayoutSize();
	};

}


#endif
