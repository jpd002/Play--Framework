#ifndef _HEADER_H_
#define _HEADER_H_

#include "win32/Window.h"
#include <commctrl.h>

namespace Framework
{
	namespace Win32
	{
		class CHeader : public CWindow
		{
		public:
					CHeader(HWND);
					CHeader(HWND, const RECT&, unsigned long = 0, unsigned long = 0);

			void	GetItem(unsigned int, HDITEM*);
			void	SetItem(unsigned int, HDITEM*);

			int		InsertItem(const TCHAR*);
			int		InsertItem(const TCHAR*, unsigned int);
			int		InsertItem(unsigned int, HDITEM*);

			void	GetItemRect(unsigned int, RECT*);
			int		GetItemCount();

			void	SetItemWidth(unsigned int, unsigned int);
			void	SetItemWidth(unsigned int, double);
		};
	}
}

#endif
