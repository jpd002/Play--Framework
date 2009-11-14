#include "win32/TrayIcon.h"

using namespace Framework;
using namespace Framework::Win32;

CTrayIcon::CTrayIcon(HWND hWnd, unsigned int nID)
: m_message(0)
, m_icon(NULL)
{
	m_hWnd = hWnd;
	m_nID = nID;
	Add();
}

CTrayIcon::~CTrayIcon()
{
	Delete();
}

void CTrayIcon::InitStructure(NOTIFYICONDATA* pD)
{
	memset(pD, 0, sizeof(NOTIFYICONDATA));
    pD->cbSize  = sizeof(NOTIFYICONDATA);
	pD->hWnd    = m_hWnd;
	pD->uID     = m_nID;
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

void CTrayIcon::SetMessage(unsigned int nMessage)
{
	NOTIFYICONDATA d;
	InitStructure(&d);
	d.uCallbackMessage = nMessage;
	d.uFlags = NIF_MESSAGE;
	Shell_NotifyIcon(NIM_MODIFY, &d);

    m_message = nMessage;
}

void CTrayIcon::SetTip(const TCHAR* sTip)
{
	NOTIFYICONDATA d;
	InitStructure(&d);
    _tcsncpy(d.szTip, sTip, sizeof(d.szTip) / sizeof(TCHAR));
	d.uFlags = NIF_TIP;
	Shell_NotifyIcon(NIM_MODIFY, &d);

    m_tip = sTip;
}

void CTrayIcon::SetIcon(HICON hIcon)
{
	NOTIFYICONDATA d;
	InitStructure(&d);
	d.hIcon     = hIcon;
	d.uFlags    = NIF_ICON;
	Shell_NotifyIcon(NIM_MODIFY, &d);

    m_icon = hIcon;
}

unsigned int CTrayIcon::GetID()
{
	return m_nID;
}