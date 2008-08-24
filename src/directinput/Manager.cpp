#include "directinput/Manager.h"
#include "directinput/Keyboard.h"
#include "directinput/Joystick.h"
#include <stdexcept>

using namespace std;
using namespace DirectInput;

CManager::CManager()
{
    if(FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void**>(&m_directInput), NULL)))
    {
        throw runtime_error("Couldn't create DirectInput8");
    }
    m_directInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumDevicesCallback, this, DIEDFL_ATTACHEDONLY);
}

CManager::~CManager()
{
    m_devices.clear();
    if(m_directInput != NULL)
    {
        m_directInput->Release();
    }
}

void CManager::CreateKeyboard(HWND window)
{
    LPDIRECTINPUTDEVICE8 device;
    if(FAILED(m_directInput->CreateDevice(GUID_SysKeyboard, &device, NULL)))
    {
        throw runtime_error("Couldn't create device.");
    }
    m_devices[GUID_SysKeyboard] = DevicePtr(new CKeyboard(device, window));
}

void CManager::CreateJoysticks(HWND window)
{
    for(JoystickInstanceList::const_iterator joystickIterator(m_joystickInstances.begin());
        m_joystickInstances.end() != joystickIterator; joystickIterator++)
    {
        LPDIRECTINPUTDEVICE8 device;
        const GUID& deviceGuid(*joystickIterator);
        if(FAILED(m_directInput->CreateDevice(deviceGuid, &device, NULL)))
        {
            continue;
        }
        m_devices[deviceGuid] = DevicePtr(new CJoystick(device, window));
    }
}

bool CManager::GetDeviceInfo(const GUID& deviceId, DIDEVICEINSTANCE* deviceInfo)
{
    if(!deviceInfo) return false;
    DeviceList::iterator deviceIterator(m_devices.find(deviceId));
    if(deviceIterator == m_devices.end()) return false;
    DevicePtr& device = deviceIterator->second;
    return device->GetInfo(deviceInfo);
}

bool CManager::GetDeviceObjectInfo(const GUID& deviceId, uint32 id, DIDEVICEOBJECTINSTANCE* objectInfo)
{
    if(!objectInfo) return false;
    DeviceList::iterator deviceIterator(m_devices.find(deviceId));
    if(deviceIterator == m_devices.end()) return false;
    DevicePtr& device = deviceIterator->second;
    return device->GetObjectInfo(id, objectInfo);
}

void CManager::ProcessEvents(const CDevice::InputEventHandler& eventHandler)
{
    for(DeviceList::iterator deviceIterator(m_devices.begin());
        deviceIterator != m_devices.end(); deviceIterator++)
    {
        DevicePtr& device = deviceIterator->second;
        device->ProcessEvents(eventHandler);
    }
}

BOOL CALLBACK CManager::EnumDevicesCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
    return static_cast<CManager*>(pvRef)->EnumDevicesCallbackImpl(lpddi);
}

BOOL CManager::EnumDevicesCallbackImpl(LPCDIDEVICEINSTANCE lpddi)
{
    m_joystickInstances.push_back(lpddi->guidInstance);
    return DIENUM_CONTINUE;
}
