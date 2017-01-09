#include "win32/PropertyGridEdit.h"
//#include <Uxtheme.h>

using namespace Framework;
using namespace Framework::Win32;

#define EDIT_STYLE		(WS_CLIPCHILDREN | WS_CLIPSIBLINGS | ES_WANTRETURN)

CPropertyGridEdit::CPropertyGridEdit(HWND parentWnd)
: CEdit(parentWnd, CRect(0, 0, 1, 1), _T(""), EDIT_STYLE)
{
	SubClass();
//	SetWindowTheme(m_hWnd, _T(""), _T(""));
}

CPropertyGridEdit::~CPropertyGridEdit()
{

}

LRESULT CPropertyGridEdit::OnWndProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
	case WM_GETDLGCODE:
		return (DLGC_WANTALLKEYS | CallWindowProc(m_baseWndProc, m_hWnd, msg, wparam, lparam));
		break;
	case WM_KILLFOCUS:
		EditCompleted(false);
		break;
	case WM_CHAR:
		if(wparam == VK_RETURN)
		{
			EditCompleted(false);
			return TRUE;
		}
		else if(wparam == VK_ESCAPE)
		{
			//Prevent bell
			return TRUE;
		}
		break;
	case WM_KEYDOWN:
		if(wparam == VK_ESCAPE)
		{
			EditCompleted(true);
			return FALSE;
		}
		break;
	}
	return CallWindowProc(m_baseWndProc, m_hWnd, msg, wparam, lparam);
}
