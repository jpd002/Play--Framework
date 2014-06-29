#include <cassert>
#include <algorithm>
#include "win32/VerticalSplitter.h"

using namespace Framework::Win32;

CVerticalSplitter::CVerticalSplitter(HWND hParent, const RECT& Rect) :
CSplitter(hParent, Rect, LoadCursor(NULL, IDC_SIZENS), ((Rect.bottom - Rect.top) - EDGESIZE) / 2)
{
	
}

CRect CVerticalSplitter::GetEdgeRect()
{
	auto clientRect = GetClientRect();
	Framework::Win32::CRect result(0, 0, clientRect.Right(), 0);
	if(m_masterChild == 0)
	{
		result.SetTop(m_edgePosition);
		result.SetBottom(m_edgePosition + EDGESIZE);
	}
	else
	{
		result.SetTop(clientRect.Bottom() - m_edgePosition);
		result.SetBottom(clientRect.Bottom() - m_edgePosition + EDGESIZE);
	}
	assert(result.Height() == EDGESIZE);
	return result;
}

CRect CVerticalSplitter::GetPaneRect(unsigned int nIndex)
{
	auto clientRect = GetClientRect();
	Framework::Win32::CRect result(0, 0, clientRect.Right(), 0);
	if(m_masterChild == 0)
	{
		if(nIndex == 0)
		{
			result.SetTop(0);
			result.SetBottom(m_edgePosition);
		}
		else if(nIndex == 1)
		{
			result.SetTop(m_edgePosition + EDGESIZE);
			result.SetBottom(clientRect.Bottom());
		}
	}
	else
	{
		if(nIndex == 0)
		{
			result.SetTop(0);
			result.SetBottom(clientRect.Bottom() - m_edgePosition);
		}
		else if(nIndex == 1)
		{
			result.SetTop(clientRect.Bottom() - m_edgePosition + EDGESIZE);
			result.SetBottom(clientRect.Bottom());
		}
	}
	return result;
}

void CVerticalSplitter::UpdateEdgePosition(int nX, int nY)
{
	auto clientRect = GetClientRect();
	nY = std::max<int>(nY, EDGESIZE);
	nY = std::min<int>(nY, clientRect.Bottom() - EDGESIZE);
	if(m_masterChild == 0)
	{
		m_edgePosition = nY;
	}
	else
	{
		m_edgePosition = clientRect.Bottom() - nY;
	}
}
