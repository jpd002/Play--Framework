#ifndef _TREEVIEW_H_
#define _TREEVIEW_H_

#include "Window.h"
#include <commctrl.h>

namespace Framework
{
	namespace Win32
	{
		class CTreeView : public CWindow
		{
		public:
							CTreeView(HWND, RECT*, unsigned long = 0, unsigned long = WS_EX_CLIENTEDGE);
			HTREEITEM		InsertItem(TVINSERTSTRUCT*);
			HTREEITEM		InsertItem(HTREEITEM, const xchar*);
			HTREEITEM		GetSelection();
			bool			GetItem(HTREEITEM, TVITEM*);
			void			GetItemText(HTREEITEM, xchar*, size_t);
			void			GetItemLabelRect(HTREEITEM, RECT*);
			HTREEITEM		GetRoot();
			bool			SetSelection(HTREEITEM);
			bool			Expand(HTREEITEM, unsigned int);
			bool			DeleteAllItems();
		};
	}
}

#endif