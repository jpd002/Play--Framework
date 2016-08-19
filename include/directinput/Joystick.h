#pragma once

#include "DirectInput.h"
#include "Device.h"

namespace Framework
{
	namespace DirectInput
	{
		class CJoystick : public CDevice
		{
		public:
									CJoystick(const DirectInputDevicePtr&);
			virtual					~CJoystick();

			int						GetButtonCount() const;
			void					ProcessEvents(const InputEventHandler&) override;

		private:
			static BOOL CALLBACK	EnumObjectsCallback(LPCDIDEVICEOBJECTINSTANCE, LPVOID);
			BOOL					EnumObjectsCallbackImpl(LPCDIDEVICEOBJECTINSTANCE);

			GUID					m_deviceGuid;
			int						m_buttonCount;
		};
	}
}
