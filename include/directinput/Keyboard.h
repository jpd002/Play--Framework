#pragma once

#include "Device.h"

namespace Framework
{
	namespace DirectInput
	{
		class CKeyboard : public CDevice
		{
		public:
									CKeyboard(const DirectInputDevicePtr&, HWND);
			virtual					~CKeyboard();

			void					ProcessEvents(const InputEventHandler&) override;
		};
	}
}
