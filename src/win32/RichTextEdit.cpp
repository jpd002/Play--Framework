#include "win32/RichTextEdit.h"
#include <commctrl.h>

using namespace Framework::Win32;

CRichTextEdit::CRichTextEdit(HWND hParent, const RECT& rect, DWORD nStyle, DWORD nExStyle)
{
	InitCommonControls();
	if(LoadLibrary(_T("riched20.dll")) == NULL)
	{
		throw std::exception();
	}
	Create(nExStyle, RICHEDIT_CLASS, _T(""), WS_CHILD | WS_VISIBLE | nStyle, rect, hParent, NULL);
}

CRichTextEdit::~CRichTextEdit()
{

}

int CRichTextEdit::GetCharFromPosition(int nX, int nY)
{
	POINTL Point;
	Point.x = nX;
	Point.y = nY;
	return static_cast<int>(SendMessage(m_hWnd, EM_CHARFROMPOS, NULL, reinterpret_cast<LPARAM>(&Point)));
}

POINTL CRichTextEdit::GetPositionFromChar(int nChar)
{
	POINTL Point;
	SendMessage(m_hWnd, EM_POSFROMCHAR, reinterpret_cast<WPARAM>(&Point), nChar);
	return Point;
}

void CRichTextEdit::SetSelection(int nStart, int nEnd)
{
	CHARRANGE Range;
	Range.cpMin = nStart;
	Range.cpMax = nEnd;
	SendMessage(m_hWnd, EM_EXSETSEL, 0, reinterpret_cast<LPARAM>(&Range));
}

void CRichTextEdit::SetSelectionAsLink(bool bSet)
{
	CHARFORMAT2 CharFormat;
	memset(&CharFormat, 0, sizeof(CharFormat));
	CharFormat.cbSize = sizeof(CharFormat);
	CharFormat.dwMask = CFM_LINK;
	CharFormat.dwEffects = (bSet ? CFE_LINK : 0);
	SendMessage(m_hWnd, EM_SETCHARFORMAT, SCF_SELECTION, reinterpret_cast<LPARAM>(&CharFormat));
}

void CRichTextEdit::SetEventMask(unsigned int nMask)
{
	SendMessage(m_hWnd, EM_SETEVENTMASK, 0, nMask);
}
