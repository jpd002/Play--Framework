#include "win32/HorizontalSplitter.h"

using namespace Framework::Win32;

CHorizontalSplitter::CHorizontalSplitter(HWND hParent, const RECT& Rect) :
CSplitter(hParent, Rect, LoadCursor(NULL, IDC_SIZEWE), ((Rect.right - Rect.left) - EDGESIZE) / 2)
{
	
}

void CHorizontalSplitter::GetEdgeRect(RECT* pEdgeRect)
{
	RECT ClientRect;

	GetClientRect(&ClientRect);
	SetRect(pEdgeRect, m_nEdgePosition, 0, m_nEdgePosition + EDGESIZE, ClientRect.bottom);
}

void CHorizontalSplitter::GetPaneRect(RECT* pPaneRect, unsigned int nIndex)
{
	RECT ClientRect;

	GetClientRect(&ClientRect);

	if(nIndex == 0)
	{
		SetRect(pPaneRect, 0, 0, m_nEdgePosition, ClientRect.bottom);
	}
	else if(nIndex == 1)
	{
		SetRect(pPaneRect, m_nEdgePosition + EDGESIZE, 0, ClientRect.right, ClientRect.bottom);
	}
}

void CHorizontalSplitter::UpdateEdgePosition(int nX, int nY)
{
	RECT ClientRect;

	GetClientRect(&ClientRect);

	if((nX > EDGESIZE) && (nX < ClientRect.right - EDGESIZE))
	{
		m_nEdgePosition = nX;
	}
}
