#pragma once

#include "DirectInput.h"
#include <functional>
#include "Types.h"
#include "win32/ComPtr.h"

namespace Framework
{
	namespace DirectInput
	{
		class CDevice
		{
		public:
			typedef std::function<void (const GUID&, uint32, uint32)> InputEventHandler;
			typedef Framework::Win32::CComPtr<IDirectInputDevice8> DirectInputDevicePtr;

										CDevice(const DirectInputDevicePtr&);
			virtual						~CDevice();

			virtual void				ProcessEvents(const InputEventHandler&) = 0;
			bool						GetInfo(DIDEVICEINSTANCE*);
			bool						GetObjectInfo(uint32, DIDEVICEOBJECTINSTANCE*);
			void						SetFocusWindow(HWND);

		protected:
			DirectInputDevicePtr		m_device;
		};
	}
}
