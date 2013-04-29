#include "win32/Static.h"
#include "win32/DefaultFonts.h"

using namespace Framework;
using namespace Framework::Win32;

CStatic::CStatic(HWND hWnd)
{
	m_hWnd = hWnd;
}

CStatic::CStatic(HWND hParent, const RECT& rect, unsigned long nStyle)
{
	Create(NULL, _T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE | nStyle, rect, hParent, NULL);
}

CStatic::CStatic(HWND hParent, const TCHAR* sText, unsigned long nStyle)
{
	Create(NULL, _T("STATIC"), sText, WS_CHILD | WS_VISIBLE | nStyle, Framework::Win32::CRect(0, 0, 0, 0), hParent, NULL);
	SetFont(CDefaultFonts::GetMessageFont());
}

void CStatic::SetIcon(HANDLE hIcon)
{
	SendMessage(m_hWnd, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
}
