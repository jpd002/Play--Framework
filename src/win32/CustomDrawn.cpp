#include "win32/CustomDrawn.h"

using namespace Framework;
using namespace Framework::Win32;

CCustomDrawn::CCustomDrawn()
{
    m_MemDc = NULL;
    m_Bitmap = NULL;
}

CCustomDrawn::~CCustomDrawn()
{
    InvalidateBitmap();
}

long CCustomDrawn::OnPaint()
{
	PAINTSTRUCT ps;
//	HDC hDC;
    HDC hWDC;
	RECT rwin;
//	HBITMAP hBM;

	BeginPaint(m_hWnd, &ps);
	hWDC = ps.hdc;

	GetClientRect(&rwin);

	//hDC = CreateCompatibleDC(hWDC);
	//hBM = CreateCompatibleBitmap(hWDC, rwin.right, rwin.bottom);
	//SelectObject(hDC, hBM);

    if(m_MemDc == NULL)
    {
        RecreateBitmap(hWDC);
    }

	Paint(m_MemDc);

	BitBlt(hWDC, 0, 0, rwin.right, rwin.bottom, m_MemDc, 0, 0, SRCCOPY);

	//DeleteObject(hBM);
	//DeleteDC(hDC);

	EndPaint(m_hWnd, &ps);

	return TRUE;
}

long CCustomDrawn::OnEraseBkgnd()
{
	return TRUE;
}

long CCustomDrawn::OnSize(unsigned int nType, unsigned int nX, unsigned int nY)
{
    InvalidateBitmap();
	Redraw();
	return TRUE;
}

void CCustomDrawn::RecreateBitmap(HDC hWindowDc)
{
    RECT rc;

    if(m_MemDc != NULL) return;

    GetClientRect(&rc);

	m_MemDc = CreateCompatibleDC(hWindowDc);
	m_Bitmap = CreateCompatibleBitmap(hWindowDc, rc.right, rc.bottom);
	SelectObject(m_MemDc, m_Bitmap);
}

void CCustomDrawn::InvalidateBitmap()
{
	DeleteObject(m_Bitmap);
	DeleteDC(m_MemDc);

    m_MemDc = NULL;
}
