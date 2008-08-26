#include "win32/ModalWindow.h"

using namespace Framework::Win32;

CModalWindow::CModalWindow(HWND hParent)
{
	if(hParent != NULL)
	{
		EnableWindow(hParent, FALSE);
	}
}

CModalWindow::~CModalWindow()
{

}

void CModalWindow::DoModal()
{
	Center(GetParent());
	Show(SW_SHOW);

	CWindow::StdMsgLoop(this);
}

long CModalWindow::OnSysCommand(unsigned int nCmd, LPARAM lParam)
{
	switch(nCmd)
	{
	case SC_CLOSE:
		UnModalWindow();
		break;
	}
	return TRUE;
}

unsigned int CModalWindow::Destroy()
{
	UnModalWindow();
	return CWindow::Destroy();
}

void CModalWindow::UnModalWindow()
{
	if(GetParent() != NULL)
	{
		EnableWindow(GetParent(), TRUE);
		SetForegroundWindow(GetParent());
	}
}
