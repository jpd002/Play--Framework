#include "win32/CustomDrawn.h"

using namespace Framework;

long CCustomDrawn::OnPaint()
{
	PAINTSTRUCT ps;
	HDC hWDC, hDC;
	RECT rwin;
	HBITMAP hBM;

	BeginPaint(m_hWnd, &ps);
	hWDC = ps.hdc;

	GetClientRect(&rwin);

	hDC = CreateCompatibleDC(hWDC);
	hBM = CreateCompatibleBitmap(hWDC, rwin.right, rwin.bottom);
	SelectObject(hDC, hBM);

	Paint(hDC);

	BitBlt(hWDC, 0, 0, rwin.right, rwin.bottom, hDC, 0, 0, SRCCOPY);

	DeleteObject(hBM);
	DeleteDC(hDC);

	EndPaint(m_hWnd, &ps);

	return TRUE;
}

long CCustomDrawn::OnEraseBkgnd()
{
	return FALSE;
}

long CCustomDrawn::OnSize(unsigned int nType, unsigned int nX, unsigned int nY)
{
	Redraw();
	return TRUE;
}
