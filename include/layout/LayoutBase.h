#pragma once

#include <vector>
#include "LayoutBaseItem.h"

namespace Framework
{

	class CLayoutBase
	{
	public:
		typedef std::vector<CLayoutBaseItem> ItemList;
		typedef ItemList::const_iterator ItemIterator;

									~CLayoutBase();

		void						Clear();

		void						InsertItem(const CLayoutBaseItem&);
		void						ComputeRanges(unsigned int);
		unsigned int				GetPreferredSize() const;

		const ItemList&				GetItems() const;

	private:
		bool						HasOnlyNonStretchable() const;
		unsigned int				GetTotalStretchUnits() const;

		ItemList					m_items;
	};

}
