#include "win32/Tab.h"
#include "win32/DefaultFonts.h"

using namespace Framework::Win32;

CTab::CTab(HWND hWnd)
{
	m_hWnd = hWnd;
}

CTab::CTab(HWND hParent, const RECT& rect, unsigned long nStyle, unsigned long nExStyle)
{
	InitCommonControls();
	Create(nExStyle, WC_TABCONTROL, _T(""), WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | nStyle, rect, hParent, NULL);
	SetFont(CDefaultFonts::GetMessageFont());
}

CTab::~CTab()
{

}

CTab& CTab::operator =(CTab&& rhs)
{
	CWindow::Reset();
	CWindow::MoveFrom(std::move(rhs));
	return (*this);
}

int CTab::InsertTab(const TCHAR* text)
{
	TC_ITEM item = {};
	item.mask		= TCIF_TEXT;
	item.pszText	= const_cast<TCHAR*>(text);

	return TabCtrl_InsertItem(m_hWnd, GetItemCount(), &item);
}

void CTab::DeleteTab(int tab)
{
	TabCtrl_DeleteItem(m_hWnd, tab);
}

std::tstring CTab::GetTabText(int tab)
{
	TCHAR text[_MAX_PATH];

	TC_ITEM item = {};
	item.mask		= TCIF_TEXT;
	item.pszText	= text;
	item.cchTextMax	= countof(text);

	TabCtrl_GetItem(m_hWnd, tab, &item);

	return std::tstring(text);
}

void CTab::SetTabText(int tab, const TCHAR* text)
{
	TC_ITEM item = {};
	item.mask		= TCIF_TEXT;
	item.pszText	= const_cast<TCHAR*>(text);
	TabCtrl_SetItem(m_hWnd, tab, &item);
}

LPARAM CTab::GetTabData(int tab)
{
	TC_ITEM item = {};
	item.mask		= TCIF_PARAM;
	TabCtrl_GetItem(m_hWnd, tab, &item);
	return item.lParam;
}

void CTab::SetTabData(int tab, LPARAM param)
{
	TC_ITEM item = {};
	item.mask		= TCIF_PARAM;
	item.lParam		= param;
	TabCtrl_SetItem(m_hWnd, tab, &item);
}

int CTab::GetSelection()
{
	return TabCtrl_GetCurSel(m_hWnd);
}

void CTab::SetSelection(int nSelection)
{
	TabCtrl_SetCurSel(m_hWnd, nSelection);
}

unsigned int CTab::GetItemCount()
{
	return TabCtrl_GetItemCount(m_hWnd);
}

int CTab::HitTest(int x, int y)
{
	TCHITTESTINFO hitTestInfo = {};
	hitTestInfo.pt.x = x;
	hitTestInfo.pt.y = y;
	return TabCtrl_HitTest(m_hWnd, &hitTestInfo);
}

Framework::Win32::CRect CTab::GetDisplayAreaRect()
{
	RECT rect = GetClientRect();
	TabCtrl_AdjustRect(m_hWnd, FALSE, &rect);
	return rect;
}
