#pragma once

#include "Window.h"

namespace Framework
{
	namespace Win32
	{
		class CMDIChild : public CWindow
		{
		public:
			void		Create(unsigned long, const TCHAR*, const TCHAR*, unsigned long, RECT*, HWND, void*);

		protected:
			long		OnWndProc(unsigned int, WPARAM, LPARAM) override;
		};
	}
}
