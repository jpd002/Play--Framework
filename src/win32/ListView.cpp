/*

	Framework - ListView.cpp
	File Version 1.0.000

*/

#include "win32/ListView.h"

using namespace Framework::Win32;

CListView::CListView(HWND hParent, RECT* pR, unsigned long nStyle, unsigned long nExStyle)
{
	InitCommonControls();
	Create(nExStyle, WC_LISTVIEW, _X(""), WS_CHILD | WS_VISIBLE | nStyle, pR, hParent, NULL);
}

CListView::~CListView()
{

}

int CListView::GetItemCount()
{
	return ListView_GetItemCount(m_hWnd);
}

int CListView::FindItemData(unsigned long nData)
{
	LVFINDINFO info;
	memset(&info, 0, sizeof(LVFINDINFO));

	info.flags	= LVFI_PARAM;
	info.lParam = nData;

	return ListView_FindItem(m_hWnd, -1, &info);
}

void CListView::DeleteAllItems()
{
	ListView_DeleteAllItems(m_hWnd);
}

int CListView::InsertItem(LVITEM* pI)
{
	return ListView_InsertItem(m_hWnd, pI);
}

void CListView::SetColumnWidth(unsigned int nCol, unsigned int nCX)
{
	ListView_SetColumnWidth(m_hWnd, nCol, nCX);
}

void CListView::InsertColumn(unsigned int nCol, LVCOLUMN* pC)
{
	ListView_InsertColumn(m_hWnd, nCol, pC);
}

void CListView::GetItemText(unsigned int nItem, unsigned int nSubItem, TCHAR* sText, unsigned int nCount)
{
	ListView_GetItemText(m_hWnd, nItem, nSubItem, sText, nCount);
}

unsigned long CListView::GetItemData(unsigned int nItem)
{
	LVITEM it;
	memset(&it, 0, sizeof(LVITEM));
	it.iItem	= nItem;
	it.mask		= LVIF_PARAM;

	ListView_GetItem(m_hWnd, &it);

	return (unsigned long)it.lParam;
}

void CListView::SetItemText(unsigned int nItem, unsigned int nSubItem, const TCHAR* sText)
{
	ListView_SetItemText(m_hWnd, nItem, nSubItem, const_cast<TCHAR*>(sText));
}

int CListView::GetSelection()
{
	return ListView_GetSelectionMark(m_hWnd);
}

void CListView::SetSelection(int nIndex)
{
	ListView_SetSelectionMark(m_hWnd, nIndex);
}

void CListView::SetExtendedListViewStyle(unsigned long nStyle)
{
	ListView_SetExtendedListViewStyle(m_hWnd, nStyle);
}

unsigned long CListView::GetExtendedListViewStyle()
{
	return ListView_GetExtendedListViewStyle(m_hWnd);
}

void CListView::SetItemCount(int nCount)
{
	ListView_SetItemCount(m_hWnd, nCount);
}

void CListView::EnsureItemVisible(unsigned int nItem, bool nPartialOk)
{
	ListView_EnsureVisible(m_hWnd, nItem, nPartialOk);
}

void CListView::ProcessGetDisplayInfo(NMHDR* pHdr, GetDispInfoCallbackType Callback)
{
	if(pHdr->code != LVN_GETDISPINFO) return;
	if(pHdr->hwndFrom != m_hWnd) return;

	LV_DISPINFO* pDispInfo;

	pDispInfo = reinterpret_cast<LV_DISPINFO*>(pHdr);
	Callback(&pDispInfo->item);
}
