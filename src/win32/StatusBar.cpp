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

void CStatusBar::SetText(unsigned int nPanelIdx, const TCHAR* sText)
{
	SendMessage(m_hWnd, SB_SETTEXT, nPanelIdx, reinterpret_cast<LPARAM>(sText));
}

void CStatusBar::SetParts(unsigned int nCount, const double* nSizesRelative)
{
	unsigned int* nSizes;
	RECT ClientRect;

	nSizes = reinterpret_cast<unsigned int*>(_alloca(sizeof(unsigned int) * nCount));
	GetClientRect(&ClientRect);

	for(unsigned int i = 0; i < nCount; i++)
	{
		nSizes[i] = static_cast<unsigned int>(nSizesRelative[i] * static_cast<double>(ClientRect.right));
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
	RECT Rect;
	GetRect(&Rect);
	return Rect.bottom - Rect.top;
}

void CStatusBar::GetRect(RECT* pR)
{
	GetWindowRect(pR);
	ScreenToClient(GetParent(), reinterpret_cast<POINT*>(pR) + 0);
	ScreenToClient(GetParent(), reinterpret_cast<POINT*>(pR) + 1);
}
