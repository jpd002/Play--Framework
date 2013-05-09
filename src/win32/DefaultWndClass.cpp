#include "win32/DefaultWndClass.h"
#include "win32/Window.h"

using namespace Framework;
using namespace Framework::Win32;

#define CLSNAME _T("DefaultWndClass")

const TCHAR* CDefaultWndClass::GetName()
{
	if(!CWindow::DoesWindowClassExist(CLSNAME))
	{
		WNDCLASSEX w;
		memset(&w, 0, sizeof(WNDCLASSEX));
		w.cbSize		= sizeof(WNDCLASSEX);
		w.lpfnWndProc	= CWindow::WndProc;
		w.lpszClassName	= CLSNAME;
		w.hbrBackground	= (HBRUSH)GetSysColorBrush(COLOR_BTNFACE);
		w.hInstance		= GetModuleHandle(NULL);
		w.hCursor		= LoadCursor(NULL, IDC_ARROW);
		RegisterClassEx(&w);
	}

	return CLSNAME;
}
