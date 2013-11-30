#pragma once

#include "Window.h"

namespace Framework
{
	namespace Win32
	{
		class CEdit : public CWindow
		{
		public:
						CEdit(HWND = 0);
						CEdit(HWND, const RECT&, const TCHAR* = _T(""), unsigned long = 0, unsigned long = WS_EX_CLIENTEDGE);

			CEdit&		operator =(CEdit&&);

			void		SetSelection(int, int);
			void		ReplaceSelectionA(bool, const char*);
			void		SetTextLimit(int);
			void		SetLeftMargin(unsigned int);
		};
	}
}
