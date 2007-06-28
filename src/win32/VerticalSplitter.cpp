#include "win32/VerticalSplitter.h"

using namespace Framework::Win32;

CVerticalSplitter::CVerticalSplitter(HWND hParent, const RECT& Rect) :
CSplitter(hParent, Rect, LoadCursor(NULL, IDC_SIZENS), ((Rect.bottom - Rect.top) - EDGESIZE) / 2)
{
	
}

void CVerticalSplitter::GetEdgeRect(RECT* pEdgeRect)
{
	RECT ClientRect;

	GetClientRect(&ClientRect);
	SetRect(pEdgeRect, 0, m_nEdgePosition, ClientRect.right, m_nEdgePosition + EDGESIZE);
}

void CVerticalSplitter::GetPaneRect(RECT* pPaneRect, unsigned int nIndex)
{
	RECT ClientRect;

	GetClientRect(&ClientRect);

	if(nIndex == 0)
	{
		SetRect(pPaneRect, 0, 0, ClientRect.right, m_nEdgePosition);
	}
	else if(nIndex == 1)
	{
		SetRect(pPaneRect, 0, m_nEdgePosition + EDGESIZE, ClientRect.right, ClientRect.bottom);
	}
}

void CVerticalSplitter::UpdateEdgePosition(int nX, int nY)
{
	RECT ClientRect;

	GetClientRect(&ClientRect);

	if((nY > EDGESIZE) && (nY < ClientRect.bottom - EDGESIZE))
	{
		m_nEdgePosition = nY;
	}
}
