#include "win32/Tab.h"
#include "win32/DefaultFonts.h"

using namespace Framework::Win32;

CTab::CTab(HWND hParent, RECT* pR, unsigned long nStyle, unsigned long nExStyle)
{
	InitCommonControls();
	Create(nExStyle, WC_TABCONTROL, _T(""), WS_CHILD | WS_VISIBLE | nStyle, pR, hParent, NULL);
	SetFont(CDefaultFonts::GetMessageFont());
}

CTab::~CTab()
{

}

int CTab::InsertTab(const TCHAR* sText)
{
    TC_ITEM Item;
    memset(&Item, 0, sizeof(TC_ITEM));
    Item.mask       = TCIF_TEXT;
    Item.pszText    = const_cast<TCHAR*>(sText);

    return TabCtrl_InsertItem(m_hWnd, GetItemCount(), &Item);
}

int CTab::GetSelection()
{
  return TabCtrl_GetCurSel(m_hWnd);
}

unsigned int CTab::GetItemCount()
{
    return TabCtrl_GetItemCount(m_hWnd);
}

RECT CTab::GetDisplayAreaRect()
{
    RECT Rect;
    Rect = GetClientRect();
    TabCtrl_AdjustRect(m_hWnd, FALSE, &Rect);
    return Rect;
}
