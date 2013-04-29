#ifndef _WIN32_STATUSBAR_H_
#define _WIN32_STATUSBAR_H_

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{

		class CStatusBar : public CWindow
		{
		public:
							CStatusBar(HWND);
			virtual			~CStatusBar();

			void			SetText(unsigned int, const TCHAR*);
			void			SetParts(unsigned int, const double*);

			void			RefreshGeometry();

			unsigned int	GetHeight();
			RECT			GetRect();
		};
	}

}

#endif
