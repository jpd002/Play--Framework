#include "win32/MemoryDeviceContext.h"

using namespace Framework;
using namespace Framework::Win32;

CMemoryDeviceContext::CMemoryDeviceContext(HDC hDC) :
CDeviceContext(CreateCompatibleDC(hDC))
{

}

CMemoryDeviceContext::~CMemoryDeviceContext()
{
	DeleteDC(m_nDC);
}
