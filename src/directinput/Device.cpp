#include "directinput/Device.h"

using namespace Framework::DirectInput;

CDevice::CDevice(LPDIRECTINPUTDEVICE8 device) :
m_device(device)
{

}

CDevice::~CDevice()
{
	m_device->Release();
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
