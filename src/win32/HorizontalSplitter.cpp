#include <cassert>
#include <algorithm>
#include "win32/HorizontalSplitter.h"

using namespace Framework::Win32;

CHorizontalSplitter::CHorizontalSplitter(HWND hParent, const RECT& Rect) :
CSplitter(hParent, Rect, LoadCursor(NULL, IDC_SIZEWE), ((Rect.right - Rect.left) - EDGESIZE) / 2)
{
	
}

CRect CHorizontalSplitter::GetEdgeRect()
{
	auto clientRect = GetClientRect();
	Framework::Win32::CRect result(0, 0, 0, clientRect.Bottom());
	if(m_masterChild == 0)
	{
		result.SetLeft(m_edgePosition);
		result.SetRight(m_edgePosition + EDGESIZE);
	}
	else
	{
		result.SetLeft(clientRect.Right() - m_edgePosition);
		result.SetRight(clientRect.Right() - m_edgePosition + EDGESIZE);
	}
	assert(result.Width() == EDGESIZE);
	return result;
}

CRect CHorizontalSplitter::GetPaneRect(unsigned int nIndex)
{
	auto clientRect = GetClientRect();
	Framework::Win32::CRect result(0, 0, 0, clientRect.Bottom());
	if(m_masterChild == 0)
	{
		if(nIndex == 0)
		{
			result.SetLeft(0);
			result.SetRight(m_edgePosition);
		}
		else if(nIndex == 1)
		{
			result.SetLeft(m_edgePosition + EDGESIZE);
			result.SetRight(clientRect.Right());
		}
	}
	else
	{
		if(nIndex == 0)
		{
			result.SetLeft(0);
			result.SetRight(clientRect.Right() - m_edgePosition);
		}
		else if(nIndex == 1)
		{
			result.SetLeft(clientRect.Right() - m_edgePosition + EDGESIZE);
			result.SetRight(clientRect.Right());
		}
	}
	return result;
}

void CHorizontalSplitter::UpdateEdgePosition(int nX, int nY)
{
	auto clientRect = GetClientRect();
	nX = std::max<int>(nX, EDGESIZE);
	nX = std::min<int>(nX, clientRect.Right() - EDGESIZE);
	if(m_masterChild == 0)
	{
		m_edgePosition = nX;
	}
	else
	{
		m_edgePosition = clientRect.Right() - nX;
	}
}
