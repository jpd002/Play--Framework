#ifndef _LISTVIEWEX_H_
#define _LISTVIEWEX_H_

#include "win32/ListView.h"

namespace Framework
{
	namespace Win32
	{
		class CListViewEx : public CListView
		{
		public:
							CListViewEx(HWND, const RECT&, unsigned long = 0, unsigned long = WS_EX_CLIENTEDGE);
							CListViewEx(HWND);
			virtual			~CListViewEx();

		protected:
			virtual	long	OnWndProc(unsigned int, WPARAM, LPARAM);
		};
	};
};

#endif
