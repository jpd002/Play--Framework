#include "win32/Button.h"
#include "win32/DefaultFonts.h"

using namespace Framework;
using namespace Framework::Win32;

CButton::CButton(HWND hWnd)
{
	m_hWnd = hWnd;
}

CButton::CButton(const TCHAR* sCaption, HWND hParent, RECT* pR, unsigned long nStyle)
{
	Create(NULL, _T("BUTTON"), sCaption, WS_VISIBLE | WS_CHILD | nStyle, pR, hParent, NULL);
	SetFont(CDefaultFonts::GetMessageFont());
}

void CButton::SetCheck(bool bChecked)
{
	SendMessage(m_hWnd, BM_SETCHECK, bChecked ? BST_CHECKED : BST_UNCHECKED, NULL);
}

void CButton::ResetCheck()
{
	SetCheck(false);
}

void CButton::SetBitmap(HBITMAP bitmap)
{
	SendMessage(m_hWnd, BM_SETIMAGE, IMAGE_BITMAP, reinterpret_cast<LPARAM>(bitmap));
}

void CButton::SetIcon(HICON icon)
{
	SendMessage(m_hWnd, BM_SETIMAGE, IMAGE_ICON, reinterpret_cast<LPARAM>(icon));
}
