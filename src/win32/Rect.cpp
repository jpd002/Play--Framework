#include "win32/Rect.h"

using namespace Framework::Win32;

CRect::CRect(int nLeft, int nTop, int nRight, int nBottom)
{
	SetRect(&m_Rect, nLeft, nTop, nRight, nBottom);
}

CRect::~CRect()
{

}

CRect::operator RECT*()
{
	return &m_Rect;
}

CRect& CRect::Adjust(uint32 nStyle, bool nMenu)
{
	AdjustWindowRect(&m_Rect, nStyle, (nMenu) ? TRUE : FALSE);
	return (*this);
}
