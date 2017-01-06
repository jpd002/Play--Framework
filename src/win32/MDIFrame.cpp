#include <cassert>
#include "win32/MDIFrame.h"

using namespace Framework;
using namespace Framework::Win32;

long CMDIFrame::OnWndProc(unsigned int nMsg, WPARAM wParam, LPARAM lParam)
{
	if(m_pMDIClient)
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
	assert(!m_pMDIClient);
	m_pMDIClient = std::make_unique<CMDIClient>(m_hWnd, hMenu);
}
