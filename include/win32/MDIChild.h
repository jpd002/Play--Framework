#ifndef _MDICHILD_H_
#define _MDICHILD_H_

#include "Window.h"

namespace Framework
{

	class CMDIChild : public CWindow
	{
	public:
		void		Create(unsigned long, const xchar*, const xchar*, unsigned long, RECT*, HWND, void*);  

	protected:
		long		OnWndProc(unsigned int, WPARAM, LPARAM);

	};

}

#endif