#ifndef _MEMORYDEVICECONTEXT_H_
#define _MEMORYDEVICECONTEXT_H_

#include "DeviceContext.h"

namespace Framework
{
	namespace Win32
	{
		class CMemoryDeviceContext : public CDeviceContext
		{
		public:
						CMemoryDeviceContext(HDC);
			virtual		~CMemoryDeviceContext();
		};
	}
}

#endif
