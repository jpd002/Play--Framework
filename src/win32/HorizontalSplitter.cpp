#include "HorizontalSplitter.h"

using namespace Framework;

CHorizontalSplitter::CHorizontalSplitter(HWND hParent, RECT* pRect) :
CSplitter(hParent, pRect, LoadCursor(NULL, IDC_SIZEWE), ((pRect->right - pRect->left) - EDGESIZE) / 2)
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
