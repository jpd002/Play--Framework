#include "win32/TrayIcon.h"

using namespace Framework;
using namespace Framework::Win32;

CTrayIcon::CTrayIcon(HWND wnd, unsigned int id)
: m_message(0)
, m_icon(NULL)
, m_wnd(wnd)
, m_id(id)
{
	Add();
}

CTrayIcon::~CTrayIcon()
{
	Delete();
}

void CTrayIcon::InitStructure(NOTIFYICONDATA* pD)
{
	memset(pD, 0, sizeof(NOTIFYICONDATA));
	pD->cbSize	= sizeof(NOTIFYICONDATA);
	pD->hWnd	= m_wnd;
	pD->uID		= m_id;
}

void CTrayIcon::Add()
{
	NOTIFYICONDATA d;
	InitStructure(&d);
	Shell_NotifyIcon(NIM_ADD, &d);
}

void CTrayIcon::Delete()
{
	NOTIFYICONDATA d;
	InitStructure(&d);
	Shell_NotifyIcon(NIM_DELETE, &d);
}

void CTrayIcon::Rebuild()
{
	Add();

	if(m_icon != NULL)
	{
		SetIcon(m_icon);
	}

	if(m_message != 0)
	{
		SetMessage(m_message);
	}

	if(m_tip.length() != 0)
	{
		SetTip(m_tip.c_str());
	}
}

void CTrayIcon::SetMessage(unsigned int message)
{
	NOTIFYICONDATA d;
	InitStructure(&d);
	d.uCallbackMessage = message;
	d.uFlags = NIF_MESSAGE;
	Shell_NotifyIcon(NIM_MODIFY, &d);

	m_message = message;
}

void CTrayIcon::SetTip(const TCHAR* tip)
{
	NOTIFYICONDATA d;
	InitStructure(&d);
	_tcsncpy(d.szTip, tip, sizeof(d.szTip) / sizeof(TCHAR));
	d.uFlags = NIF_TIP;
	Shell_NotifyIcon(NIM_MODIFY, &d);
	
	m_tip = tip;
}

void CTrayIcon::SetIcon(HICON icon)
{
	NOTIFYICONDATA d;
	InitStructure(&d);
	d.hIcon		= icon;
	d.uFlags	= NIF_ICON;
	Shell_NotifyIcon(NIM_MODIFY, &d);

	m_icon = icon;
}

unsigned int CTrayIcon::GetID() const
{
	return m_id;
}
