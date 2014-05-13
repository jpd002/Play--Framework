#include <assert.h>
#include "win32/TreeView.h"

using namespace Framework;
using namespace Framework::Win32;

CTreeView::CTreeView(HWND hParent, const RECT& rect, unsigned long nStyle, unsigned long nExStyle)
{
	InitCommonControls();
	Create(nExStyle, WC_TREEVIEW, _T(""), WS_CHILD | WS_VISIBLE | nStyle, rect, hParent, NULL);
}

HTREEITEM CTreeView::InsertItem(TVINSERTSTRUCT* pI)
{
	return TreeView_InsertItem(m_hWnd, pI);
}

HTREEITEM CTreeView::InsertItem(HTREEITEM nParent, const TCHAR* sText)
{
	TVINSERTSTRUCT s;
	s.hParent		= nParent;
	s.hInsertAfter	= TVI_LAST;
	s.item.pszText	= const_cast<TCHAR*>(sText);
	s.item.mask		= TVIF_TEXT;
	return InsertItem(&s);
}

HTREEITEM CTreeView::GetSelection()
{
	return (HTREEITEM)TreeView_GetSelection(m_hWnd);
}

bool CTreeView::GetItem(HTREEITEM hItem, TVITEM* pI)
{
	pI->hItem = hItem;
	return ((TreeView_GetItem(m_hWnd, pI) == TRUE) ? true : false);
}

HTREEITEM CTreeView::GetItemParent(HTREEITEM hItem)
{
	return TreeView_GetParent(m_hWnd, hItem);
}

void CTreeView::GetItemText(HTREEITEM hItem, TCHAR* sText, size_t nCount)
{
	TVITEM Item;

	memset(&Item, 0, sizeof(TVITEM));
	Item.mask		= TVIF_TEXT;
	Item.pszText	= sText;
	Item.cchTextMax = static_cast<int>(nCount);

	GetItem(hItem, &Item);
}

std::tstring CTreeView::GetItemText(HTREEITEM hItem)
{
	TCHAR sString[260];
	GetItemText(hItem, sString, _countof(sString));
	return std::tstring(sString);
}

void* CTreeView::GetItemParam(HTREEITEM hItem)
{
	TVITEM Item;

	memset(&Item, 0, sizeof(TVITEM));
	Item.mask		= TVIF_PARAM;

	GetItem(hItem, &Item);

	return reinterpret_cast<void*>(Item.lParam);
}

void CTreeView::GetItemLabelRect(HTREEITEM hItem, RECT* pRect)
{
	assert(pRect != NULL);
	TreeView_GetItemRect(m_hWnd, hItem, pRect, TRUE);
}

void CTreeView::SetItem(HTREEITEM hItem, TVITEM* pI)
{
	pI->hItem = hItem;
	TreeView_SetItem(m_hWnd, pI);
}

void CTreeView::SetItemText(HTREEITEM hItem, const TCHAR* sText)
{
	TVITEM Item;

	memset(&Item, 0, sizeof(TVITEM));
	Item.mask		= TVIF_TEXT;
	Item.pszText	= const_cast<TCHAR*>(sText);

	SetItem(hItem, &Item);
}

void CTreeView::SetItemParam(HTREEITEM hItem, void* pParam)
{
	TVITEM Item;

	memset(&Item, 0, sizeof(TVITEM));
	Item.mask		= TVIF_PARAM;
	Item.lParam		= reinterpret_cast<LPARAM>(pParam);

	SetItem(hItem, &Item);
}

void CTreeView::SetImageList(HIMAGELIST hImageList)
{
	TreeView_SetImageList(m_hWnd, hImageList, 0);
}

void CTreeView::SetItemParam(HTREEITEM hItem, unsigned int nParam)
{
	TVITEM Item;

	memset(&Item, 0, sizeof(TVITEM));
	Item.mask		= TVIF_PARAM;
	Item.lParam		= nParam;

	SetItem(hItem, &Item);
}

HTREEITEM CTreeView::GetRoot()
{
	return TreeView_GetRoot(m_hWnd);
}

HTREEITEM CTreeView::GetChild(HTREEITEM hItem)
{
	return TreeView_GetChild(m_hWnd, hItem);
}

HTREEITEM CTreeView::GetNextSibling(HTREEITEM hItem)
{
	return TreeView_GetNextSibling(m_hWnd, hItem);
}

bool CTreeView::SetSelection(HTREEITEM hItem)
{
	return ((TreeView_SelectItem(m_hWnd, hItem) == TRUE) ? true : false);
}

bool CTreeView::Expand(HTREEITEM hItem, unsigned int nFlags)
{
	return ((TreeView_Expand(m_hWnd, hItem, nFlags) == TRUE) ? true : false);
}

void CTreeView::DeleteChildren(HTREEITEM hItem)
{
	HTREEITEM hChild(TreeView_GetChild(m_hWnd, hItem));

	while(hChild != NULL)
	{
		HTREEITEM hNext(TreeView_GetNextSibling(m_hWnd, hChild));
		TreeView_DeleteItem(m_hWnd, hChild);
		hChild = hNext;
	}
}

bool CTreeView::DeleteAllItems()
{
	return ((TreeView_DeleteAllItems(m_hWnd) == TRUE) ? true : false);
}

void CTreeView::SortChildren(HTREEITEM item, bool recurse)
{
	TreeView_SortChildren(m_hWnd, item, recurse);
}
