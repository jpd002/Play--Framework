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
						CButton(xchar*, HWND, RECT*, unsigned long = 0);
			void		SetCheck(bool = true);
			void		ResetCheck();
		};
	}
}

#endif