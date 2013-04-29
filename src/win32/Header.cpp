#include <assert.h>
#include "win32/Header.h"

using namespace Framework;
using namespace Framework::Win32;

CHeader::CHeader(HWND hWnd)
{
	m_hWnd = hWnd;
}

CHeader::CHeader(HWND hParent, const RECT& rect, unsigned long nStyle, unsigned long nExStyle)
{
	InitCommonControls();
	Create(nExStyle, WC_HEADER, _T(""), WS_CHILD | WS_VISIBLE | nStyle, rect, hParent, NULL);
}

void CHeader::GetItem(unsigned int index, HDITEM* item)
{
	Header_GetItem(m_hWnd, index, item);
}

void CHeader::SetItem(unsigned int index, HDITEM* item)
{
	Header_SetItem(m_hWnd, index, item);
}

int CHeader::InsertItem(const TCHAR* sText)
{
	HDITEM Item;

	memset(&Item, 0, sizeof(HDITEM));
	Item.mask		= HDI_TEXT;
	Item.pszText	= const_cast<TCHAR*>(sText);

	return InsertItem(GetItemCount(), &Item);
}

int CHeader::InsertItem(const TCHAR* sText, unsigned int nSize)
{
	HDITEM Item;
	
	memset(&Item, 0, sizeof(HDITEM));
	Item.mask		= HDI_TEXT | HDI_WIDTH;
	Item.pszText	= const_cast<TCHAR*>(sText);
	Item.cxy		= nSize;

	return InsertItem(GetItemCount(), &Item);
}

int CHeader::InsertItem(unsigned int nIndex, HDITEM* pItem)
{
	return Header_InsertItem(m_hWnd, nIndex, pItem);
}

void CHeader::GetItemRect(unsigned int nIndex, RECT* pRect)
{
	assert(pRect != NULL);
	Header_GetItemRect(m_hWnd, nIndex, pRect);
}

int CHeader::GetItemCount()
{
	return Header_GetItemCount(m_hWnd);
}

void CHeader::SetItemWidth(unsigned int nItem, unsigned int nWidth)
{
	HDITEM Item;

	memset(&Item, 0, sizeof(HDITEM));
	Item.mask	= HDI_WIDTH;
	Item.cxy	= nWidth;

	Header_SetItem(m_hWnd, nItem, &Item);
}

void CHeader::SetItemWidth(unsigned int nItem, double nWidth)
{
	RECT Rect(GetClientRect());
	SetItemWidth(nItem, static_cast<unsigned int>(static_cast<double>(Rect.right) * nWidth));
}
