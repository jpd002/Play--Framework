#ifndef _EDIT_H_
#define _EDIT_H_

#include "Window.h"

namespace Framework
{
	namespace Win32
	{
		class CEdit : public CWindow
		{
		public:
					CEdit(HWND, unsigned int);
					CEdit(HWND, RECT*, const xchar* = _X(""), unsigned long = 0, unsigned long = WS_EX_CLIENTEDGE);
			void	SetSelection(int, int);
			void	ReplaceSelectionA(bool, const char*);
			void	SetTextLimit(int);
			void	SetLeftMargin(unsigned int);
		};
	}
}

#endif