#include "win32/Edit.h"
#include "win32/DefaultFonts.h"
#include <CommCtrl.h>

using namespace Framework;
using namespace Framework::Win32;

CEdit::CEdit(HWND hWnd)
{
	m_hWnd = hWnd;
}

CEdit::CEdit(HWND hParent, const RECT& rect, const TCHAR* sText, unsigned long nStyle, unsigned long nStyleEx)
{
	Create(nStyleEx, WC_EDIT, sText, WS_VISIBLE | WS_CHILD | nStyle, rect, hParent, NULL);
	SetFont(CDefaultFonts::GetMessageFont());
}

CEdit& CEdit::operator =(CEdit&& rhs)
{
	CWindow::Reset();
	CWindow::MoveFrom(std::move(rhs));
	return (*this);
}

void CEdit::SetSelection(int nStart, int nEnd)
{
	SendMessage(m_hWnd, EM_SETSEL, nStart, nEnd);
}

void CEdit::ReplaceSelectionA(bool nCanBeUndone, const char* sText)
{
	SendMessageA(m_hWnd, EM_REPLACESEL, nCanBeUndone, (LPARAM)sText);
}

void CEdit::SetTextLimit(int nLimit)
{
	SendMessage(m_hWnd, EM_LIMITTEXT, nLimit, 0);
}

void CEdit::SetLeftMargin(unsigned int nMargin)
{
	SendMessage(m_hWnd, EM_SETMARGINS, EC_LEFTMARGIN, MAKEWORD(nMargin, 0));
}
