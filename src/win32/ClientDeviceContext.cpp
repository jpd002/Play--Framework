#include "win32/ClientDeviceContext.h"

using namespace Framework;
using namespace Framework::Win32;

CClientDeviceContext::CClientDeviceContext(HWND wnd)
: CDeviceContext(GetDC(wnd))
, m_wnd(wnd)
{

}

CClientDeviceContext::~CClientDeviceContext()
{
	ReleaseDC(m_wnd, m_dc);
}
