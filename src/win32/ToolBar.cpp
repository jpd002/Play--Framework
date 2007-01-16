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
	m_ButtonToolTips[nId] = sText;
}

void CToolBar::ProcessNotify(WPARAM wParam, NMHDR* pHdr)
{
	if(pHdr->hwndFrom != GetToolTips()) return;

	switch(pHdr->code)
	{
	case TTN_GETDISPINFO:
		{
			LPTOOLTIPTEXT pToolTipText(reinterpret_cast<LPTOOLTIPTEXT>(pHdr));
				
			ButtonToolTipMap::iterator itToolTip;
			itToolTip = m_ButtonToolTips.find(pHdr->idFrom);

			if(itToolTip == m_ButtonToolTips.end()) return;

			pToolTipText->hinst		= GetModuleHandle(NULL);
			pToolTipText->lpszText	= const_cast<LPWSTR>((*itToolTip).second.c_str());
		}
		break;
	}
}
