#ifndef _MDICHILD_H_
#define _MDICHILD_H_

#include "Window.h"

namespace Framework
{

	class CMDIChild : public CWindow
	{
	public:
		void		Create(unsigned long, const TCHAR*, const TCHAR*, unsigned long, RECT*, HWND, void*);  

	protected:
		long		OnWndProc(unsigned int, WPARAM, LPARAM);

	};

}

#endif