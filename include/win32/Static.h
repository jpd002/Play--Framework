#ifndef _STATIC_H_
#define _STATIC_H_

#include "Window.h"

namespace Framework
{
	namespace Win32
	{
		class CStatic : public CWindow
		{
		public:
							CStatic(CStatic&&);
							CStatic(HWND = 0);
							CStatic(HWND, const RECT&, unsigned long = 0);
							CStatic(HWND, const TCHAR*, unsigned long = 0);

			CStatic&		operator =(CStatic&&);

			void			SetIcon(HANDLE);
		};
	}
}

#endif
