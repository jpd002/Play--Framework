#include "win32/InputBox.h"
#include "PtrMacro.h"
#include "layout/HorizontalLayout.h"
#include "layout/LayoutStretch.h"
#include "win32/Static.h"
#include "win32/LayoutWindow.h"
#include "win32/DefaultFonts.h"
#include "win32/AcceleratorTableGenerator.h"

#define CLSNAME		_T("CInputBox")
#define WNDSTYLE	(WS_CAPTION | WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU)
#define WNDSTYLEEX	(WS_EX_DLGMODALFRAME)

#define IDC_SELECTALL	(0xBEEF)
#define SCALE(x)		MulDiv(x, ydpi, 96)

using namespace Framework;
using namespace Framework::Win32;

CInputBox::CInputBox(const TCHAR* sTitle, const TCHAR* sPrompt, const TCHAR* sValue)
: m_pOk(NULL)
, m_pCancel(NULL)
, m_pValue(NULL)
, m_nCancelled(false)
, m_sTitle(sTitle)
, m_sPrompt(sPrompt)
, m_sValue((sValue != NULL) ? sValue : _T(""))
, m_isMultiline(false)
{

}

CInputBox::~CInputBox()
{

}

void CInputBox::SetIsMultiline(bool isMultiline)
{
	m_isMultiline = isMultiline;
}

const TCHAR* CInputBox::GetValue(HWND hParent)
{
	EnableWindow(GetActiveWindow(), FALSE);

	HFONT nFont = CDefaultFonts::GetMessageFont();

	if(!DoesWindowClassExist(CLSNAME))
	{
		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(WNDCLASSEX));
		wc.cbSize			= sizeof(WNDCLASSEX);
		wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW); 
		wc.hInstance		= GetModuleHandle(NULL);
		wc.lpszClassName	= CLSNAME;
		wc.lpfnWndProc		= CWindow::WndProc;
		RegisterClassEx(&wc);
	}

	int ydpi = GetDeviceCaps(GetDC(NULL), LOGPIXELSY);

	{
		RECT rc;
		if(m_isMultiline)
		{
			SetRect(&rc, 0, 0, SCALE(300), SCALE(150));
		}
		else
		{
			SetRect(&rc, 0, 0, SCALE(300), SCALE(115));
		}
		Create(WNDSTYLEEX, CLSNAME, m_sTitle.c_str(), WNDSTYLE, rc, hParent, NULL);
		SetClassPtr();
	}

	m_pOk = new CButton(_T("OK"), m_hWnd, CRect(0, 0, 0, 0));
	m_pOk->SetFont(nFont);
	m_pOk->ModifyStyleOr(BS_DEFPUSHBUTTON);

	m_pCancel = new CButton(_T("Cancel"), m_hWnd, CRect(0, 0, 0, 0));
	m_pCancel->SetFont(nFont);

	m_pValue = new CEdit(m_hWnd, CRect(0, 0, 0, 0), m_sValue.c_str(), m_isMultiline ? ES_MULTILINE : 0);
	m_pValue->SetFont(nFont);
	m_pValue->SetSelection(0, -1);
	m_pValue->SetFocus();
	
	FlatLayoutPtr pSubLayout0 = CHorizontalLayout::Create();
	pSubLayout0->InsertObject(CLayoutStretch::Create());
	pSubLayout0->InsertObject(CLayoutWindow::CreateButtonBehavior(SCALE(75), SCALE(23), m_pOk));
	pSubLayout0->InsertObject(CLayoutWindow::CreateButtonBehavior(SCALE(75), SCALE(23), m_pCancel));
	pSubLayout0->SetVerticalStretch(0);

	m_layout = CVerticalLayout::Create();
	m_layout->InsertObject(CLayoutWindow::CreateTextBoxBehavior(SCALE(100), SCALE(14), new CStatic(m_hWnd, m_sPrompt.c_str())));
	if(m_isMultiline)
	{
		m_layout->InsertObject(CLayoutWindow::CreateCustomBehavior(SCALE(100), SCALE(20), 1, 1, m_pValue));
	}
	else
	{
		m_layout->InsertObject(CLayoutWindow::CreateTextBoxBehavior(SCALE(100), SCALE(21), m_pValue));
		m_layout->InsertObject(CLayoutStretch::Create());
	}
	m_layout->InsertObject(pSubLayout0);

	RefreshLayout();

	HACCEL hAccel = CreateAccelerators();

	Center();
	Show(SW_SHOW);

	while(IsWindow())
	{
		MSG msg;
		GetMessage(&msg, NULL, 0, 0);
		if(!TranslateAccelerator(m_hWnd, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	DestroyAcceleratorTable(hAccel);

	return m_nCancelled ? NULL : m_sValue.c_str();
}

void CInputBox::RefreshLayout()
{
	RECT rc = GetClientRect();
	
	rc.left		+= 10;
	rc.right	-= 10;
	rc.top		+= 7;
	rc.bottom	-= 7;

	m_layout->SetRect(rc.left, rc.top, rc.right, rc.bottom);
	m_layout->RefreshGeometry();
}

void CInputBox::RestoreFocus()
{
	EnableWindow(GetParent(), TRUE);
	SetForegroundWindow(GetParent());
}

void CInputBox::ConfirmDialog()
{
	TCHAR sTemp[256];
	
	m_pValue->GetText(sTemp, 255);
	m_sValue = sTemp;

	m_nCancelled = false;

	RestoreFocus();
	Destroy();
}

void CInputBox::CancelDialog()
{
	m_nCancelled = true;

	RestoreFocus();
	Destroy();
}

HACCEL CInputBox::CreateAccelerators()
{
	CAcceleratorTableGenerator generator;
	generator.Insert(IDOK,			VK_RETURN,	FVIRTKEY);
	generator.Insert(IDCANCEL,		VK_ESCAPE,	FVIRTKEY);
	generator.Insert(IDC_SELECTALL,	'A',		FVIRTKEY | FCONTROL);
	return generator.Create();
}

long CInputBox::OnCommand(unsigned short nID, unsigned short nSubMsg, HWND hSender)
{
	if((hSender == m_pOk->m_hWnd) || (nID == IDOK))
	{
		ConfirmDialog();
		return FALSE;
	}
	else if((hSender == m_pCancel->m_hWnd) || (nID == IDCANCEL))
	{
		CancelDialog();
		return FALSE;
	}
	else if(nID == IDC_SELECTALL)
	{
		HWND focusWnd = GetFocus();
		if(focusWnd == m_pValue->m_hWnd)
		{
			SendMessage(m_pValue->m_hWnd, EM_SETSEL, 0, -1);
		}
		return FALSE;
	}
	return TRUE;
}

long CInputBox::OnSysCommand(unsigned int nCmd, LPARAM lParam)
{
	switch(nCmd)
	{
	case SC_CLOSE:
		CancelDialog();
		return TRUE;
	}
	return TRUE;
}
