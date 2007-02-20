#include <assert.h>
#include "win32/DeviceContext.h"
#include "win32/GdiObj.h"

using namespace Framework;
using namespace Framework::Win32;

CDeviceContext::CDeviceContext(HDC nDC)
{
	m_nDC = nDC;
}

CDeviceContext::~CDeviceContext()
{

}

CDeviceContext::operator HDC()
{
	return m_nDC;
}

unsigned int CDeviceContext::GetFontHeight(HFONT nFont)
{
	SIZE s;
	HGDIOBJ nPrevFont;

	nPrevFont = SelectObject(nFont);
	GetTextExtentPoint32(m_nDC, _T("0"), 1, &s);
	SelectObject(nPrevFont);

	return s.cy;
}

void CDeviceContext::FillRect(RECT* pRect, COLORREF nColor)
{
	assert(pRect != NULL);
	CBrush Brush(CreateSolidBrush(nColor));
	::FillRect(m_nDC, pRect, Brush);
}

void CDeviceContext::DrawLine(int nX1, int nY1, int nX2, int nY2)
{
	MoveToEx(m_nDC, nX1, nY1, NULL);
	LineTo(m_nDC, nX2, nY2);
}

void CDeviceContext::DrawLine(int nX1, int nY1, int nX2, int nY2, COLORREF nColor)
{
	CPen Pen(CreatePen(PS_SOLID, 0, nColor));
	SelectObject(Pen);
	DrawLine(nX1, nY1, nX2, nY2);
}

void CDeviceContext::TextOut(int nX, int nY, const TCHAR* sText)
{
	::TextOut(m_nDC, nX, nY, sText, static_cast<int>(_tcslen(sText)));
}

HGDIOBJ CDeviceContext::SelectObject(HGDIOBJ hObject)
{
	return ::SelectObject(m_nDC, hObject);
}
