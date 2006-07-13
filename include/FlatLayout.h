#ifndef _FLATLAYOUT_H_
#define _FLATLAYOUT_H_

#include "List.h"
#include "LayoutObject.h"
#include "LayoutBase.h"

namespace Framework
{

	class CFlatLayout : public CLayoutObject
	{
	public:
									CFlatLayout(unsigned int, unsigned int, unsigned int = LAYOUT_DEFAULT_SPACING);
		virtual						~CFlatLayout();
		void						InsertObject(CLayoutObject*);
		virtual	void				RefreshGeometry();

	protected:
		virtual CLayoutBaseItem*	CreateLayoutBaseItem(CLayoutObject*)						= 0;
		virtual void				SetObjectRange(CLayoutObject*, unsigned int, unsigned int)	= 0;
		virtual unsigned int		GetObjectPreferredSize(CLayoutObject*)						= 0;
		virtual unsigned int		GetLayoutSize()												= 0;
		unsigned int				GetPreferredSize();
		CList<CLayoutObject>		m_Object;

	private:
		CLayoutBase					m_LayoutBase;
		unsigned int				m_nSpacing;

	};

}

#endif
