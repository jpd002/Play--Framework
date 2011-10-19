#include "win32/InputBox.h"
#include "PtrMacro.h"
#include "layout/HorizontalLayout.h"
#include "layout/LayoutStretch.h"
#include "win32/Static.h"
#include "win32/LayoutWindow.h"

#define CLSNAME		_T("CInputBox")
#define WNDSTYLE	(WS_CAPTION | WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU)
#define WNDSTYLEEX	(WS_EX_DLGMODALFRAME)

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
{

}

CInputBox::~CInputBox()
{

}

const TCHAR* CInputBox::GetValue(HWND hParent)
{
	EnableWindow(GetActiveWindow(), FALSE);

	HFONT nFont = CreateFont(-11, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, _T("Tahoma"));

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

	RECT rc;
	SetRect(&rc, 0, 0, 300, 108);
	Create(WNDSTYLEEX, CLSNAME, m_sTitle.c_str(), WNDSTYLE, &rc, hParent, NULL);
	SetClassPtr();

	SetRect(&rc, 0, 0, 0, 0);

	m_pOk = new CButton(_T("OK"), m_hWnd, &rc);
	m_pOk->SetFont(nFont);
	m_pOk->ModifyStyleOr(BS_DEFPUSHBUTTON);

	m_pCancel = new CButton(_T("Cancel"), m_hWnd, &rc);
	m_pCancel->SetFont(nFont);

	m_pValue = new CEdit(m_hWnd, &rc, m_sValue.c_str());
	m_pValue->SetFont(nFont);
	m_pValue->SetSelection(0, -1);
	m_pValue->SetFocus();
	
    FlatLayoutPtr pSubLayout0 = CHorizontalLayout::Create();
    pSubLayout0->InsertObject(CLayoutStretch::Create());
	pSubLayout0->InsertObject(CLayoutWindow::CreateButtonBehavior(75, 23, m_pOk));
	pSubLayout0->InsertObject(CLayoutWindow::CreateButtonBehavior(75, 23, m_pCancel));
	pSubLayout0->SetVerticalStretch(0);

    m_layout = CVerticalLayout::Create();
	m_layout->InsertObject(CLayoutWindow::CreateTextBoxBehavior(100, 14, new CStatic(m_hWnd, m_sPrompt.c_str())));
	m_layout->InsertObject(CLayoutWindow::CreateTextBoxBehavior(100, 20, m_pValue));
	m_layout->InsertObject(pSubLayout0);
    m_layout->InsertObject(CLayoutStretch::Create());

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
	DeleteObject(nFont);

	return m_nCancelled ? NULL : m_sValue.c_str();
}

void CInputBox::RefreshLayout()
{
	RECT rc;
	GetClientRect(&rc);
	
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
	ACCEL Accel[2];

	Accel[0].cmd	= IDOK;
	Accel[0].key	= VK_RETURN;
	Accel[0].fVirt	= FVIRTKEY;

	Accel[1].cmd	= IDCANCEL;
	Accel[1].key	= VK_ESCAPE;
	Accel[1].fVirt	= FVIRTKEY;

	return CreateAcceleratorTable(Accel, sizeof(Accel) / sizeof(ACCEL));
}

long CInputBox::OnCommand(unsigned short nID, unsigned short nSubMsg, HWND hSender)
{
	if((hSender == m_pOk->m_hWnd) || (nID == IDOK))
	{
		ConfirmDialog();
		return FALSE;
	}
	if((hSender == m_pCancel->m_hWnd) || (nID == IDCANCEL))
	{
		CancelDialog();
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
