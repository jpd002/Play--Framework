#ifndef _VERTICALLAYOUT_H_
#define _VERTICALLAYOUT_H_

#include "FlatLayout.h"

namespace Framework
{

	class CVerticalLayout : public CFlatLayout
	{
	public:
        static FlatLayoutPtr    Create(unsigned int = LAYOUT_DEFAULT_SPACING);
		unsigned int		    GetPreferredWidth();
		unsigned int		    GetPreferredHeight();

	protected:
							    CVerticalLayout(unsigned int);
		CLayoutBaseItem*	    CreateLayoutBaseItem(const LayoutObjectPtr&);
		void				    SetObjectRange(const LayoutObjectPtr&, unsigned int, unsigned int);
		unsigned int		    GetObjectPreferredSize(const LayoutObjectPtr&);
		unsigned int		    GetLayoutSize();
		

	private:


	};

}

#endif
