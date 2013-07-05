#ifndef _CLIENTDEVICECONTEXT_H_
#define _CLIENTDEVICECONTEXT_H_

#include "win32/DeviceContext.h"

namespace Framework
{
	namespace Win32
	{
		class CClientDeviceContext : public CDeviceContext
		{
		public:
						CClientDeviceContext(HWND);
			virtual		~CClientDeviceContext();

		private:
			HWND		m_wnd;
		};
	}
}

#endif
