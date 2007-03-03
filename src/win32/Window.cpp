/*

	Framework - Window.cpp
	File Version 1.0.000

*/

#include "win32/Window.h"
#include <windowsx.h>

using namespace Framework;
using namespace Framework::Win32;

#define PROPNAME		_T("CWindow::this")

ATOM			CWindow::m_nAtom;

CWindow::CWindow()
{
	m_nNoCallDef = 0;
	m_hWnd = 0;
}

CWindow::~CWindow()
{

}

CWindow::operator HWND()
{
	return m_hWnd;
}

void CWindow::StdMsgLoop(CWindow* pW)
{
	MSG m;
	while(pW->IsWindow())
	{
		GetMessage(&m, NULL, NULL, NULL);
		TranslateMessage(&m);
		DispatchMessage(&m);
	}
}

int CWindow::MessageBoxFormat(HWND hWnd, unsigned int nType, const TCHAR* sTitle, const TCHAR* sFormat, ...)
{
	TCHAR sMessage[256];
	va_list Args;

	va_start(Args, sFormat);
	_vsntprintf(sMessage, 256, sFormat, Args);
	va_end(Args);

	return MessageBox(hWnd, sMessage, sTitle, nType);
}

void CWindow::SetClassPtr()
{
	SetProp(m_hWnd, PROPNAME, this);
}

void CWindow::ClearClassPtr()
{
	SetProp(m_hWnd, PROPNAME, NULL);
}

void CWindow::SubClass()
{
	SetClassPtr();
#pragma warning(push)
#pragma warning(disable : 4311)
#pragma warning(disable : 4312)
	m_pBaseWndProc = (WNDPROC)SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (LONG)SubClassWndProc);
#pragma warning(pop)
}

long CWindow::CallBaseWndProc(unsigned int uiMsg, WPARAM wParam, LPARAM lParam)
{
	return (long)CallWindowProc(m_pBaseWndProc, m_hWnd, uiMsg, wParam, lParam);
}

void CWindow::Initialize()
{
	m_nAtom = GlobalAddAtom(PROPNAME);
}

void CWindow::Release()
{
	GlobalDeleteAtom(m_nAtom);
}

unsigned int CWindow::DoesWindowClassExist(const TCHAR* sClass)
{
	WNDCLASS wc;
	return GetClassInfo(GetModuleHandle(NULL), sClass, &wc);
}

///////////////////////////////////////////////////////////
//Window Message Helpers
///////////////////////////////////////////////////////////

void CWindow::Create(unsigned long nStyleEx, const TCHAR* sClass, const TCHAR* sWindow, unsigned long nStyle, RECT* pR, HWND hParent, void* pParam)
{
	m_hWnd = CreateWindowEx(nStyleEx, sClass, sWindow, nStyle, pR->left, pR->top, (pR->right - pR->left), (pR->bottom - pR->top), hParent, NULL, GetModuleHandle(NULL), pParam);
}

bool CWindow::IsWindow()
{
	return (::IsWindow(m_hWnd) ? true : false);
}

bool CWindow::IsVisible()
{
	long nStyle;
	nStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	if(nStyle & WS_VISIBLE) return true;
	return false;
}

unsigned int CWindow::Destroy()
{
	return DestroyWindow(m_hWnd);
}

unsigned int CWindow::Show(int nMode)
{
	return ShowWindow(m_hWnd, nMode);
}

unsigned int CWindow::Enable(unsigned int nEnable)
{
	return EnableWindow(m_hWnd, nEnable);
}

int CWindow::GetText(TCHAR* sText, int nMax)
{
	return GetWindowText(m_hWnd, sText, nMax);
}

unsigned int CWindow::GetTextLength()
{
	return (unsigned int)SendMessage(m_hWnd, WM_GETTEXTLENGTH, 0, 0);
}

unsigned int CWindow::SetText(const TCHAR* sText)
{
	return SetWindowText(m_hWnd, sText);
}

unsigned int CWindow::SetTextA(const char* sText)
{
	return SetWindowTextA(m_hWnd, sText);
}

void CWindow::SetFocus()
{
	::SetFocus(m_hWnd);
}

void CWindow::SetFont(HFONT nFont)
{
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)nFont, TRUE);
}

HFONT CWindow::GetFont()
{
	return reinterpret_cast<HFONT>(SendMessage(m_hWnd, WM_GETFONT, 0, 0));
}

void CWindow::SetMenu(HMENU nMenu)
{
	::SetMenu(m_hWnd, nMenu);
}

void CWindow::SetIcon(unsigned int nWhich, HICON nIcon)
{
	SendMessage(m_hWnd, WM_SETICON, nWhich, (LPARAM)nIcon);
}

HWND CWindow::GetParent()
{
	return ::GetParent(m_hWnd);
}

void CWindow::GetClientRect(RECT* pR)
{
	::GetClientRect(m_hWnd, pR);
}

void CWindow::GetWindowRect(RECT* pR)
{
	::GetWindowRect(m_hWnd, pR);
}

RECT CWindow::GetClientRect()
{
    RECT Rect;
    ::GetClientRect(m_hWnd, &Rect);
    return Rect;
}

void CWindow::Center(HWND hParent)
{
	RECT rParent;
	RECT rWindow;

	GetWindowRect(&rWindow);
	if(hParent == NULL)
	{
		SetRect(&rParent, 0, 0, GetDeviceCaps(GetDC(NULL), HORZRES), GetDeviceCaps(GetDC(NULL), VERTRES));
	}
	else
	{
		::GetClientRect(hParent, &rParent);
	}

	SetWindowPos(m_hWnd, NULL, (rParent.right - (rWindow.right - rWindow.left)) / 2, (rParent.bottom - (rWindow.bottom - rWindow.top)) / 2, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

}

void CWindow::SetSize(unsigned int nWidth, unsigned int nHeight)
{
	SetWindowPos(m_hWnd, NULL, 0, 0, nWidth, nHeight, SWP_NOMOVE | SWP_NOZORDER);
}

void CWindow::SetPosition(unsigned int nX, unsigned int nY)
{
	SetWindowPos(m_hWnd, NULL, nX, nY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void CWindow::SetSizePosition(RECT* pRect)
{
	SetWindowPos(m_hWnd, NULL, pRect->left, pRect->top, pRect->right - pRect->left, pRect->bottom - pRect->top, SWP_NOZORDER);
}

void CWindow::Redraw()
{
	RedrawWindow(m_hWnd, NULL, NULL, RDW_ERASE | RDW_UPDATENOW | RDW_INVALIDATE);
}

void CWindow::ModifyStyleOr(unsigned long nStyleBit)
{
	SetWindowLong(m_hWnd, GWL_STYLE, GetWindowLong(m_hWnd, GWL_STYLE) | nStyleBit);
}

void CWindow::SetRedraw(bool nRedrawAllowed)
{
	SendMessage(m_hWnd, WM_SETREDRAW, (nRedrawAllowed) ? TRUE : FALSE, 0);
}

unsigned int CWindow::GetScrollThumbPosition(int nBar)
{
	SCROLLINFO si;
	memset(&si, 0, sizeof(SCROLLINFO));
	si.cbSize	= sizeof(SCROLLINFO);
	si.fMask	= SIF_TRACKPOS;
	GetScrollInfo(m_hWnd, nBar, &si);
	return si.nTrackPos;
}

///////////////////////////////////////////////////////////
//Window Message Handlers
///////////////////////////////////////////////////////////

LRESULT WINAPI CWindow::WndProc(HWND hWnd, unsigned int uiMsg, WPARAM wParam, LPARAM lParam)
{
	CWindow* pThis;
	pThis = (CWindow*)GetProp(hWnd, PROPNAME);
	if(pThis == NULL)
	{
		return (long)DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}
	switch(uiMsg)
	{
	case WM_SYSCOMMAND:
		if(!pThis->OnSysCommand((unsigned int)wParam, lParam)) return FALSE;
		break;
	case WM_SIZE:
		if(!pThis->OnSize((unsigned int)wParam, LOWORD(lParam), HIWORD(lParam))) return FALSE;
		break;
	case WM_SETFOCUS:
		pThis->OnSetFocus();
		break;
	case WM_KILLFOCUS:
		pThis->OnKillFocus();
		break;
	case WM_PAINT:
		if(!pThis->OnPaint()) return FALSE;
		break;
	case WM_ERASEBKGND:
		if(!pThis->OnEraseBkgnd()) return FALSE;
		break;
	case WM_KEYDOWN:
		if(!pThis->OnKeyDown((unsigned int)wParam)) return FALSE;
		break;
	case WM_KEYUP:
		if(!pThis->OnKeyUp((unsigned int)wParam)) return FALSE;
		break;
	case WM_SYSKEYDOWN:
		if(!pThis->OnSysKeyDown((unsigned int)wParam)) return FALSE;
		break;
	case WM_COMMAND:
		if(!pThis->OnCommand(LOWORD(wParam), HIWORD(wParam), (HWND)lParam)) return FALSE;
		break;
	case WM_NOTIFY:
		return pThis->OnNotify(wParam, (NMHDR*)lParam);
		break;
	case WM_TIMER:
		pThis->OnTimer();
		return FALSE;
		break;
	case WM_HSCROLL:
		if(!pThis->OnHScroll(LOWORD(wParam), HIWORD(wParam))) return FALSE;
		break;
	case WM_VSCROLL:
		if(!pThis->OnVScroll(LOWORD(wParam), HIWORD(wParam))) return FALSE;
		break;
	case WM_MOUSEMOVE:
		if(!pThis->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))) return FALSE;
		break;
	case WM_LBUTTONDOWN:
		if(!pThis->OnLeftButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))) return FALSE;
		break;
	case WM_LBUTTONUP:
		if(!pThis->OnLeftButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))) return FALSE;
		break;
	case WM_LBUTTONDBLCLK:
		if(!pThis->OnLeftButtonDblClk(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))) return FALSE;
		break;
	case WM_RBUTTONUP:
		if(!pThis->OnRightButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))) return FALSE;
		break;
	case 0x20A:
		if(!pThis->OnMouseWheel((short)HIWORD(wParam))) return FALSE;
		break;
	case WM_MOUSELEAVE:
		if(!pThis->OnMouseLeave()) return FALSE;
		break;
	case WM_DESTROY:
		if(!pThis->OnDestroy()) return FALSE;
		break;
	case WM_CTLCOLORSTATIC:
		long nBrush;
		nBrush = pThis->OnCtlColorStatic((HDC)wParam, (HWND)lParam);
		if(!nBrush)
		{
			return (long)DefWindowProc(hWnd, uiMsg, wParam, lParam);
		}
		else
		{
			return nBrush;
		}
		break;
	case WM_ACTIVATE:
		if(!pThis->OnActivate(LOWORD(wParam), HIWORD(wParam) != 0, (HWND)lParam)) return FALSE;
		break;
	case WM_ACTIVATEAPP:
		if(!pThis->OnActivateApp(LOWORD(wParam) != 0, (unsigned long)lParam)) return FALSE;
		break;
	case WM_SETCURSOR:
		if(!pThis->OnSetCursor((HWND)wParam, LOWORD(lParam), HIWORD(lParam))) return FALSE;
		break;
	case WM_DRAWITEM:
		if(pThis->OnDrawItem((unsigned int)wParam, (LPDRAWITEMSTRUCT)lParam)) return TRUE;
		break;
    case WM_COPY:
        pThis->OnCopy();
        return TRUE;
        break;
	}
	if(!pThis->OnWndProc(uiMsg, wParam, lParam)) return FALSE;
	if(!pThis->m_nNoCallDef)
	{
		return (long)DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}
	return TRUE;
}

LRESULT WINAPI CWindow::SubClassWndProc(HWND hWnd, unsigned int uiMsg, WPARAM wParam, LPARAM lParam)
{
	CWindow* pThis;
	pThis = (CWindow*)GetProp(hWnd, PROPNAME);
	if(pThis != NULL)
	{
		return pThis->OnWndProc(uiMsg, wParam, lParam);
	}
	//Probably isn't good if we get there...
	return DefWindowProc(hWnd, uiMsg, wParam, lParam);
}

long CWindow::OnWndProc(unsigned int uiMsg, WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

long CWindow::OnCommand(unsigned short nID, unsigned short nMsg, HWND hWnd)
{
	return TRUE;
}

long CWindow::OnSysCommand(unsigned int nCmd, LPARAM lParam)
{
	return TRUE;
}

long CWindow::OnNotify(WPARAM wParam, NMHDR* pHDR)
{
	return FALSE;
}

long CWindow::OnSize(unsigned int nType, unsigned int nWidth, unsigned int nHeight)
{
	return TRUE;
}

long CWindow::OnMouseLeave()
{
	return TRUE;
}

long CWindow::OnMouseMove(WPARAM nButton, int nX, int nY)
{
	return TRUE;
}

long CWindow::OnLeftButtonDown(int nX, int nY)
{
	return TRUE;
}

long CWindow::OnLeftButtonUp(int nX, int nY)
{
	return TRUE;
}

long CWindow::OnLeftButtonDblClk(int nX, int nY)
{
	return TRUE;
}

long CWindow::OnRightButtonUp(int nX, int nY)
{
	return TRUE;
}

long CWindow::OnMouseWheel(short nZ)
{
	return TRUE;
}

long CWindow::OnDestroy()
{
	return TRUE;
}

long CWindow::OnPaint()
{
	return TRUE;
}

long CWindow::OnTimer()
{
	return TRUE;
}

long CWindow::OnEraseBkgnd()
{
	return TRUE;
}

long CWindow::OnVScroll(unsigned int nType, unsigned int nTrackPos)
{
	return TRUE;
}

long CWindow::OnHScroll(unsigned int nType, unsigned int nTrackPos)
{
	return TRUE;
}

long CWindow::OnSysKeyDown(unsigned int nKey)
{
	return TRUE;
}

long CWindow::OnKeyDown(unsigned int nKey)
{
	return TRUE;
}

long CWindow::OnKeyUp(unsigned int nKey)
{
	return TRUE;
}

long CWindow::OnKillFocus()
{
	return TRUE;
}

long CWindow::OnSetFocus()
{
	return TRUE;
}

long CWindow::OnCtlColorStatic(HDC hDC, HWND hWnd)
{
	return FALSE;
}

long CWindow::OnActivate(unsigned int nType, bool bMinimized, HWND hWnd)
{
	return TRUE;
}

long CWindow::OnActivateApp(bool nActive, DWORD nThreadId)
{
	return TRUE;
}

long CWindow::OnSetCursor(HWND hWndFrom, unsigned int nHitTest, unsigned int nMsgId)
{
	return TRUE;
}

long CWindow::OnDrawItem(unsigned int nId, LPDRAWITEMSTRUCT pDrawItem)
{
	return FALSE;
}

long CWindow::OnCopy()
{
    return TRUE;
}
