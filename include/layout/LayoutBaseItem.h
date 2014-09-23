#pragma once

#include "LayoutObject.h"

namespace Framework
{

	class CLayoutBaseItem
	{
	public:
							CLayoutBaseItem() = default;
							CLayoutBaseItem(unsigned int, unsigned int, const LayoutObjectPtr&);
							CLayoutBaseItem(unsigned int, unsigned int, unsigned int = -1);

		unsigned int		GetPreferredSize()	const;
		unsigned int		GetStretch()		const;
		LayoutObjectPtr		GetObject()			const;
		unsigned int		GetKey()			const;

		unsigned int		GetRangeStart()		const;
		unsigned int		GetRangeEnd()		const;
		void				SetRange(unsigned int, unsigned int);

	private:
		unsigned int		m_preferredSize = 0;
		unsigned int		m_stretch = 0;

		LayoutObjectPtr		m_object;
		unsigned int		m_key = 0;

		unsigned int		m_rangeStart = 0;
		unsigned int		m_rangeEnd = 0;
	};

}
