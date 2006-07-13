#include "win32/MDIClient.h"

using namespace Framework;

CMDIClient::CMDIClient(HWND hParent, HMENU hMenu)
{
	CLIENTCREATESTRUCT ccs;
	memset(&ccs, 0, sizeof(CLIENTCREATESTRUCT));
	ccs.hWindowMenu = hMenu;
	m_hWnd = CreateWindow(_X("MDICLIENT"), _X(""), WS_CLIPCHILDREN | WS_CHILD | WS_VSCROLL | WS_HSCROLL, 0, 0, 600, 600, hParent, (HMENU)0xCAC, GetModuleHandle(NULL), &ccs);
	Show(SW_SHOW);
}

CMDIClient::~CMDIClient()
{

}

void CMDIClient::Cascade()
{
	SendMessage(m_hWnd, WM_MDICASCADE, NULL, NULL);
}

void CMDIClient::TileHorizontal()
{
	SendMessage(m_hWnd, WM_MDITILE, MDITILE_HORIZONTAL, NULL);
}

void CMDIClient::TileVertical()
{
	SendMessage(m_hWnd, WM_MDITILE, MDITILE_VERTICAL, NULL);
}
