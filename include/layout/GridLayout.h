#pragma once

#include "LayoutObject.h"
#include "LayoutBase.h"
#include <vector>

namespace Framework
{
	class CGridLayout;
	typedef std::shared_ptr<CGridLayout> GridLayoutPtr;

	class CGridLayout : public CLayoutObject
	{
	public:
								CGridLayout(unsigned int, unsigned int, unsigned int);
		virtual					~CGridLayout();

		static GridLayoutPtr	Create(unsigned int, unsigned int, unsigned int = LAYOUT_DEFAULT_SPACING);

		unsigned int			GetPreferredWidth() override;
		unsigned int			GetPreferredHeight() override;
		void					RefreshGeometry() override;

		void					SetObject(unsigned int, unsigned int, const LayoutObjectPtr&);

	private:
		typedef std::vector<std::vector<LayoutObjectPtr>> GridArray;

		void					RebuildLayouts();
		CLayoutBaseItem			CreateColLayoutBaseItem(unsigned int) const;
		CLayoutBaseItem			CreateRowLayoutBaseItem(unsigned int) const;

		unsigned int			m_cols;
		unsigned int			m_rows;
		unsigned int			m_spacing;

		GridArray				m_objects;

		CLayoutBase				m_horzLayout;
		CLayoutBase				m_vertLayout;
	};
}
