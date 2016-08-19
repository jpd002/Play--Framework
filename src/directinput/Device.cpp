#include "directinput/Device.h"

using namespace Framework::DirectInput;

CDevice::CDevice(const DirectInputDevicePtr& device)
: m_device(device)
{

}

CDevice::~CDevice()
{

}

bool CDevice::GetInfo(DIDEVICEINSTANCE* deviceInfo)
{
	deviceInfo->dwSize = sizeof(DIDEVICEINSTANCE);
	return !FAILED(m_device->GetDeviceInfo(deviceInfo));
}

bool CDevice::GetObjectInfo(uint32 id, DIDEVICEOBJECTINSTANCE* objectInfo)
{
	objectInfo->dwSize = sizeof(DIDEVICEOBJECTINSTANCE);
	return !FAILED(m_device->GetObjectInfo(objectInfo, id, DIPH_BYOFFSET));
}

void CDevice::SetFocusWindow(HWND focusWindow)
{
	//Unacquire device just to be sure
	m_device->Unacquire();

	HRESULT result = m_device->SetCooperativeLevel(focusWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	assert(SUCCEEDED(result));
}
