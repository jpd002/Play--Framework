#ifndef _TREEVIEW_H_
#define _TREEVIEW_H_

#include "Window.h"
#include <commctrl.h>

namespace Framework
{
	namespace Win32
	{
		class CTreeView : public virtual CWindow
		{
		public:
							CTreeView(HWND, const RECT&, unsigned long = 0, unsigned long = WS_EX_CLIENTEDGE);
			HTREEITEM		InsertItem(TVINSERTSTRUCT*);
			HTREEITEM		InsertItem(HTREEITEM, const TCHAR*);
			HTREEITEM		GetSelection();
			bool			GetItem(HTREEITEM, TVITEM*);
			HTREEITEM		GetItemParent(HTREEITEM);
			void			GetItemText(HTREEITEM, TCHAR*, size_t);
			std::tstring	GetItemText(HTREEITEM);
			void*			GetItemParam(HTREEITEM);
			void			GetItemLabelRect(HTREEITEM, RECT*);
			void			SetItem(HTREEITEM, TVITEM*);
			void			SetItemText(HTREEITEM, const TCHAR*);
			void			SetItemParam(HTREEITEM, void*);
			void			SetItemParam(HTREEITEM, unsigned int);
			void			SetImageList(HIMAGELIST);
			HTREEITEM		GetRoot();
			HTREEITEM		GetChild(HTREEITEM);
			HTREEITEM		GetNextSibling(HTREEITEM);
			bool			SetSelection(HTREEITEM);
			bool			Expand(HTREEITEM, unsigned int = TVE_EXPAND);
			void			DeleteChildren(HTREEITEM);
			bool			DeleteAllItems();
			void			SortChildren(HTREEITEM, bool);

			//Some templates
			template <typename Type>
			Type GetItemParam(HTREEITEM hItem)
			{
				TVITEM Item;
				memset(&Item, 0, sizeof(TVITEM));
				Item.hItem  = hItem;
				Item.mask   = TVIF_PARAM;

				GetItem(hItem, &Item);

				return static_cast<Type>(Item.lParam);
			}

			template <typename Type>
			Type* GetItemParamPtr(HTREEITEM hItem)
			{
				return reinterpret_cast<Type*>(GetItemParam(hItem));
			}
		};
	}
}

#endif