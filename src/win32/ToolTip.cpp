#include "ToolTip.h"
#include <commctrl.h>

using namespace Framework;

CToolTip::CToolTip(HWND hParent)
{
	InitCommonControls();
	m_hWnd = CreateWindowEx(NULL, TOOLTIPS_CLASS, _X(""), WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hParent, NULL, GetModuleHandle(NULL), NULL);
	SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	m_hParent = hParent;
}

void CToolTip::Activate(BOOL nActive)
{
	SendMessage(m_hWnd, TTM_ACTIVATE, nActive, 0);
}

void CToolTip::AddTool(HWND hTool, const xchar* sDescription)
{
	TOOLINFO ti;
	
	memset(&ti, 0, sizeof(TOOLINFO));
	ti.cbSize	= sizeof(TOOLINFO);
	ti.uFlags	= TTF_IDISHWND | TTF_SUBCLASS;
	ti.uId		= (UINT_PTR)hTool;
	ti.lpszText = (LPWSTR)sDescription;

	SendMessage(m_hWnd, TTM_ADDTOOL, NULL, (LPARAM)&ti);
}

void CToolTip::AddTool(RECT* pR, const xchar* sDescription)
{
	TOOLINFO ti;

	memset(&ti, 0, sizeof(TOOLINFO));
	ti.cbSize	= sizeof(TOOLINFO);
	ti.uFlags	= TTF_SUBCLASS;
	ti.uId		= GetToolCount();
	ti.lpszText	= (LPWSTR)sDescription;
	ti.hwnd		= m_hParent;
	CopyRect(&ti.rect, pR);

	SendMessage(m_hWnd, TTM_ADDTOOL, NULL, (LPARAM)&ti);
}

unsigned int CToolTip::GetToolCount()
{
	return (unsigned int)SendMessage(m_hWnd, TTM_GETTOOLCOUNT, NULL, NULL);
}

void CToolTip::DeleteTool(unsigned int nIndex)
{
	TOOLINFO ti;
	memset(&ti, 0, sizeof(TOOLINFO));
	ti.cbSize = sizeof(TOOLINFO);
	SendMessage(m_hWnd, TTM_ENUMTOOLS, nIndex, (LPARAM)&ti);
	SendMessage(m_hWnd, TTM_DELTOOL, NULL, (LPARAM)&ti);
}

void CToolTip::DeleteAllTools()
{
	while(GetToolCount() != 0)
	{
		DeleteTool(0);
	}
}
