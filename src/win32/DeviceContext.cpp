#include <assert.h>
#include "win32/DeviceContext.h"
#include "win32/GdiObj.h"

using namespace Framework;
using namespace Framework::Win32;

CDeviceContext::CDeviceContext(HDC dc)
: m_dc(dc)
{

}

CDeviceContext::~CDeviceContext()
{

}

CDeviceContext::operator HDC()
{
	return m_dc;
}

void CDeviceContext::FillRect(RECT* pRect, COLORREF nColor)
{
	assert(pRect != NULL);
	CBrush Brush(CreateSolidBrush(nColor));
	::FillRect(m_dc, pRect, Brush);
}

void CDeviceContext::DrawLine(int nX1, int nY1, int nX2, int nY2)
{
	MoveToEx(m_dc, nX1, nY1, NULL);
	LineTo(m_dc, nX2, nY2);
}

void CDeviceContext::DrawLine(int nX1, int nY1, int nX2, int nY2, COLORREF nColor)
{
	CPen pen(CreatePen(PS_SOLID, 0, nColor));
	SelectObject(pen);
	DrawLine(nX1, nY1, nX2, nY2);
}

void CDeviceContext::TextOut(int x, int y, const TCHAR* text)
{
	::TextOut(m_dc, x, y, text, static_cast<int>(_tcslen(text)));
}

void CDeviceContext::TextOut(int x, int y, const TCHAR* text, COLORREF color)
{
	SetTextColor(m_dc, color);
	TextOut(x, y, text);
}

HGDIOBJ CDeviceContext::SelectObject(HGDIOBJ hObject)
{
	return ::SelectObject(m_dc, hObject);
}
