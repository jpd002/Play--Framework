#include "win32/HorizontalSplitter.h"

using namespace Framework::Win32;

CHorizontalSplitter::CHorizontalSplitter(HWND hParent, const RECT& Rect) :
CSplitter(hParent, Rect, LoadCursor(NULL, IDC_SIZEWE), ((Rect.right - Rect.left) - EDGESIZE) / 2)
{
	
}

void CHorizontalSplitter::GetEdgeRect(RECT* pEdgeRect)
{
	RECT clientRect = GetClientRect();
	SetRect(pEdgeRect, m_nEdgePosition, 0, m_nEdgePosition + EDGESIZE, clientRect.bottom);
}

void CHorizontalSplitter::GetPaneRect(RECT* pPaneRect, unsigned int nIndex)
{
	RECT clientRect = GetClientRect();

	if(nIndex == 0)
	{
		SetRect(pPaneRect, 0, 0, m_nEdgePosition, clientRect.bottom);
	}
	else if(nIndex == 1)
	{
		SetRect(pPaneRect, m_nEdgePosition + EDGESIZE, 0, clientRect.right, clientRect.bottom);
	}
}

void CHorizontalSplitter::UpdateEdgePosition(int nX, int nY)
{
	RECT clientRect = GetClientRect();

	if((nX > EDGESIZE) && (nX < clientRect.right - EDGESIZE))
	{
		m_nEdgePosition = nX;
	}
}
