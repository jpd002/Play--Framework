#include "win32/TrayIconServer.h"
#include "win32/Rect.h"

#define CLSNAME _T("TrayIconServer")
#define WM_TRAY (WM_USER)

using namespace Framework;
using namespace Framework::Win32;

CTrayIconServer::CTrayIconServer()
: m_taskBarCreatedMessage(0)
{
	m_taskBarCreatedMessage = RegisterWindowMessage(_T("TaskbarCreated"));

	if(!DoesWindowClassExist(CLSNAME))
	{
		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(WNDCLASSEX));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpfnWndProc = CWindow::WndProc;
		wc.lpszClassName = CLSNAME;
		wc.hInstance = GetModuleHandle(NULL);
		RegisterClassEx(&wc);
	}

	Create(NULL, CLSNAME, _T(""), NULL, Framework::Win32::CRect(0, 0, 0, 0), NULL, NULL);
	SetClassPtr();
}

CTrayIconServer::~CTrayIconServer()
{
	DestroyWindow(m_hWnd);
}

void CTrayIconServer::RegisterHandler(const IconEventHandlerType& Handler)
{
    m_IconEventSignal.connect(Handler);
}

CTrayIcon* CTrayIconServer::Insert()
{
    unsigned int nID = static_cast<unsigned int>(m_Icons.size());
	CTrayIcon* pIcon = new CTrayIcon(m_hWnd, nID);
    pIcon->SetMessage(WM_TRAY);

    m_Icons.insert(nID, pIcon);

    return pIcon;
}

long CTrayIconServer::OnWndProc(unsigned int uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uiMsg)
	{
	case WM_TRAY:
        {
            TrayIconMapType::iterator itIcon = m_Icons.find(wParam);
            if(itIcon != m_Icons.end())
            {
                m_IconEventSignal(&(*itIcon->second), lParam);
            }
        }
		return FALSE;
		break;
	}
    if(uiMsg == m_taskBarCreatedMessage)
    {
        for(TrayIconMapType::iterator itIcon = m_Icons.begin();
            itIcon != m_Icons.end(); itIcon++)
        {
            itIcon->second->Rebuild();
        }
    }
	return TRUE;
}
