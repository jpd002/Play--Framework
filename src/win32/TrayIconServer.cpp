#include "win32/TrayIconServer.h"
#include "win32/Rect.h"

#define WM_TRAY (WM_USER)

using namespace Framework;
using namespace Framework::Win32;

CTrayIconServer::CTrayIconServer()
{
	m_taskBarCreatedMessage = RegisterWindowMessage(_T("TaskbarCreated"));
	Create(NULL, CDefaultWndClass::GetName(), _T(""), NULL, Framework::Win32::CRect(0, 0, 0, 0), NULL, NULL);
	SetClassPtr();
}

CTrayIconServer::~CTrayIconServer()
{
	DestroyWindow(m_hWnd);
}

void CTrayIconServer::RegisterHandler(const IconEventHandlerType& Handler)
{
	m_iconEventSignal.connect(Handler);
}

CTrayIcon* CTrayIconServer::Insert()
{
	unsigned int iconId = m_nextIconId++;
	auto icon = std::make_unique<CTrayIcon>(m_hWnd, iconId);
	auto result = icon.get();
	icon->SetMessage(WM_TRAY);
	m_icons.insert(std::make_pair(iconId, std::move(icon)));
	return result;
}

LRESULT CTrayIconServer::OnWndProc(unsigned int uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uiMsg)
	{
	case WM_TRAY:
		{
			auto iconIterator = m_icons.find(static_cast<unsigned int>(wParam));
			if(iconIterator != std::end(m_icons))
			{
				m_iconEventSignal(iconIterator->second.get(), lParam);
			}
		}
		return FALSE;
		break;
	}
	if(uiMsg == m_taskBarCreatedMessage)
	{
		for(const auto& iconPair : m_icons)
		{
			iconPair.second->Rebuild();
		}
	}
	return TRUE;
}
