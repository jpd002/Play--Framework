#include "win32/ListView.h"

using namespace Framework::Win32;

CListView::CListView(HWND hWnd)
{
	m_hWnd = hWnd;
}

CListView::CListView(HWND hParent, const RECT& rect, unsigned long nStyle, unsigned long nExStyle)
{
	InitCommonControls();
	Create(nExStyle, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | nStyle, rect, hParent, NULL);
}

CListView::~CListView()
{

}

CListView& CListView::operator =(CListView&& rhs)
{
	CWindow::Reset();
	CWindow::MoveFrom(std::move(rhs));
	return (*this);
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

void CListView::DeleteItem(unsigned int itemIdx)
{
	ListView_DeleteItem(m_hWnd, itemIdx);
}

bool CListView::DeleteColumn(unsigned int itemIdx)
{
	return ListView_DeleteColumn(m_hWnd, itemIdx) != FALSE;
}

void CListView::DeleteAllItems()
{
	ListView_DeleteAllItems(m_hWnd);
}

int CListView::InsertItem(const LVITEM& item)
{
	return ListView_InsertItem(m_hWnd, &item);
}

void CListView::SetColumnWidth(unsigned int nCol, unsigned int nCX)
{
	ListView_SetColumnWidth(m_hWnd, nCol, nCX);
}

void CListView::InsertColumn(unsigned int index, const LVCOLUMN& column)
{
	ListView_InsertColumn(m_hWnd, index, &column);
}

std::tstring CListView::GetItemText(unsigned int itemIndex, unsigned int subItemIndex)
{
	int size = 0x100;
	std::tstring result;
	while(1)
	{
		result.resize(size);
		LV_ITEM item = {};
		item.cchTextMax	= result.size();
		item.pszText	= const_cast<TCHAR*>(result.data());
		item.iSubItem	= subItemIndex;
		int n = SendMessage(m_hWnd, LVM_GETITEMTEXT, itemIndex, reinterpret_cast<LPARAM>(&item));
		if((n + 1) != size)
		{
			result.resize(n);
			return result;
		}
		size *= 2;
	}
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

void CListView::SetItemState(unsigned int itemIdx, unsigned int state, unsigned int mask)
{
	ListView_SetItemState(m_hWnd, itemIdx, state, mask);
}

int CListView::GetSelection()
{
	return ListView_GetSelectionMark(m_hWnd);
}

void CListView::SetSelection(int nIndex)
{
	ListView_SetSelectionMark(m_hWnd, nIndex);
}

void CListView::EnableGroupView(bool enabled)
{
	ListView_EnableGroupView(m_hWnd, enabled);
}

int CListView::InsertGroup(const TCHAR* name, unsigned int id, unsigned int index)
{
	LVGROUP group;
	memset(&group, 0, sizeof(group));
	group.cbSize		= sizeof(LVGROUP);
	group.mask			= LVGF_HEADER | LVGF_GROUPID;
	group.pszHeader		= const_cast<TCHAR*>(name);
	group.iGroupId		= id;
	return ListView_InsertGroup(m_hWnd, index, &group);
}

void CListView::RemoveAllGroups()
{
	ListView_RemoveAllGroups(m_hWnd);
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

HWND CListView::GetHeader()
{
	return ListView_GetHeader(m_hWnd);
}
