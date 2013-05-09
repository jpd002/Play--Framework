#include "win32/HorizontalSplitter.h"

using namespace Framework::Win32;

CHorizontalSplitter::CHorizontalSplitter(HWND hParent, const RECT& Rect) :
CSplitter(hParent, Rect, LoadCursor(NULL, IDC_SIZEWE), ((Rect.right - Rect.left) - EDGESIZE) / 2)
{
	
}

RECT CHorizontalSplitter::GetEdgeRect()
{
	RECT clientRect = GetClientRect();
	RECT result = {};
	SetRect(&result, m_nEdgePosition, 0, m_nEdgePosition + EDGESIZE, clientRect.bottom);
	return result;
}

RECT CHorizontalSplitter::GetPaneRect(unsigned int nIndex)
{
	RECT clientRect = GetClientRect();
	RECT result = {};

	if(nIndex == 0)
	{
		SetRect(&result, 0, 0, m_nEdgePosition, clientRect.bottom);
	}
	else if(nIndex == 1)
	{
		SetRect(&result, m_nEdgePosition + EDGESIZE, 0, clientRect.right, clientRect.bottom);
	}

	return result;
}

void CHorizontalSplitter::UpdateEdgePosition(int nX, int nY)
{
	RECT clientRect = GetClientRect();

	if((nX > EDGESIZE) && (nX < clientRect.right - EDGESIZE))
	{
		m_nEdgePosition = nX;
	}
}
