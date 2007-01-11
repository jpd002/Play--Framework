#include "win32/ToolBar.h"
#include <commctrl.h>

using namespace Framework::Win32;

CToolBar::CToolBar(HWND hParent, unsigned int nBitmapNumber, HINSTANCE hInstance, unsigned int nBitmapId, unsigned int nButtonWidth, unsigned int nButtonHeight)
{
	InitCommonControls();

	m_hWnd = CreateToolbarEx(hParent, WS_VISIBLE, NULL, 
		nBitmapNumber, hInstance, nBitmapId, NULL, 0, nButtonWidth, nButtonHeight, nButtonWidth, nButtonHeight, sizeof(TBBUTTON));
}

CToolBar::~CToolBar()
{

}

void CToolBar::InsertButton(unsigned int nBitmapId, unsigned int nCommandId)
{
	TBBUTTON Button;

	memset(&Button, 0, sizeof(TBBUTTON));
	Button.iBitmap		= nBitmapId;
	Button.idCommand	= nCommandId;
	Button.fsState		= TBSTATE_ENABLED;
	Button.fsStyle		= TBSTYLE_BUTTON;

	SendMessage(m_hWnd, TB_ADDBUTTONS, 1, reinterpret_cast<LPARAM>(&Button));
}

void CToolBar::Resize()
{
	SendMessage(m_hWnd, TB_AUTOSIZE, 0, 0);
}
