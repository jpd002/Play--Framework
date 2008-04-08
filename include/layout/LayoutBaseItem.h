#ifndef _LAYOUTBASEITEM_H_
#define _LAYOUTBASEITEM_H_

#include <boost/noncopyable.hpp>
#include "LayoutObject.h"

namespace Framework
{

    class CLayoutBaseItem : public boost::noncopyable
	{
	public:
                            CLayoutBaseItem(unsigned int, unsigned int, const LayoutObjectPtr&);
                            CLayoutBaseItem(unsigned int, unsigned int, unsigned int = -1);

        unsigned int        GetPreferredSize()	const;
        unsigned int        GetStretch()		const;
        LayoutObjectPtr     GetObject()			const;
        unsigned int        GetKey()			const;

        unsigned int        GetRangeStart()		const;
        unsigned int        GetRangeEnd()		const;
        void                SetRange(unsigned int, unsigned int);

	private:
		unsigned int        m_nPreferredSize;
		unsigned int        m_nStretch;

		LayoutObjectPtr     m_pObject;
		unsigned int        m_nKey;

		unsigned int        m_nRangeStart;
		unsigned int        m_nRangeEnd;
	};

}

#endif
