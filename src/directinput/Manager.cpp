#include "directinput/Manager.h"
#include "directinput/Keyboard.h"
#include "directinput/Joystick.h"
#include <stdexcept>
#include <wbemidl.h>

using namespace Framework::DirectInput;

CManager::CManager(bool filterXInput)
: m_updateThreadHandle(NULL)
, m_updateThreadOver(false)
, m_nextInputEventHandlerId(1)
, m_filterXInput(filterXInput)
{
	if(FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void**>(&m_directInput), NULL)))
	{
		throw std::runtime_error("Couldn't create DirectInput8");
	}
	m_directInput->EnumDevices(DI8DEVCLASS_GAMECTRL, &CManager::EnumDevicesCallback, this, DIEDFL_ATTACHEDONLY);
	{
		DWORD threadId = 0;
		InitializeCriticalSection(&m_updateMutex);
		m_updateThreadHandle = CreateThread(NULL, NULL, &CManager::UpdateThreadProcStub, this, NULL, &threadId);
	}
}

CManager::~CManager()
{
	m_updateThreadOver = true;
	WaitForSingleObject(m_updateThreadHandle, INFINITE);
	DeleteCriticalSection(&m_updateMutex);
}

void CManager::SetFocusWindow(HWND focusWindow)
{
	EnterCriticalSection(&m_updateMutex);
	{
		for(const auto& devicePair : m_devices)
		{
			devicePair.second->SetFocusWindow(focusWindow);
		}
	}
	LeaveCriticalSection(&m_updateMutex);
}

uint32 CManager::RegisterInputEventHandler(const InputEventHandler& inputEventHandler)
{
	uint32 eventHandlerId = m_nextInputEventHandlerId++;
	EnterCriticalSection(&m_updateMutex);
	{
		m_inputEventHandlers[eventHandlerId] = inputEventHandler;
	}
	LeaveCriticalSection(&m_updateMutex);
	return eventHandlerId;
}

void CManager::UnregisterInputEventHandler(uint32 eventHandlerId)
{
	EnterCriticalSection(&m_updateMutex);
	{
		auto inputEventHandlerIterator = m_inputEventHandlers.find(eventHandlerId);
		assert(inputEventHandlerIterator != std::end(m_inputEventHandlers));
		m_inputEventHandlers.erase(inputEventHandlerIterator);
	}
	LeaveCriticalSection(&m_updateMutex);
}

void CManager::CreateKeyboard()
{
	CDevice::DirectInputDevicePtr device;
	if(FAILED(m_directInput->CreateDevice(GUID_SysKeyboard, &device, NULL)))
	{
		throw std::runtime_error("Couldn't create device.");
	}
	EnterCriticalSection(&m_updateMutex);
	{
		m_devices[GUID_SysKeyboard] = std::make_shared<CKeyboard>(device);
	}
	LeaveCriticalSection(&m_updateMutex);
}

void CManager::CreateJoysticks()
{
	for(const auto& joystickInstance : m_joystickInstances)
	{
		CDevice::DirectInputDevicePtr device;
		if(FAILED(m_directInput->CreateDevice(joystickInstance, &device, NULL)))
		{
			continue;
		}
		EnterCriticalSection(&m_updateMutex);
		{
			m_devices[joystickInstance] = std::make_shared<CJoystick>(device);
		}
		LeaveCriticalSection(&m_updateMutex);
	}
}

bool CManager::GetDeviceInfo(const GUID& deviceId, DIDEVICEINSTANCE* deviceInfo)
{
	if(!deviceInfo) return false;
	auto deviceIterator(m_devices.find(deviceId));
	if(deviceIterator == std::end(m_devices)) return false;
	auto& device = deviceIterator->second;
	return device->GetInfo(deviceInfo);
}

bool CManager::GetDeviceObjectInfo(const GUID& deviceId, uint32 id, DIDEVICEOBJECTINSTANCE* objectInfo)
{
	if(!objectInfo) return false;
	auto deviceIterator(m_devices.find(deviceId));
	if(deviceIterator == std::end(m_devices)) return false;
	auto& device = deviceIterator->second;
	return device->GetObjectInfo(id, objectInfo);
}

//Based on code available here: https://docs.microsoft.com/en-us/windows/desktop/xinput/xinput-and-directinput
bool CManager::IsXInputDevice(const GUID& productId)
{
	HRESULT result = S_OK;

	Framework::Win32::CComPtr<IWbemLocator> wbemLocator;
	result = CoCreateInstance(__uuidof(WbemLocator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IWbemLocator), reinterpret_cast<void**>(&wbemLocator));
	assert(SUCCEEDED(result));

	if(FAILED(result) || wbemLocator.IsEmpty())
	{
		return false;
	}

	Framework::Win32::CComPtr<IWbemServices> wbemServices;

	{
		BSTR bstrNamespace = SysAllocString(L"\\\\.\\root\\cimv2");

		result = wbemLocator->ConnectServer(bstrNamespace, NULL, NULL, 0L, 0L, NULL, NULL, reinterpret_cast<IWbemServices**>(&wbemServices));
		assert(SUCCEEDED(result));
		SysFreeString(bstrNamespace);
	
		if(FAILED(result) || wbemServices.IsEmpty())
		{
			return false;
		}
	}

	//Switch security level to IMPERSONATE.
	result = CoSetProxyBlanket(wbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	assert(SUCCEEDED(result));

	Framework::Win32::CComPtr<IEnumWbemClassObject> enumDevices;

	{
		BSTR bstrClassName = SysAllocString(L"Win32_PNPEntity");

		result = wbemServices->CreateInstanceEnum(bstrClassName, 0, NULL, reinterpret_cast<IEnumWbemClassObject**>(&enumDevices));
		assert(SUCCEEDED(result));
		SysFreeString(bstrClassName);

		if(FAILED(result) || enumDevices.IsEmpty())
		{
			return false;
		}
	}

	BSTR bstrDeviceID  = SysAllocString(L"DeviceID");
	bool isXInputDevice = false;

	// Loop over all devices
	while(!isXInputDevice)
	{
		static const unsigned int devicesPerIter = 20;
		IWbemClassObject* devices[devicesPerIter];
		ULONG returned = 0;

		result = enumDevices->Next(10000, 20, reinterpret_cast<IWbemClassObject**>(&devices), &returned);
		assert(SUCCEEDED(result));

		if(FAILED(result))
		{
			break;
		}

		if(returned == 0) break;

		for(uint32 deviceIndex = 0; deviceIndex < returned; deviceIndex++)
		{
			// For each device, get its device ID
			auto device = devices[deviceIndex];
			VARIANT deviceId;
			result = device->Get(bstrDeviceID, 0L, &deviceId, NULL, NULL);
			if(SUCCEEDED(result) && (deviceId.vt == VT_BSTR) && (deviceId.bstrVal != NULL))
			{
				// Check if the device ID contains "IG_".  If it does, then it's an XInput device
				// This information can not be found from DirectInput 
				if(wcsstr(deviceId.bstrVal, L"IG_"))
				{
					// If it does, then get the VID/PID from var.bstrVal
					DWORD vid = 0;
					{
						auto vidString = wcsstr(deviceId.bstrVal, L"VID_");
						if(vidString && swscanf(vidString, L"VID_%4X", &vid) != 1)
						{
							vid = 0;
						}
					}

					DWORD pid = 0;
					{
						auto pidString = wcsstr(deviceId.bstrVal, L"PID_");
						if(pidString && swscanf(pidString, L"PID_%4X", &pid) != 1)
						{
							pid = 0;
						}
					}

					// Compare the VID/PID to the DInput device
					DWORD vidpid = MAKELONG(vid, pid);
					if(vidpid == productId.Data1)
					{
						isXInputDevice = true;
						break;
					}
				}
			}
			device->Release();
		}
	}

	SysFreeString(bstrDeviceID);

	return isXInputDevice;
}

BOOL CALLBACK CManager::EnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	return static_cast<CManager*>(pvRef)->EnumDevicesCallbackImpl(lpddi);
}

BOOL CManager::EnumDevicesCallbackImpl(LPCDIDEVICEINSTANCE lpddi)
{
	if(m_filterXInput && IsXInputDevice(lpddi->guidProduct))
	{
		return DIENUM_CONTINUE;
	}
	m_joystickInstances.push_back(lpddi->guidInstance);
	return DIENUM_CONTINUE;
}

DWORD CManager::UpdateThreadProc()
{
	auto inputEventHandler = 
		[this] (const GUID& device, uint32 id, uint32 value)
		{
			for(const auto& inputEventHandler : m_inputEventHandlers)
			{
				inputEventHandler.second(device, id, value);
			}
		};

	while(!m_updateThreadOver)
	{
		EnterCriticalSection(&m_updateMutex);
		{
			for(const auto& devicePair : m_devices)
			{
				auto& device = devicePair.second;
				device->ProcessEvents(inputEventHandler);
			}
		}
		LeaveCriticalSection(&m_updateMutex);
		Sleep(16);
	}
	return 0;
}

DWORD WINAPI CManager::UpdateThreadProcStub(void* param)
{
	return reinterpret_cast<CManager*>(param)->UpdateThreadProc();
}
