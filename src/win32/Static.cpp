#include "win32/Static.h"
#include "win32/DefaultFonts.h"

using namespace Framework;
using namespace Framework::Win32;

CStatic::CStatic(HWND hParent, RECT* pR, unsigned long nStyle)
{
	Create(NULL, _X("STATIC"), _X(""), WS_CHILD | WS_VISIBLE | nStyle, pR, hParent, NULL);
}

CStatic::CStatic(HWND hParent, const xchar* sText, unsigned long nStyle)
{
	RECT rc;
	SetRect(&rc, 0, 0, 0, 0);
	Create(NULL, _X("STATIC"), sText, WS_CHILD | WS_VISIBLE | nStyle, &rc, hParent, NULL);
	SetFont(CDefaultFonts::GetMessageFont());
}

void CStatic::SetIcon(HANDLE hIcon)
{
	SendMessage(m_hWnd, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
}
