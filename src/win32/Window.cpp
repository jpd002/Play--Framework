#include "win32/Window.h"
#include <windowsx.h>
#include <assert.h>

using namespace Framework;
using namespace Framework::Win32;

#define PROPNAME		_T("CWindow::this")

CWindow::CWindow()
: m_hWnd(NULL)
, m_baseWndProc(nullptr)
, m_noCallDef(false)
, m_hasClassPtr(false)
{

}

CWindow::~CWindow()
{

}

void CWindow::Reset()
{
	if(m_hWnd && m_hasClassPtr)
	{
		ClearClassPtr();
	}
	m_hWnd = NULL;
	m_baseWndProc = nullptr;
	m_hasClassPtr = false;
	m_noCallDef = false;
}

void CWindow::MoveFrom(CWindow&& rhs)
{
	assert(m_hWnd == NULL);
	std::swap(m_hWnd, rhs.m_hWnd);
	std::swap(m_baseWndProc, rhs.m_baseWndProc);
	std::swap(m_hasClassPtr, rhs.m_hasClassPtr);
	std::swap(m_noCallDef, rhs.m_noCallDef);
	if(m_hasClassPtr)
	{
		SetClassPtr();
	}
}

CWindow::operator HWND() const
{
	return m_hWnd;
}

void CWindow::StdMsgLoop(CWindow& window)
{
	while(window.IsWindow())
	{
		MSG m;
		GetMessage(&m, NULL, NULL, NULL);
		TranslateMessage(&m);
		DispatchMessage(&m);
	}
}

void CWindow::DlgMsgLoop(CWindow& window)
{
	while(window.IsWindow())
	{
		MSG m;
		GetMessage(&m, NULL, NULL, NULL);
		if(!IsDialogMessage(window.m_hWnd, &m))
		{
			TranslateMessage(&m);
			DispatchMessage(&m);
		}
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
	m_hasClassPtr = true;
}

void CWindow::ClearClassPtr()
{
	assert(m_hasClassPtr == true);
	SetProp(m_hWnd, PROPNAME, NULL);
	m_hasClassPtr = false;
}

CWindow* CWindow::GetClassPtr(HWND hWnd)
{
	return reinterpret_cast<CWindow*>(GetProp(hWnd, PROPNAME));
}

void CWindow::SubClass()
{
	SetClassPtr();
	m_baseWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(SubClassWndProc)));
}

long CWindow::CallBaseWndProc(unsigned int uiMsg, WPARAM wParam, LPARAM lParam)
{
	return (long)CallWindowProc(m_baseWndProc, m_hWnd, uiMsg, wParam, lParam);
}

bool CWindow::DoesWindowClassExist(const TCHAR* className)
{
	WNDCLASS wc;
	return GetClassInfo(GetModuleHandle(NULL), className, &wc) != 0;
}

bool CWindow::IsNotifySource(const CWindow* pWindow, const NMHDR* pHdr)
{
	return (pWindow != NULL) && (pWindow->m_hWnd == pHdr->hwndFrom);
}

bool CWindow::IsCommandSource(const CWindow* pWindow, HWND hWndFrom)
{
	return (pWindow != NULL) && (pWindow->m_hWnd == hWndFrom);
}

///////////////////////////////////////////////////////////
//Window Message Helpers
///////////////////////////////////////////////////////////

void CWindow::Create(unsigned long nStyleEx, const TCHAR* sClass, const TCHAR* sWindow, unsigned long nStyle, const CRect& rect, HWND hParent, void* pParam)
{
	m_hWnd = CreateWindowEx(nStyleEx, sClass, sWindow, nStyle, rect.Left(), rect.Top(), rect.Width(), rect.Height(), 
		hParent, NULL, GetModuleHandle(NULL), pParam);
	assert(m_hWnd != NULL);
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

std::tstring CWindow::GetText()
{
	TCHAR* sBuffer;
	unsigned int nLength(GetTextLength() + 1);
	sBuffer = reinterpret_cast<TCHAR*>(_alloca(sizeof(TCHAR) * nLength));
	GetText(sBuffer, nLength);
	return std::tstring(sBuffer);
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

CRect CWindow::GetClientRect()
{
	RECT rect;
	::GetClientRect(m_hWnd, &rect);
	return rect;
}

CRect CWindow::GetWindowRect()
{
	RECT rect;
	::GetWindowRect(m_hWnd, &rect);
	return rect;
}

void CWindow::Center(HWND hParent)
{
	RECT rParent;

	RECT rWindow = GetWindowRect();
	if(hParent == NULL)
	{
		SetRect(&rParent, 0, 0, GetDeviceCaps(GetDC(NULL), HORZRES), GetDeviceCaps(GetDC(NULL), VERTRES));
	}
	else
	{
		::GetClientRect(hParent, &rParent);
	}

	POINT result;
	result.x = (rParent.right - (rWindow.right - rWindow.left)) / 2;
	result.y = (rParent.bottom - (rWindow.bottom - rWindow.top)) / 2;

	if(hParent != NULL)
	{
		POINT origin;
		origin.x = 0;
		origin.y = 0;
		ClientToScreen(hParent, &origin);
		result.x += origin.x;
		result.y += origin.y;
	}

	SetWindowPos(m_hWnd, NULL, result.x, result.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void CWindow::SetSize(unsigned int nWidth, unsigned int nHeight)
{
	SetWindowPos(m_hWnd, NULL, 0, 0, nWidth, nHeight, SWP_NOMOVE | SWP_NOZORDER);
}

void CWindow::SetPosition(unsigned int nX, unsigned int nY)
{
	SetWindowPos(m_hWnd, NULL, nX, nY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void CWindow::SetSizePosition(const CRect& rect)
{
	SetWindowPos(m_hWnd, NULL, rect.Left(), rect.Top(), rect.Width(), rect.Height(), SWP_NOZORDER);
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

CScrollBar CWindow::GetVerticalScrollBar()
{
	return CScrollBar(m_hWnd, SB_VERT);
}

CScrollBar CWindow::GetHorizontalScrollBar()
{
	return CScrollBar(m_hWnd, SB_HORZ);
}

///////////////////////////////////////////////////////////
//Window Message Handlers
///////////////////////////////////////////////////////////

LRESULT WINAPI CWindow::WndProc(HWND hWnd, unsigned int uiMsg, WPARAM wParam, LPARAM lParam)
{
	if(uiMsg == WM_NCCREATE)
	{
		CWindow* window(NULL);
		bool foundWnd = false;

		HWND parentWnd = ::GetParent(hWnd);
		if(parentWnd != NULL)
		{
			TCHAR className[255];
			GetClassName(parentWnd, className, 255);
			if(!_tcsicmp(className, _T("MDIClient")))
			{
				CREATESTRUCT* createStruct(reinterpret_cast<CREATESTRUCT*>(lParam));
				MDICREATESTRUCT* mdiCreateStruct(reinterpret_cast<MDICREATESTRUCT*>(createStruct->lpCreateParams));
				window = reinterpret_cast<CWindow*>(mdiCreateStruct->lParam);
				foundWnd = true;
			}
		}

		if(!foundWnd)
		{
			CREATESTRUCT* createStruct(reinterpret_cast<CREATESTRUCT*>(lParam));
			window = reinterpret_cast<CWindow*>(createStruct->lpCreateParams);
		}

		if(window != NULL)
		{
			window->m_hWnd = hWnd;
			window->SetClassPtr();
		}
	}
	CWindow* pThis = GetClassPtr(hWnd);
	if(pThis == NULL)
	{
		return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}
	switch(uiMsg)
	{
	case WM_CLOSE:
		if(!pThis->OnClose()) return FALSE;
		break;
	case WM_SYSCOMMAND:
		if(!pThis->OnSysCommand((unsigned int)wParam, lParam)) return FALSE;
		break;
	case WM_SIZE:
		if(!pThis->OnSize((unsigned int)wParam, LOWORD(lParam), HIWORD(lParam))) return FALSE;
		break;
	case WM_MOVE:
		if(!pThis->OnMove(LOWORD(lParam), HIWORD(lParam))) return FALSE;
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
		{
			long nRet = pThis->OnEraseBkgnd();
			if(nRet != 0) return nRet;
		}
		break;
	case WM_KEYDOWN:
		if(!pThis->OnKeyDown(wParam, lParam)) return FALSE;
		break;
	case WM_KEYUP:
		if(!pThis->OnKeyUp(wParam, lParam)) return FALSE;
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
		pThis->OnTimer(wParam);
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
	case WM_RBUTTONDOWN:
		if(!pThis->OnRightButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))) return FALSE;
		break;
	case WM_RBUTTONUP:
		if(!pThis->OnRightButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))) return FALSE;
		break;
	case WM_MOUSEWHEEL:
		if(!pThis->OnMouseWheel(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), GET_WHEEL_DELTA_WPARAM(wParam))) return FALSE;
		break;
	case WM_MOUSELEAVE:
		if(!pThis->OnMouseLeave()) return FALSE;
		break;
	case WM_DESTROY:
		if(!pThis->OnDestroy()) return FALSE;
		break;
	case WM_NCDESTROY:
		//Window Handle not valid after this
		pThis->m_hWnd = NULL;
		break;
	case WM_CTLCOLORSTATIC:
		{
			long nBrush = pThis->OnCtlColorStatic((HDC)wParam, (HWND)lParam);
			if(!nBrush)
			{
				return (long)DefWindowProc(hWnd, uiMsg, wParam, lParam);
			}
			else
			{
				return nBrush;
			}
		}
		break;
	case WM_ACTIVATE:
		if(!pThis->OnActivate(LOWORD(wParam), HIWORD(wParam) != 0, (HWND)lParam)) return FALSE;
		break;
	case WM_MOUSEACTIVATE:
		return pThis->OnMouseActivate(wParam, lParam);
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
	case WM_NCCALCSIZE:
		if(!pThis->OnNcCalcSize(wParam, lParam)) return FALSE;
		break;
	case WM_NCPAINT:
		if(!pThis->OnNcPaint(wParam)) return FALSE;
		break;
	case WM_GETDLGCODE:
		return pThis->OnGetDlgCode(wParam, lParam);
		break;
	case WM_THEMECHANGED:
		if(!pThis->OnThemeChanged()) return FALSE;
		break;
	}
	if(!pThis->OnWndProc(uiMsg, wParam, lParam)) return FALSE;
	if(!pThis->m_noCallDef)
	{
		return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}
	return TRUE;
}

LRESULT WINAPI CWindow::SubClassWndProc(HWND hWnd, unsigned int uiMsg, WPARAM wParam, LPARAM lParam)
{
	CWindow* pThis = GetClassPtr(hWnd);
	if(pThis != NULL)
	{
		return pThis->OnWndProc(uiMsg, wParam, lParam);
	}
	//Probably isn't good if we get here...
	return DefWindowProc(hWnd, uiMsg, wParam, lParam);
}

long CWindow::OnWndProc(UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

long CWindow::OnClose()
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

long CWindow::OnMove(int x, int y)
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

long CWindow::OnRightButtonDown(int nX, int nY)
{
	return TRUE;
}

long CWindow::OnRightButtonUp(int nX, int nY)
{
	return TRUE;
}

long CWindow::OnMouseWheel(int x, int y, short z)
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

long CWindow::OnTimer(WPARAM)
{
	return TRUE;
}

long CWindow::OnEraseBkgnd()
{
	return FALSE;
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

long CWindow::OnKeyDown(WPARAM, LPARAM)
{
	return TRUE;
}

long CWindow::OnKeyUp(WPARAM, LPARAM)
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

long CWindow::OnMouseActivate(WPARAM wParam, LPARAM lParam)
{
	return static_cast<long>(DefWindowProc(m_hWnd, WM_MOUSEACTIVATE, wParam, lParam));
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

long CWindow::OnNcCalcSize(WPARAM, LPARAM)
{
	return TRUE;
}

long CWindow::OnNcPaint(WPARAM)
{
	return TRUE;
}

long CWindow::OnGetDlgCode(WPARAM wParam, LPARAM lParam)
{
	return static_cast<long>(DefWindowProc(m_hWnd, WM_GETDLGCODE, wParam, lParam));
}

long CWindow::OnThemeChanged()
{
	return TRUE;
}
