#include "win32/Button.h"
#include "win32/DefaultFonts.h"

using namespace Framework;
using namespace Framework::Win32;

CButton::CButton(const xchar* sCaption, HWND hParent, RECT* pR, unsigned long nStyle)
{
	Create(NULL, _X("BUTTON"), sCaption, WS_VISIBLE | WS_CHILD | nStyle, pR, hParent, NULL);
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
