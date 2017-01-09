#include <assert.h>
#include "win32/MDIChild.h"

using namespace Framework;
using namespace Framework::Win32;

void CMDIChild::Create(unsigned long nStyleEx, const TCHAR* sClass, const TCHAR* sWindow, unsigned long nStyle, RECT* pR, HWND hParent, void* pParam)
{
	m_hWnd = CreateMDIWindow(sClass, sWindow, nStyle, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hParent, GetModuleHandle(NULL), (LPARAM)pParam);
	assert(m_hWnd != NULL);
}

LRESULT CMDIChild::OnWndProc(unsigned int nMsg, WPARAM wParam, LPARAM lParam)
{
	return DefMDIChildProc(m_hWnd, nMsg, wParam, lParam);
}
