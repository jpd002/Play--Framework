#include "win32/ToolTip.h"

using namespace Framework::Win32;

CToolTip::CToolTip(HWND hParent)
{
	InitCommonControls();
	m_hWnd = CreateWindowEx(NULL, TOOLTIPS_CLASS, _T(""), WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hParent, NULL, GetModuleHandle(NULL), NULL);
	SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	m_hParent = hParent;
}

void CToolTip::Activate(bool nActive)
{
    SendMessage(m_hWnd, TTM_ACTIVATE, nActive ? TRUE : FALSE, 0);
}

void CToolTip::TrackActivate(unsigned int nId, bool nActive)
{
    TOOLINFO ti;
    memset(&ti, 0, sizeof(TOOLINFO));
    ti.cbSize   = sizeof(TOOLINFO);
    ti.hwnd     = m_hParent;
    ti.uId      = nId;

    SendMessage(m_hWnd, TTM_TRACKACTIVATE, nActive ? TRUE : FALSE, reinterpret_cast<LPARAM>(&ti));    
}

void CToolTip::TrackPosition(int nX, int nY)
{
    SendMessage(m_hWnd, TTM_TRACKPOSITION, 0, MAKELONG(nX, nY));
}

void CToolTip::AddTool(HWND hTool, const TCHAR* sDescription)
{
	TOOLINFO ti;
	
	memset(&ti, 0, sizeof(TOOLINFO));
	ti.cbSize	= sizeof(TOOLINFO);
	ti.uFlags	= TTF_IDISHWND | TTF_SUBCLASS;
	ti.uId		= reinterpret_cast<UINT_PTR>(hTool);
	ti.lpszText = reinterpret_cast<LPWSTR>(const_cast<TCHAR*>(sDescription));
	ti.hwnd		= m_hParent;

	SendMessage(m_hWnd, TTM_ADDTOOL, NULL, (LPARAM)&ti);
}

unsigned int CToolTip::AddTool(const RECT& Rect, const TCHAR* sDescription)
{
	TOOLINFO ti;
    unsigned int nId(GetToolCount());

	memset(&ti, 0, sizeof(TOOLINFO));
	ti.cbSize	= sizeof(TOOLINFO);
	ti.uFlags	= TTF_SUBCLASS;
	ti.uId		= nId;
	ti.lpszText	= reinterpret_cast<LPWSTR>(const_cast<TCHAR*>(sDescription));
	ti.hwnd		= m_hParent;
	CopyRect(&ti.rect, &Rect);

	SendMessage(m_hWnd, TTM_ADDTOOL, NULL, reinterpret_cast<LPARAM>(&ti));

    return nId;
}

unsigned int CToolTip::AddTrackTool(const TCHAR* sText)
{
	TOOLINFO ti;
    unsigned int nId(GetToolCount());

	memset(&ti, 0, sizeof(TOOLINFO));
	ti.cbSize	= sizeof(TOOLINFO);
	ti.uFlags	= TTF_SUBCLASS | TTF_TRACK;
	ti.uId		= nId;
	ti.lpszText	= reinterpret_cast<LPWSTR>(const_cast<TCHAR*>(sText));
	ti.hwnd		= m_hParent;

	SendMessage(m_hWnd, TTM_ADDTOOL, NULL, reinterpret_cast<LPARAM>(&ti));

    return nId;
}

void CToolTip::SetToolText(UINT_PTR nId, const TCHAR* sText)
{
	TOOLINFO ti;
	memset(&ti, 0, sizeof(TOOLINFO));
	ti.cbSize	= sizeof(TOOLINFO);
	ti.uId		= nId;
	ti.lpszText	= reinterpret_cast<LPWSTR>(const_cast<TCHAR*>(sText));
	ti.hwnd		= m_hParent;

	SendMessage(m_hWnd, TTM_UPDATETIPTEXT, NULL, reinterpret_cast<LPARAM>(&ti));
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

TOOLINFO CToolTip::GetTool(UINT_PTR nId)
{
    TOOLINFO ti;
    memset(&ti, 0, sizeof(TOOLINFO));
    ti.cbSize	= sizeof(TOOLINFO);
    ti.hwnd		= m_hParent;
    ti.uId		= nId;

    if(SendMessage(m_hWnd, TTM_GETTOOLINFO, NULL, reinterpret_cast<LPARAM>(&ti)) == FALSE)
    {
		throw std::exception();
    }

    return ti;
}
