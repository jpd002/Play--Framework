#pragma once

#include <list>
#include "LayoutObject.h"
#include "LayoutBase.h"

namespace Framework
{

	class CFlatLayout : public CLayoutObject
	{
	public:
		typedef std::list<LayoutObjectPtr> ObjectList;
		typedef ObjectList::const_iterator ObjectIterator;

									CFlatLayout(unsigned int, unsigned int, unsigned int = LAYOUT_DEFAULT_SPACING);
									CFlatLayout(const CFlatLayout&) = delete;
		virtual						~CFlatLayout();

		CFlatLayout&				operator =(const CFlatLayout&) = delete;

		void						InsertObject(const LayoutObjectPtr&);
		virtual	void				RefreshGeometry() override;

	protected:
		virtual CLayoutBaseItem		CreateLayoutBaseItem(const LayoutObjectPtr&)						= 0;
		virtual void				SetObjectRange(const LayoutObjectPtr&, unsigned int, unsigned int)	= 0;
		virtual unsigned int		GetObjectPreferredSize(const LayoutObjectPtr&)						= 0;
		virtual unsigned int		GetLayoutSize()														= 0;
		unsigned int				GetPreferredSize() const;
		ObjectList					m_objects;

	private:
		CLayoutBase					m_layoutBase;
		unsigned int				m_spacing;
	};

	typedef std::shared_ptr<CFlatLayout> FlatLayoutPtr;
}
