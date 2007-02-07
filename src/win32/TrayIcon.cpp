#include "win32/TrayIcon.h"

using namespace Framework;
using namespace Framework::Win32;

CTrayIcon::CTrayIcon(HWND hWnd, unsigned int nID)
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

void CTrayIcon::SetMessage(unsigned int nMessage)
{
	NOTIFYICONDATA d;
	InitStructure(&d);
	d.uCallbackMessage = nMessage;
	d.uFlags = NIF_MESSAGE;
	Shell_NotifyIcon(NIM_MODIFY, &d);
}

void CTrayIcon::SetTip(TCHAR* sTip)
{
	NOTIFYICONDATA d;
	InitStructure(&d);
    _tcscpy(d.szTip, sTip);
	d.uFlags = NIF_TIP;
	Shell_NotifyIcon(NIM_MODIFY, &d);
}

void CTrayIcon::SetIcon(HICON hIcon)
{
	NOTIFYICONDATA d;
	InitStructure(&d);
	d.hIcon     = hIcon;
	d.uFlags    = NIF_ICON;
	Shell_NotifyIcon(NIM_MODIFY, &d);
}

unsigned int CTrayIcon::GetID()
{
	return m_nID;
}