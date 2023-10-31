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
			virtual					~CJoystick() = default;

			int						GetButtonCount() const;
			void					ProcessEvents(const InputEventHandler&) override;
			void					SetVibration(uint8_t largeMotor, uint8_t smallMotor);

		private:
			static BOOL CALLBACK	EnumObjectsCallback(LPCDIDEVICEOBJECTINSTANCE, LPVOID);
			BOOL					EnumObjectsCallbackImpl(LPCDIDEVICEOBJECTINSTANCE);
			void					CreateVibrationEffects();

			GUID					m_deviceGuid;
			int						m_buttonCount;
			bool					m_hasVibrationSupport = false;

			using DirectInputEffectPtr = Framework::Win32::CComPtr<IDirectInputEffect>;
			DirectInputEffectPtr m_pEffectSmall;
			DirectInputEffectPtr m_pEffectMedium;
			DirectInputEffectPtr m_pEffectLarge;
		};
	}
}
