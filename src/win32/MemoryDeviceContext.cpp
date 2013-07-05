#include "win32/MemoryDeviceContext.h"

using namespace Framework;
using namespace Framework::Win32;

CMemoryDeviceContext::CMemoryDeviceContext(HDC dc) :
CDeviceContext(CreateCompatibleDC(dc))
{

}

CMemoryDeviceContext::~CMemoryDeviceContext()
{
	DeleteDC(m_dc);
}
