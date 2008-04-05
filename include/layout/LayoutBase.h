#ifndef _LAYOUTBASE_H_
#define _LAYOUTBASE_H_

#include <boost/ptr_container/ptr_list.hpp>
#include "LayoutBaseItem.h"

namespace Framework
{

    class CLayoutBase
    {
    public:
        typedef boost::ptr_list<CLayoutBaseItem> ItemList;
        typedef ItemList::const_iterator ItemIterator;

                                    ~CLayoutBase();
        void                        Clear();
        void                        InsertItem(CLayoutBaseItem*);
        void                        ComputeRanges(unsigned int);
        unsigned int                GetPreferredSize() const;
        
        ItemIterator                GetItemsBegin() const;
        ItemIterator                GetItemsEnd() const;

    private:
        bool                        HasOnlyNonStretchable() const;
        unsigned int                GetTotalStretchUnits() const;
        ItemList                    m_items;
    };

}

#endif
