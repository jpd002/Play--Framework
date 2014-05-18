#pragma once

#include "Window.h"
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x501
#endif
#include <commctrl.h>

namespace Framework
{
	namespace Win32
	{
		class CListView : public CWindow
		{
		public:
							CListView(HWND = 0);
							CListView(HWND, const RECT&, unsigned long = 0, unsigned long = WS_EX_CLIENTEDGE);
			virtual			~CListView();

			CListView&		operator =(CListView&&);

			int				GetItemCount();
			int				FindItemData(unsigned long);
			void			DeleteItem(unsigned int);
			bool			DeleteColumn(unsigned int);
			void			DeleteAllItems();
			int				InsertItem(const LVITEM&);
			void			InsertColumn(unsigned int, const LVCOLUMN&);

			std::tstring	GetItemText(unsigned int, unsigned int);
			void			SetItemText(unsigned int, unsigned int, const TCHAR*);

			void			SetItemState(unsigned int, unsigned int, unsigned int);

			unsigned long	GetItemData(unsigned int);

			int				GetSelection();
			void			SetSelection(int);

			void			EnableGroupView(bool);
			int				InsertGroup(const TCHAR*, unsigned int, unsigned int = -1);
			void			RemoveAllGroups();

			void			SetColumnWidth(unsigned int, unsigned int);

			void			SetExtendedListViewStyle(unsigned long);
			unsigned long	GetExtendedListViewStyle();

			void			SetItemCount(int);

			void			EnsureItemVisible(unsigned int, bool);
			
			HWND			GetHeader();
		};
	}
}
