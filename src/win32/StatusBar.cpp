#include "win32/StatusBar.h"
#include <commctrl.h>

using namespace Framework;
using namespace Framework::Win32;

CStatusBar::CStatusBar(HWND hParent)
{
	InitCommonControls();

	m_hWnd = CreateStatusWindow(WS_CHILD | WS_VISIBLE, _T(""), hParent, 0);
}

CStatusBar::~CStatusBar()
{

}

CStatusBar& CStatusBar::operator =(CStatusBar&& rhs)
{
	CWindow::Reset();
	CWindow::MoveFrom(std::move(rhs));
	return (*this);
}

void CStatusBar::SetText(unsigned int nPanelIdx, const TCHAR* sText)
{
	SendMessage(m_hWnd, SB_SETTEXT, nPanelIdx, reinterpret_cast<LPARAM>(sText));
}

void CStatusBar::SetParts(unsigned int nCount, const double* nSizesRelative)
{
	unsigned int* nSizes = reinterpret_cast<unsigned int*>(_alloca(sizeof(unsigned int) * nCount));
	RECT clientRect = GetClientRect();

	for(unsigned int i = 0; i < nCount; i++)
	{
		nSizes[i] = static_cast<unsigned int>(nSizesRelative[i] * static_cast<double>(clientRect.right));
		if(i != 0) nSizes[i] += nSizes[i - 1];
	}

	SendMessage(m_hWnd, SB_SETPARTS, nCount, reinterpret_cast<LPARAM>(nSizes));
}

void CStatusBar::RefreshGeometry()
{
	SendMessage(m_hWnd, WM_SIZE, 0, 0);
}

unsigned int CStatusBar::GetHeight()
{
	RECT rect = GetRect();
	return rect.bottom - rect.top;
}

RECT CStatusBar::GetRect()
{
	RECT rect = GetWindowRect();
	ScreenToClient(GetParent(), reinterpret_cast<POINT*>(&rect) + 0);
	ScreenToClient(GetParent(), reinterpret_cast<POINT*>(&rect) + 1);
	return rect;
}
