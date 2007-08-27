#include "win32/Rect.h"

using namespace Framework::Win32;

CRect::CRect(int nLeft, int nTop, int nRight, int nBottom)
{
	SetRect(&m_Rect, nLeft, nTop, nRight, nBottom);
}

CRect::CRect(RECT Source)
{
    CopyRect(&m_Rect, &Source);
}

CRect::~CRect()
{

}

CRect::operator RECT*()
{
	return &m_Rect;
}

CRect::operator RECT&()
{
    return m_Rect;
}

CRect& CRect::Adjust(uint32 nStyle, bool nMenu)
{
	AdjustWindowRect(&m_Rect, nStyle, (nMenu) ? TRUE : FALSE);
	return (*this);
}

CRect& CRect::Inflate(int nDx, int nDy)
{
    InflateRect(&m_Rect, nDx, nDy);
    return (*this);
}

bool CRect::PtIn(int nX, int nY)
{
    POINT Pt;
    Pt.x = nX;
    Pt.y = nY;
    return PtInRect(&m_Rect, Pt) != 0;
}
