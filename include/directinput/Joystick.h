#ifndef _DIRECTINPUTJOYSTICK_H_
#define _DIRECTINPUTJOYSTICK_H_

#include "DirectInput.h"
#include "Device.h"

namespace Framework
{
	namespace DirectInput
	{
		class CJoystick : public CDevice
		{
		public:
									CJoystick(LPDIRECTINPUTDEVICE8, HWND);
			virtual					~CJoystick();

			int						GetButtonCount() const;
			virtual void			ProcessEvents(const InputEventHandler&);

		private:
			static BOOL CALLBACK	EnumObjectsCallback(LPCDIDEVICEOBJECTINSTANCE, LPVOID);
			BOOL					EnumObjectsCallbackImpl(LPCDIDEVICEOBJECTINSTANCE);

			GUID					m_deviceGuid;
			int						m_buttonCount;
		};
	}
}

#endif
