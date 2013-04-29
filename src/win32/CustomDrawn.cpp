#include "win32/CustomDrawn.h"

using namespace Framework;
using namespace Framework::Win32;

CCustomDrawn::CCustomDrawn()
: m_MemDc(NULL)
, m_Bitmap(NULL)
{

}

CCustomDrawn::~CCustomDrawn()
{
	InvalidateBitmap();
}

long CCustomDrawn::OnPaint()
{
	PAINTSTRUCT ps;
	BeginPaint(m_hWnd, &ps);

	HDC hWDC = ps.hdc;

	if(m_MemDc == NULL)
	{
		RecreateBitmap(hWDC);
	}

	Paint(m_MemDc);

	BitBlt(hWDC, 
		ps.rcPaint.left,
		ps.rcPaint.top,
		ps.rcPaint.right,
		ps.rcPaint.bottom,
		m_MemDc,
		ps.rcPaint.left,
		ps.rcPaint.top,
		SRCCOPY);

	EndPaint(m_hWnd, &ps);

	return FALSE;
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
	if(m_MemDc != NULL) return;

	RECT rc = GetClientRect();
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
