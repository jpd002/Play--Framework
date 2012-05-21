#include "win32/ListBox.h"
#include "win32/DefaultFonts.h"

using namespace Framework;
using namespace Framework::Win32;

CListBox::CListBox(HWND hWnd)
{
	m_hWnd = hWnd;
}

CListBox::CListBox(HWND hParent, RECT* pR, unsigned long nStyle, unsigned long nStyleEx)
{
	Create(nStyleEx, _T("LISTBOX"), _T(""), WS_VISIBLE | WS_CHILD | nStyle, pR, hParent, NULL);
	SetFont(CDefaultFonts::GetMessageFont());
}

unsigned int CListBox::AddString(const TCHAR* sValue)
{
	return static_cast<unsigned int>(SendMessage(m_hWnd, LB_ADDSTRING, NULL, (LPARAM)sValue));
}

void CListBox::ResetContent()
{
	SendMessage(m_hWnd, LB_RESETCONTENT, NULL, NULL);
}

int CListBox::GetCurrentSelection()
{
	return static_cast<int>(SendMessage(m_hWnd, LB_GETCURSEL, 0, 0));
}

void CListBox::SetCurrentSelection(unsigned int index)
{
	SendMessage(m_hWnd, LB_SETCURSEL, index, 0);
}

INT_PTR CListBox::GetItemData(unsigned int index)
{
	return SendMessage(m_hWnd, LB_GETITEMDATA, index, 0);
}

void CListBox::SetItemData(unsigned int index, INT_PTR itemData)
{
	SendMessage(m_hWnd, LB_SETITEMDATA, index, itemData);
}
