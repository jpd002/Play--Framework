#include "win32/VerticalSplitter.h"

using namespace Framework::Win32;

CVerticalSplitter::CVerticalSplitter(HWND hParent, const RECT& Rect) :
CSplitter(hParent, Rect, LoadCursor(NULL, IDC_SIZENS), ((Rect.bottom - Rect.top) - EDGESIZE) / 2)
{
	
}

void CVerticalSplitter::GetEdgeRect(RECT* pEdgeRect)
{
	RECT clientRect = GetClientRect();
	SetRect(pEdgeRect, 0, m_nEdgePosition, clientRect.right, m_nEdgePosition + EDGESIZE);
}

void CVerticalSplitter::GetPaneRect(RECT* pPaneRect, unsigned int nIndex)
{
	RECT clientRect = GetClientRect();
	if(nIndex == 0)
	{
		SetRect(pPaneRect, 0, 0, clientRect.right, m_nEdgePosition);
	}
	else if(nIndex == 1)
	{
		SetRect(pPaneRect, 0, m_nEdgePosition + EDGESIZE, clientRect.right, clientRect.bottom);
	}
}

void CVerticalSplitter::UpdateEdgePosition(int nX, int nY)
{
	RECT clientRect = GetClientRect();
	if((nY > EDGESIZE) && (nY < clientRect.bottom - EDGESIZE))
	{
		m_nEdgePosition = nY;
	}
}
