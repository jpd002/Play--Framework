#include "win32/MDIChild.h"

using namespace Framework;

void CMDIChild::Create(unsigned long nStyleEx, const xchar* sClass, const xchar* sWindow, unsigned long nStyle, RECT* pR, HWND hParent, void* pParam)
{
	//m_hWnd = CreateMDIWindow(sClass, sWindow, nStyle, pR->left, pR->top, (pR->right - pR->left), (pR->bottom - pR->top), hParent, GetModuleHandle(NULL), (LPARAM)pParam);
	m_hWnd = CreateMDIWindow(sClass, sWindow, nStyle, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hParent, GetModuleHandle(NULL), (LPARAM)pParam);
}

long CMDIChild::OnWndProc(unsigned int nMsg, WPARAM wParam, LPARAM lParam)
{
	return (long)DefMDIChildProc(m_hWnd, nMsg, wParam, lParam);
}