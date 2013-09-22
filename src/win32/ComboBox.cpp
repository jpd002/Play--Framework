#include "win32/ComboBox.h"
#include "win32/DefaultFonts.h"

using namespace Framework;
using namespace Framework::Win32;

CComboBox::CComboBox(HWND hWnd)
{
	m_hWnd = hWnd;
}

CComboBox& CComboBox::operator =(CComboBox&& rhs)
{
	CWindow::Reset();
	CWindow::MoveFrom(std::move(rhs));
	return (*this);
}

CComboBox::CComboBox(HWND hParent, const RECT& rect, unsigned long nStyle)
{
	Create(NULL, _T("ComboBox"), _T(""), WS_VISIBLE | WS_CHILD | WS_VSCROLL | nStyle, rect, hParent, NULL);
	SetFont(CDefaultFonts::GetMessageFont());
}

unsigned int CComboBox::AddString(const TCHAR* sString)
{
	return (unsigned int)SendMessage(m_hWnd, CB_ADDSTRING, 0, (LPARAM)sString);
}

int CComboBox::GetSelection()
{
	return (int)SendMessage(m_hWnd, CB_GETCURSEL, 0, 0);
}

void CComboBox::SetSelection(int nIndex)
{
	SendMessage(m_hWnd, CB_SETCURSEL, nIndex, NULL);
}

unsigned int CComboBox::GetItemCount()
{
	return (unsigned int)SendMessage(m_hWnd, CB_GETCOUNT, 0, 0);
}

void CComboBox::SetItemData(unsigned int nIndex, uint32 nValue)
{
	SendMessage(m_hWnd, CB_SETITEMDATA, nIndex, (LPARAM)nValue);
}

uint32 CComboBox::GetItemData(unsigned int nIndex)
{
	return (uint32)SendMessage(m_hWnd, CB_GETITEMDATA, nIndex, 0); 
}

int CComboBox::FindItemData(uint32 nValue)
{
	unsigned int i, nCount;

	nCount = GetItemCount();
	for(i = 0; i < nCount; i++)
	{
		if(GetItemData(i) == nValue) return i;
	}

	return -1;
}

void CComboBox::FixHeight(unsigned int nHeight)
{
	RECT rc = GetClientRect();
	SetSize(rc.right - rc.left, nHeight);
}

void CComboBox::ResetContent()
{
	SendMessage(m_hWnd, CB_RESETCONTENT, 0, 0);
}
