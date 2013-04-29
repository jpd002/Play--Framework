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

CRect::~CRect()
{

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

bool CRect::PtIn(int nX, int nY)
{
	POINT pt;
	pt.x = nX;
	pt.y = nY;
	return PtInRect(&m_rect, pt) != 0;
}
