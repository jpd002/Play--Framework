#ifndef _LISTBOX_H_
#define _LISTBOX_H_

#include "Window.h"

namespace Framework
{
	namespace Win32
	{
		class CListBox : public CWindow
		{
		public:
							CListBox(HWND);
							CListBox(HWND, RECT*, unsigned long = 0, unsigned long = WS_EX_CLIENTEDGE);

			unsigned int	AddString(const TCHAR*);
			void			ResetContent();

			int				GetCurrentSelection();
			void			SetCurrentSelection(unsigned int);

			INT_PTR			GetItemData(unsigned int);
			void			SetItemData(unsigned int, INT_PTR);
		};
	}
}

#endif
