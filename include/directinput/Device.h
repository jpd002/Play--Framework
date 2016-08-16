#pragma once

#include "DirectInput.h"
#include <functional>
#include "Types.h"

namespace Framework
{
	namespace DirectInput
	{
		class CDevice
		{
		public:
			typedef std::function<void (const GUID&, uint32, uint32)> InputEventHandler;

										CDevice(LPDIRECTINPUTDEVICE8);
			virtual						~CDevice();

			virtual void				ProcessEvents(const InputEventHandler&) = 0;
			bool						GetInfo(DIDEVICEINSTANCE*);
			bool						GetObjectInfo(uint32, DIDEVICEOBJECTINSTANCE*);

		protected:
			LPDIRECTINPUTDEVICE8		m_device;
		};
	}
}
