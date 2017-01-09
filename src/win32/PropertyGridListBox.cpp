#include <windowsx.h>
#include "win32/PropertyGridListBox.h"

using namespace Framework;
using namespace Framework::Win32;

#define LISTBOX_STYLE	(WS_CLIPCHILDREN | WS_CLIPSIBLINGS | LBS_NOTIFY | LBS_OWNERDRAWFIXED | LBS_NOINTEGRALHEIGHT | LBS_WANTKEYBOARDINPUT)

CPropertyGridListBox::CPropertyGridListBox(HWND parentWnd)
: CListBox(parentWnd, CRect(0, 0, 1, 1), LISTBOX_STYLE)
{
	SubClass();
//	SetWindowTheme(m_hWnd, _T(""), _T(""));
}

CPropertyGridListBox::~CPropertyGridListBox()
{

}

LRESULT CPropertyGridListBox::OnWndProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
	case WM_GETDLGCODE:
		return (DLGC_WANTALLKEYS | CallWindowProc(m_baseWndProc, m_hWnd, msg, wparam, lparam));
		break;
	case WM_LBUTTONDOWN:
		return OnLeftButtonDown(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;
	case WM_LBUTTONUP:
		return OnLeftButtonUp(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;
	}
	return CallWindowProc(m_baseWndProc, m_hWnd, msg, wparam, lparam);
}

long CPropertyGridListBox::OnLeftButtonDown(int x, int y)
{
	return FALSE;
}

long CPropertyGridListBox::OnLeftButtonUp(int x, int y)
{
	auto itemFromPointInfo = SendMessage(m_hWnd, LB_ITEMFROMPOINT, 0, MAKELPARAM(x, y));

	bool outside = HIWORD(itemFromPointInfo) != 0;

	if(outside) return FALSE;

	unsigned int itemIndex = LOWORD(itemFromPointInfo);

	if(GetCurrentSelection() != itemIndex)
	{
		SetCurrentSelection(itemIndex);
	}

	SetFocus();
	StartEdition(itemIndex);

	return FALSE;
}
