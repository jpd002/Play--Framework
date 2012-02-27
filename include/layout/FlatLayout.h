#ifndef _FLATLAYOUT_H_
#define _FLATLAYOUT_H_

#include "LayoutObject.h"
#include "LayoutBase.h"

namespace Framework
{

    class CFlatLayout : public CLayoutObject, public boost::noncopyable
    {
    public:
        typedef std::list<LayoutObjectPtr> ObjectList;
        typedef ObjectList::const_iterator ObjectIterator;

                                    CFlatLayout(unsigned int, unsigned int, unsigned int = LAYOUT_DEFAULT_SPACING);
        virtual                     ~CFlatLayout();
        void                        InsertObject(const LayoutObjectPtr&);
        virtual	void                RefreshGeometry();

    protected:
        virtual CLayoutBaseItem*    CreateLayoutBaseItem(const LayoutObjectPtr&)                        = 0;
        virtual void                SetObjectRange(const LayoutObjectPtr&, unsigned int, unsigned int)  = 0;
        virtual unsigned int        GetObjectPreferredSize(const LayoutObjectPtr&)                      = 0;
        virtual unsigned int        GetLayoutSize()                                                     = 0;
        unsigned int                GetPreferredSize() const;
        ObjectList                  m_objects;

    private:
        CLayoutBase                 m_LayoutBase;
        unsigned int                m_nSpacing;

    };

    typedef std::shared_ptr<CFlatLayout> FlatLayoutPtr;
}

#endif
