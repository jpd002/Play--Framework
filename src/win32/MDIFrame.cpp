#include "win32/MDIFrame.h"
#include "PtrMacro.h"

using namespace Framework;
using namespace Framework::Win32;

CMDIFrame::CMDIFrame()
{
	m_pMDIClient = NULL;
}

CMDIFrame::~CMDIFrame()
{
	DELETEPTR(m_pMDIClient);
}

long CMDIFrame::OnWndProc(unsigned int nMsg, WPARAM wParam, LPARAM lParam)
{
	if(m_pMDIClient != NULL)
	{
		return (long)DefFrameProc(m_hWnd, m_pMDIClient->m_hWnd, nMsg, wParam, lParam);
	}
	else
	{
		return (long)DefFrameProc(m_hWnd, NULL, nMsg, wParam, lParam);
	}
}

void CMDIFrame::CreateClient(HMENU hMenu)
{
	m_pMDIClient = new CMDIClient(m_hWnd, hMenu);
}
