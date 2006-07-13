#ifndef _LAYOUTBASE_H_
#define _LAYOUTBASE_H_

#include "List.h"
#include "LayoutBaseItem.h"

namespace Framework
{

	class CLayoutBase
	{
	public:
									~CLayoutBase();
		void						Clear();
		void						InsertItem(CLayoutBaseItem*);
		void						ComputeRanges(unsigned int);
		unsigned int				GetPreferredSize();
		CList<CLayoutBaseItem>*		GetItems();

	private:
		bool						HasOnlyNonStretchable();
		unsigned int				GetTotalStretchUnits();
		CList<CLayoutBaseItem>		m_Item;
	};

}

#endif
