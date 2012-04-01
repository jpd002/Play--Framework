#ifndef _DIRECTINPUTMANAGER_H_
#define _DIRECTINPUTMANAGER_H_

#include "DirectInput.h"
#include <memory>
#include <list>
#include <map>
#include "win32/GuidUtils.h"
#include "Device.h"

namespace Framework
{
	namespace DirectInput
	{
		class CManager
		{
		public:
									CManager();
			virtual					~CManager();

			void					CreateKeyboard(HWND);
			void					CreateJoysticks(HWND);
			void					ProcessEvents(const CDevice::InputEventHandler&);
			bool					GetDeviceInfo(const GUID&, DIDEVICEINSTANCE*);
			bool					GetDeviceObjectInfo(const GUID&, uint32, DIDEVICEOBJECTINSTANCE*);

		private:
			typedef std::shared_ptr<CDevice> DevicePtr;
			typedef std::map<GUID, DevicePtr> DeviceList;
			typedef std::list<GUID> JoystickInstanceList;

			static BOOL CALLBACK	EnumDevicesCallback(LPCDIDEVICEINSTANCE, LPVOID);
			BOOL					EnumDevicesCallbackImpl(LPCDIDEVICEINSTANCE);

			LPDIRECTINPUT8			m_directInput;
			JoystickInstanceList	m_joystickInstances;
			DeviceList				m_devices;
		};
	}
}

#endif
