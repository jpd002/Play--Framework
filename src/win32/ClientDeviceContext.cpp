#include "win32/ClientDeviceContext.h"
#include <cassert>

using namespace Framework;
using namespace Framework::Win32;

CClientDeviceContext::CClientDeviceContext(HWND wnd)
: CDeviceContext(GetDC(wnd))
, m_wnd(wnd)
{

}

CClientDeviceContext::~CClientDeviceContext()
{
	int result = ReleaseDC(m_wnd, m_dc);
	assert(result == 1);
}
