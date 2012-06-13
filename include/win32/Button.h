#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Window.h"

namespace Framework
{
	namespace Win32
	{
		class CButton : public CWindow
		{
		public:
						CButton(HWND);
						CButton(const TCHAR*, HWND, RECT*, unsigned long = 0);

			bool		GetCheck();
			void		SetCheck(bool = true);
			void		ResetCheck();

			void		SetBitmap(HBITMAP);
			void		SetIcon(HICON);
		};
	}
}

#endif