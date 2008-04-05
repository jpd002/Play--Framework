#ifndef _GRIDLAYOUT_H_
#define _GRIDLAYOUT_H_

#include "LayoutObject.h"
#include "LayoutBase.h"
#include <boost/multi_array.hpp>

namespace Framework
{

    class CGridLayout : public CLayoutObject
    {
    public:
                            CGridLayout(unsigned int, unsigned int, unsigned int = LAYOUT_DEFAULT_SPACING);
        virtual             ~CGridLayout();

        unsigned int        GetPreferredWidth();
        unsigned int        GetPreferredHeight();
        void                RefreshGeometry();

        void                SetObject(unsigned int, unsigned int, CLayoutObject*);

    private:
        typedef boost::multi_array<CLayoutObject*, 2> GridArray;

        void                RebuildLayouts();
        CLayoutBaseItem*    CreateColLayoutBaseItem(unsigned int);
        CLayoutBaseItem*    CreateRowLayoutBaseItem(unsigned int);

        unsigned int        m_nCols;
        unsigned int        m_nRows;
        unsigned int        m_nSpacing;

        GridArray           m_objects;

        CLayoutBase         m_HorzLayout;
        CLayoutBase         m_VertLayout;

    };

}

#endif
