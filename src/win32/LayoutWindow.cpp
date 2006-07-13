#include "win32/LayoutWindow.h"
#include "PtrMacro.h"

using namespace Framework;

CLayoutWindow::CLayoutWindow(unsigned int nPrefWidth, unsigned int nPrefHeight, unsigned int nHorzStretch, unsigned int nVertStretch, CWindow* pWindow, bool nUseNoCopy) :
CLayoutObject(nHorzStretch, nVertStretch)
{
	m_nPrefWidth = nPrefWidth;
	m_nPrefHeight = nPrefHeight;
	m_pWindow = pWindow;
	m_nUseNoCopy = nUseNoCopy;
}

CLayoutWindow::~CLayoutWindow()
{
	DELETEPTR(m_pWindow);
}

CLayoutWindow* CLayoutWindow::CreateButtonBehavior(unsigned int nWidth, unsigned int nHeight, CWindow* pWindow)
{
	return new CLayoutWindow(nWidth, nHeight, 0, 0, pWindow);
}

CLayoutWindow* CLayoutWindow::CreateTextBoxBehavior(unsigned int nWidth, unsigned int nHeight, CWindow* pWindow)
{
	return new CLayoutWindow(nWidth, nHeight, 1, 0, pWindow);
}

unsigned int CLayoutWindow::GetPreferredWidth()
{
	return m_nPrefWidth;
}

unsigned int CLayoutWindow::GetPreferredHeight()
{
	return m_nPrefHeight;
}

void CLayoutWindow::RefreshGeometry()
{
	unsigned int nWidth, nHeight;

	nWidth = GetRight() - GetLeft();
	nHeight = GetBottom() - GetTop();

	if(m_nUseNoCopy)
	{
		SetWindowPos(m_pWindow->m_hWnd, NULL, GetLeft(), GetTop(), nWidth, nHeight, SWP_NOZORDER | SWP_NOCOPYBITS);
	}
	else
	{
		SetWindowPos(m_pWindow->m_hWnd, NULL, GetLeft(), GetTop(), nWidth, nHeight, SWP_NOZORDER);
	}
}
