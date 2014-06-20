#pragma once

#include "win32/Window.h"
#include <commctrl.h>

namespace Framework
{
	namespace Win32
	{
		class CTab : public CWindow
		{
		public:
									CTab(HWND = 0);
									CTab(HWND, const RECT&, unsigned long = 0, unsigned long = 0);
			virtual					~CTab();

			CTab&					operator =(CTab&&);

			int						InsertTab(const TCHAR*);

			std::tstring			GetTabText(int);
			void					SetTabText(int, const TCHAR*);

			LPARAM					GetTabData(int);
			void					SetTabData(int, LPARAM);

			int						GetSelection();
			void					SetSelection(int);
			unsigned int			GetItemCount();
			Framework::Win32::CRect	GetDisplayAreaRect();

		private:

		};
	}
}
