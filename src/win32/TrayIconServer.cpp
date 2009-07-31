#include "win32/TrayIconServer.h"

#define CLSNAME _T("TrayIconServer")
#define WM_TRAY (WM_USER)

using namespace Framework;
using namespace Framework::Win32;

CTrayIconServer::CTrayIconServer()
{
	RECT rc;

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

	SetRect(&rc, 0, 0, 0, 0);

	Create(NULL, CLSNAME, _T(""), NULL, &rc, NULL, NULL);
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
	CTrayIcon* pIcon;
	unsigned int nID;

    nID = static_cast<unsigned int>(m_Icons.size());
	pIcon = new CTrayIcon(m_hWnd, nID);
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
            TrayIconMapType::iterator itIcon;
            itIcon = m_Icons.find(wParam);
            if(itIcon != m_Icons.end())
            {
                m_IconEventSignal(&(*itIcon->second), lParam);
            }
        }
		return FALSE;
		break;
	}
	return TRUE;
}
