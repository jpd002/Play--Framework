#pragma once

#include "Window.h"

namespace Framework
{
	namespace Win32
	{
		class CButton : public CWindow
		{
		public:
						CButton(HWND = 0);
						CButton(const TCHAR*, HWND, const RECT&, unsigned long = 0);

			CButton&	operator =(CButton&&);

			bool		GetCheck();
			void		SetCheck(bool = true);
			void		ResetCheck();

			void		SetBitmap(HBITMAP);
			void		SetIcon(HICON);
		};
	}
}
