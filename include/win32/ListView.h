/*

	Framework - ListView.h
	File Version 1.0.000

*/

#ifndef _LISTVIEW_H_
#define _LISTVIEW_H_

#include "Window.h"
#include <commctrl.h>
#include <boost/function.hpp>

namespace Framework
{
	namespace Win32
	{
		class CListView : public virtual CWindow
		{
		public:
			typedef boost::function<void (LVITEM*)> GetDispInfoCallbackType;

            class CItem
            {
            public:
                            CItem(const TCHAR*);
                virtual     ~CItem();

                void        SetText(const TCHAR*);
                void        SetParam(LPARAM);
                operator    const LVITEM&() const;

            private:
                LVITEM      m_Item;
            };

							CListView(HWND, RECT*, unsigned long = 0, unsigned long = WS_EX_CLIENTEDGE);
			virtual			~CListView();

			int				GetItemCount();
			int				FindItemData(unsigned long);
			void			DeleteAllItems();
			int				InsertItem(LVITEM*);
            int             InsertItem(const LVITEM&);
			void			InsertColumn(unsigned int, LVCOLUMN*);

			void			SetItemText(unsigned int, unsigned int, const TCHAR*);
			void			GetItemText(unsigned int, unsigned int, TCHAR*, unsigned int);

			unsigned long	GetItemData(unsigned int);

			int				GetSelection();
			void			SetSelection(int);

            void            EnableGroupView(bool);
            int             InsertGroup(const TCHAR*, unsigned int, unsigned int = -1);
            void            RemoveAllGroups();

			void			SetColumnWidth(unsigned int, unsigned int);

			void			SetExtendedListViewStyle(unsigned long);
			unsigned long	GetExtendedListViewStyle();

			void			SetItemCount(int);

			void			EnsureItemVisible(unsigned int, bool);
			
			void			ProcessGetDisplayInfo(NMHDR*, GetDispInfoCallbackType);

            HWND            GetHeader();
		};
	}
}

#endif