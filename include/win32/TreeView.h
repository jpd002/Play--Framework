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
			HTREEITEM		InsertItem(HTREEITEM, const TCHAR*);
			HTREEITEM		GetSelection();
			bool			GetItem(HTREEITEM, TVITEM*);
            HTREEITEM       GetItemParent(HTREEITEM);
            void			GetItemText(HTREEITEM, TCHAR*, size_t);
            void*           GetItemParam(HTREEITEM);
			void			GetItemLabelRect(HTREEITEM, RECT*);
            void            SetItem(HTREEITEM, TVITEM*);
            void            SetItemText(HTREEITEM, const TCHAR*);
            void            SetItemParam(HTREEITEM, void*);
            HTREEITEM		GetRoot();
			bool			SetSelection(HTREEITEM);
			bool			Expand(HTREEITEM, unsigned int = TVE_EXPAND);
			bool			DeleteAllItems();

            //Some templates
            template <typename Type>
            Type* GetItemParam(HTREEITEM hItem)
            {
                return reinterpret_cast<Type*>(GetItemParam(hItem));   
            }
		};
	}
}

#endif