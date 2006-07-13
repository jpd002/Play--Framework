#include "win32/ClientDeviceContext.h"

using namespace Framework;
using namespace Framework::Win32;

CClientDeviceContext::CClientDeviceContext(HWND nWnd) :
CDeviceContext(GetDC(nWnd))
{
	m_nWnd = nWnd;
}

CClientDeviceContext::~CClientDeviceContext()
{
	ReleaseDC(m_nWnd, m_nDC);
}
