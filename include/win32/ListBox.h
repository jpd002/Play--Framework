#pragma once

#include "Window.h"

namespace Framework
{
	namespace Win32
	{
		class CListBox : public CWindow
		{
		public:
							CListBox(HWND = 0);
							CListBox(HWND, const RECT&, unsigned long = 0, unsigned long = WS_EX_CLIENTEDGE);

			CListBox&		operator =(CListBox&&);

			unsigned int	AddString(const TCHAR*);
			void			ResetContent();

			int				GetCurrentSelection();
			void			SetCurrentSelection(unsigned int);

			INT_PTR			GetItemData(unsigned int);
			void			SetItemData(unsigned int, INT_PTR);
		};
	}
}
