#include "win32/VerticalSplitter.h"

using namespace Framework::Win32;

CVerticalSplitter::CVerticalSplitter(HWND hParent, const RECT& Rect) :
CSplitter(hParent, Rect, LoadCursor(NULL, IDC_SIZENS), ((Rect.bottom - Rect.top) - EDGESIZE) / 2)
{
	
}

RECT CVerticalSplitter::GetEdgeRect()
{
	RECT clientRect = GetClientRect();
	RECT result = {};
	SetRect(&result, 0, m_nEdgePosition, clientRect.right, m_nEdgePosition + EDGESIZE);
	return result;
}

RECT CVerticalSplitter::GetPaneRect(unsigned int nIndex)
{
	RECT clientRect = GetClientRect();
	RECT result = {};
	if(nIndex == 0)
	{
		SetRect(&result, 0, 0, clientRect.right, m_nEdgePosition);
	}
	else if(nIndex == 1)
	{
		SetRect(&result, 0, m_nEdgePosition + EDGESIZE, clientRect.right, clientRect.bottom);
	}
	return result;
}

void CVerticalSplitter::UpdateEdgePosition(int nX, int nY)
{
	RECT clientRect = GetClientRect();
	if((nY > EDGESIZE) && (nY < clientRect.bottom - EDGESIZE))
	{
		m_nEdgePosition = nY;
	}
}
