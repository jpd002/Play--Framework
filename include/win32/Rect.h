#pragma once

#include <Windows.h>
#include "Types.h"

namespace Framework
{
	namespace Win32
	{
		class CRect
		{
		public:
						CRect(int, int, int, int);
						CRect(const RECT&);
			virtual		~CRect();

						operator RECT*();
						operator RECT&();

			int			Left() const;
			int			Top() const;
			int			Right() const;
			int			Bottom() const;

			void		SetLeft(int);
			void		SetTop(int);
			void		SetRight(int);
			void		SetBottom(int);

			int			Width() const;
			int			Height() const;

			CRect&		Adjust(uint32, bool = false);
			CRect&		Inflate(int, int);
			CRect&		CenterInside(const CRect&);
			CRect&		ScreenToClient(HWND);
			CRect&		ClientToScreen(HWND);
			bool		PtIn(int, int) const;

		private:
			RECT		m_rect;
		};

		CRect MakeRectPositionSize(int, int, int, int);
	}
}
