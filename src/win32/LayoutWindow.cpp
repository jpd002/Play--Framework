#include "win32/LayoutWindow.h"
#include "PtrMacro.h"

using namespace Framework;
using namespace Framework::Win32;

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

LayoutObjectPtr CLayoutWindow::CreateButtonBehavior(unsigned int nWidth, unsigned int nHeight, CWindow* pWindow)
{
	return LayoutObjectPtr(new CLayoutWindow(nWidth, nHeight, 0, 0, pWindow));
}

LayoutObjectPtr CLayoutWindow::CreateTextBoxBehavior(unsigned int nWidth, unsigned int nHeight, CWindow* pWindow)
{
	return LayoutObjectPtr(new CLayoutWindow(nWidth, nHeight, 1, 0, pWindow));
}

LayoutObjectPtr CLayoutWindow::CreateCustomBehavior(unsigned int prefWidth, unsigned int prefHeight, unsigned int horzStretch, unsigned int vertStretch, CWindow* window, bool useNoCopy)
{
    return LayoutObjectPtr(new CLayoutWindow(prefWidth, prefHeight, horzStretch, vertStretch, window, useNoCopy));
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
	unsigned int nWidth = GetRight() - GetLeft();
	unsigned int nHeight = GetBottom() - GetTop();

	if(m_nUseNoCopy)
	{
		SetWindowPos(m_pWindow->m_hWnd, NULL, GetLeft(), GetTop(), nWidth, nHeight, SWP_NOZORDER | SWP_NOCOPYBITS);
	}
	else
	{
		SetWindowPos(m_pWindow->m_hWnd, NULL, GetLeft(), GetTop(), nWidth, nHeight, SWP_NOZORDER);
	}
}
