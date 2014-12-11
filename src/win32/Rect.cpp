#include "win32/Rect.h"

using namespace Framework::Win32;

CRect::CRect(int nLeft, int nTop, int nRight, int nBottom)
{
	SetRect(&m_rect, nLeft, nTop, nRight, nBottom);
}

CRect::CRect(const RECT& Source)
{
	CopyRect(&m_rect, &Source);
}

CRect::operator RECT*()
{
	return &m_rect;
}

CRect::operator RECT&()
{
	return m_rect;
}

int CRect::Left() const
{
	return m_rect.left;
}

int CRect::Top() const
{
	return m_rect.top;
}

int CRect::Right() const
{
	return m_rect.right;
}

int CRect::Bottom() const
{
	return m_rect.bottom;
}

void CRect::SetLeft(int left)
{
	m_rect.left = left;
}

void CRect::SetTop(int top)
{
	m_rect.top = top;
}

void CRect::SetRight(int right)
{
	m_rect.right = right;
}

void CRect::SetBottom(int bottom)
{
	m_rect.bottom = bottom;
}

int CRect::Width() const
{
	return m_rect.right - m_rect.left;
}

int CRect::Height() const
{
	return m_rect.bottom - m_rect.top;
}

CRect& CRect::Adjust(uint32 nStyle, bool nMenu)
{
	AdjustWindowRect(&m_rect, nStyle, (nMenu) ? TRUE : FALSE);
	return (*this);
}

CRect& CRect::Inflate(int nDx, int nDy)
{
	InflateRect(&m_rect, nDx, nDy);
	return (*this);
}

CRect& CRect::CenterInside(const CRect& parentRect)
{
	int width = Width();
	int height = Height();
	m_rect.left = parentRect.Left() + ((parentRect.Width() - width) / 2);
	m_rect.top = parentRect.Top() + ((parentRect.Height() - height) / 2);
	m_rect.right = m_rect.left + width;
	m_rect.bottom = m_rect.top + height;
	return (*this);
}

CRect& CRect::ScreenToClient(HWND window)
{
	::ScreenToClient(window, reinterpret_cast<LPPOINT>(&m_rect) + 0);
	::ScreenToClient(window, reinterpret_cast<LPPOINT>(&m_rect) + 1);
	return (*this);
}

CRect& CRect::ClientToScreen(HWND window)
{
	::ClientToScreen(window, reinterpret_cast<LPPOINT>(&m_rect) + 0);
	::ClientToScreen(window, reinterpret_cast<LPPOINT>(&m_rect) + 1);
	return (*this);
}

bool CRect::PtIn(int nX, int nY) const
{
	POINT pt;
	pt.x = nX;
	pt.y = nY;
	return PtInRect(&m_rect, pt) != 0;
}

CRect Framework::Win32::MakeRectPositionSize(int left, int top, int width, int height)
{
	return CRect(left, top, left + width, top + height);
}
