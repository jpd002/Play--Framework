#ifndef _LISTBOX_H_
#define _LISTBOX_H_

#include "Window.h"

namespace Framework
{

	class CListBox : public CWindow
	{
	public:
				CListBox(HWND, RECT*, unsigned long = 0, unsigned long = WS_EX_CLIENTEDGE);
		void	AddString(const TCHAR*);
		void	ResetContent();

	};

}

#endif
