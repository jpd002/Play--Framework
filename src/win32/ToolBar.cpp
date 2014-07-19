#include "win32/ToolBar.h"
#include <commctrl.h>

using namespace Framework::Win32;

CToolBar::CToolBar(HWND hParent, unsigned int nBitmapNumber, HINSTANCE hInstance, unsigned int nBitmapId, unsigned int nButtonWidth, unsigned int nButtonHeight)
{
	InitCommonControls();

	m_hWnd = CreateToolbarEx(hParent, WS_VISIBLE | TBSTYLE_TOOLTIPS, NULL, 
		nBitmapNumber, hInstance, nBitmapId, NULL, 0, nButtonWidth, nButtonHeight, nButtonWidth, nButtonHeight, sizeof(TBBUTTON));
}

CToolBar::CToolBar(HWND hParent)
{
	InitCommonControls();

	m_hWnd = CreateWindowEx(NULL, TOOLBARCLASSNAME, NULL, WS_VISIBLE | WS_CHILD | TBSTYLE_TOOLTIPS, 0, 0, 1, 1, hParent, NULL, GetModuleHandle(NULL), NULL);
	SendMessage(m_hWnd, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);
}

CToolBar::~CToolBar()
{

}

CToolBar& CToolBar::operator =(CToolBar&& rhs)
{
	Reset();
	MoveFrom(std::move(rhs));
	return (*this);
}

void CToolBar::Reset()
{
	m_buttonToolTips.clear();
	CWindow::Reset();
}

void CToolBar::MoveFrom(CToolBar&& rhs)
{
	m_buttonToolTips = std::move(rhs.m_buttonToolTips);
	CWindow::MoveFrom(std::move(rhs));
}

void CToolBar::InsertImageButton(unsigned int nBitmapId, unsigned int nCommandId)
{
	TBBUTTON Button;

	memset(&Button, 0, sizeof(TBBUTTON));
	Button.iBitmap		= nBitmapId;
	Button.idCommand	= nCommandId;
	Button.fsState		= TBSTATE_ENABLED;
	Button.fsStyle		= TBSTYLE_BUTTON;

	SendMessage(m_hWnd, TB_ADDBUTTONS, 1, reinterpret_cast<LPARAM>(&Button));
}

void CToolBar::InsertTextButton(const TCHAR* sText, unsigned int nCommandId)
{
	TBBUTTON Button;

	memset(&Button, 0, sizeof(TBBUTTON));
	Button.iBitmap		= I_IMAGENONE;
	Button.idCommand	= nCommandId;
	Button.fsState		= TBSTATE_ENABLED;
	Button.fsStyle		= TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE;
	Button.iString		= reinterpret_cast<INT_PTR>(sText);

	SendMessage(m_hWnd, TB_ADDBUTTONS, 1, reinterpret_cast<LPARAM>(&Button));
}

void CToolBar::LoadStandardImageList(unsigned int nIndex)
{
	SendMessage(m_hWnd, TB_LOADIMAGES, nIndex, reinterpret_cast<LPARAM>(HINST_COMMCTRL));
}

void CToolBar::Resize()
{
	SendMessage(m_hWnd, TB_AUTOSIZE, 0, 0);
}

HWND CToolBar::GetToolTips()
{
	return reinterpret_cast<HWND>(SendMessage(m_hWnd, TB_GETTOOLTIPS, NULL, NULL));
}

void CToolBar::SetButtonToolTipText(unsigned int nId, const TCHAR* sText)
{
	m_buttonToolTips[nId] = sText;
}

void CToolBar::SetButtonChecked(unsigned int id, bool checked)
{
	TBBUTTONINFO buttonInfo = {};
	buttonInfo.cbSize		= sizeof(TBBUTTONINFO);
	buttonInfo.idCommand	= id;
	buttonInfo.fsState		= TBSTATE_ENABLED | (checked ? TBSTATE_CHECKED : 0);
	buttonInfo.dwMask		= TBIF_STATE;

	SendMessage(m_hWnd, TB_SETBUTTONINFO, id, reinterpret_cast<LPARAM>(&buttonInfo));
}

void CToolBar::ProcessNotify(WPARAM wparam, NMHDR* hdr)
{
	if(hdr->hwndFrom != GetToolTips()) return;

	switch(hdr->code)
	{
	case TTN_GETDISPINFO:
		{
			LPTOOLTIPTEXT toolTipText(reinterpret_cast<LPTOOLTIPTEXT>(hdr));

			auto toolTipIterator = m_buttonToolTips.find(static_cast<unsigned int>(hdr->idFrom));
			if(toolTipIterator == m_buttonToolTips.end()) return;

			toolTipText->hinst		= GetModuleHandle(NULL);
			toolTipText->lpszText	= const_cast<LPWSTR>((*toolTipIterator).second.c_str());
		}
		break;
	}
}
