#pragma once

#include <memory>

#define LAYOUT_DEFAULT_SPACING	(5)

namespace Framework
{
	class CLayoutBaseItem;
	
	class CLayoutObject : public std::enable_shared_from_this<CLayoutObject>
	{
	public:
								CLayoutObject(unsigned int, unsigned int);
		virtual					~CLayoutObject();

		virtual unsigned int	GetPreferredWidth()		= 0;
		virtual unsigned int	GetPreferredHeight()	= 0;
		virtual void			RefreshGeometry()		= 0;

		void					SetHorizontalStretch(unsigned int);
		void					SetVerticalStretch(unsigned int);

		unsigned int			GetHorizontalStretch()	const;
		unsigned int			GetVerticalStretch()	const;
		
		void					SetLeft(unsigned int);
		void					SetRight(unsigned int);
		void					SetTop(unsigned int);
		void					SetBottom(unsigned int);
		void					SetRect(unsigned int, unsigned int, unsigned int, unsigned int);

		unsigned int			GetLeft()		const;
		unsigned int			GetRight()		const;
		unsigned int			GetTop()		const;
		unsigned int			GetBottom()		const;

		CLayoutBaseItem			CreateHorizontalBaseLayoutItem();
		CLayoutBaseItem			CreateVerticalBaseLayoutItem();

	private:

		unsigned int			m_left = 0;
		unsigned int			m_right = 0;
		unsigned int			m_top = 0;
		unsigned int			m_bottom = 0;

		unsigned int			m_horizontalStretch = 0;
		unsigned int			m_verticalStretch = 0;
	};

	typedef std::shared_ptr<CLayoutObject> LayoutObjectPtr;
};
