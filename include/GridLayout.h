#ifndef _GRIDLAYOUT_H_
#define _GRIDLAYOUT_H_

#include "LayoutObject.h"
#include "LayoutBase.h"

namespace Framework
{

	class CGridLayout : public CLayoutObject
	{
	public:
							CGridLayout(unsigned int, unsigned int, unsigned int = LAYOUT_DEFAULT_SPACING);
							~CGridLayout();

		unsigned int		GetPreferredWidth();
		unsigned int		GetPreferredHeight();
		void				RefreshGeometry();

		void				SetObject(unsigned int, unsigned int, CLayoutObject*);

	private:
		void				RebuildLayouts();
		CLayoutBaseItem*	CreateColLayoutBaseItem(unsigned int);
		CLayoutBaseItem*	CreateRowLayoutBaseItem(unsigned int);

		unsigned int		m_nCols;
		unsigned int		m_nRows;
		unsigned int		m_nSpacing;

		CLayoutObject***	m_pObject;

		CLayoutBase			m_HorzLayout;
		CLayoutBase			m_VertLayout;

	};

}

#endif
