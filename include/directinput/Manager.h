#pragma once

#include "DirectInput.h"
#include <memory>
#include <list>
#include <map>
#include <unordered_map>
#include "win32/GuidUtils.h"
#include "win32/ComPtr.h"
#include "Device.h"

namespace Framework
{
	namespace DirectInput
	{
		class CManager
		{
		public:
			typedef std::function<void (const GUID&, uint32, uint32)> InputEventHandler;

									CManager(bool filterXInput = false);
			virtual					~CManager();

			void					SetFocusWindow(HWND);

			uint32					RegisterInputEventHandler(const InputEventHandler&);
			void					UnregisterInputEventHandler(uint32);

			void					CreateKeyboard();
			void					CreateJoysticks();
			bool					GetDeviceInfo(const GUID&, DIDEVICEINSTANCE*);
			bool					GetDeviceObjectInfo(const GUID&, uint32, DIDEVICEOBJECTINSTANCE*);

		private:
			typedef std::shared_ptr<CDevice> DevicePtr;
			typedef std::map<GUID, DevicePtr> DeviceList;
			typedef std::list<GUID> JoystickInstanceList;
			typedef std::unordered_map<uint32, InputEventHandler> InputEventHandlerMap;
			typedef Framework::Win32::CComPtr<IDirectInput8> DirectInputPtr;

			DWORD					UpdateThreadProc();
			static DWORD CALLBACK	UpdateThreadProcStub(void*);

			static bool				IsXInputDevice(const GUID&);
			static BOOL CALLBACK	EnumDevicesCallback(LPCDIDEVICEINSTANCE, LPVOID);
			BOOL					EnumDevicesCallbackImpl(LPCDIDEVICEINSTANCE);

			DirectInputPtr			m_directInput;
			JoystickInstanceList	m_joystickInstances;
			DeviceList				m_devices;

			InputEventHandlerMap	m_inputEventHandlers;
			uint32					m_nextInputEventHandlerId;

			HANDLE					m_updateThreadHandle;
			bool					m_updateThreadOver;
			CRITICAL_SECTION		m_updateMutex;

			bool					m_filterXInput = false;
		};
	}
}
