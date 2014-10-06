#pragma once

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{

		class CStatusBar : public CWindow
		{
		public:
							CStatusBar(HWND = 0);
			virtual			~CStatusBar();

			CStatusBar&		operator =(CStatusBar&&);

			void			SetText(unsigned int, const TCHAR*);
			void			SetParts(unsigned int, const double*);

			void			RefreshGeometry();

			unsigned int	GetHeight();
			RECT			GetRect();
		};
	}

}
