#include "win32/ListViewEx.h"

using namespace Framework;
using namespace Framework::Win32;

CListViewEx::CListViewEx(HWND hWnd)
: CListView(hWnd)
{
	SubClass();
}

CListViewEx::CListViewEx(HWND hParent, const RECT& rect, unsigned long nStyle, unsigned long nExStyle)
: CListView(hParent, rect, nStyle, nExStyle)
{
	SubClass();
}

CListViewEx::~CListViewEx()
{

}

long CListViewEx::OnWndProc(unsigned int nMsg, WPARAM wParam, LPARAM lParam)
{
	switch(nMsg)
	{
	case WM_ERASEBKGND:
		return TRUE;
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(m_hWnd, &ps);
			HDC hWDC = ps.hdc;

			RECT rwin = GetClientRect();

			HDC hDC = CreateCompatibleDC(hWDC);
			HBITMAP hBM = CreateCompatibleBitmap(hWDC, rwin.right, rwin.bottom);
			SelectObject(hDC, hBM);

			SetBkColor(hDC, GetSysColor(COLOR_WINDOW));
			ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rwin, NULL, 0, NULL);

			FillRect(hDC, &rwin, reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));

			CallWindowProc(m_pBaseWndProc, m_hWnd, WM_PAINT, (WPARAM)hDC, 0);

			BitBlt(hWDC, 0, 0, rwin.right, rwin.bottom, hDC, 0, 0, SRCCOPY);

			DeleteObject(hBM);
			DeleteDC(hDC);

			EndPaint(m_hWnd, &ps);

			HWND headerCtrl = GetHeader();
			if(::IsWindow(headerCtrl))
			{
				RECT headerRect;
				::GetClientRect(headerCtrl, &headerRect);
				RedrawWindow(headerCtrl, &headerRect, NULL, RDW_ERASE | RDW_UPDATENOW | RDW_INVALIDATE);
			}

			return TRUE;
		}

		break;
	}

	return static_cast<long>(CallWindowProc(m_pBaseWndProc, m_hWnd, nMsg, wParam, lParam));
}
