#include "directinput/Joystick.h"
#include <stdexcept>

#define DIBUFFERSIZE    (10)

using namespace DirectInput;
using namespace std;

CJoystick::CJoystick(LPDIRECTINPUTDEVICE8 device, HWND ownerWindow) :
CDevice(device),
m_buttonCount(0)
{
    m_device->EnumObjects(&EnumObjectsCallback, this, DIDFT_ALL);
    if(FAILED(m_device->SetDataFormat(&c_dfDIJoystick)))
    {
        throw runtime_error("Couldn't SetDataFormat.");
    }
    if(FAILED(m_device->SetCooperativeLevel(ownerWindow, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
    {
        throw runtime_error("Couldn't SetCooperativeLevel.");
    }

    {
	    DIPROPDWORD p;
	    memset(&p, 0, sizeof(DIPROPDWORD));
	    p.diph.dwSize		= sizeof(DIPROPDWORD);
	    p.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	    p.diph.dwHow		= DIPH_DEVICE;
	    p.diph.dwObj		= 0;
	    p.dwData			= DIBUFFERSIZE;

	    m_device->SetProperty(DIPROP_BUFFERSIZE, &p.diph);
    }

	m_device->Acquire();

    {
        DIDEVICEINSTANCE deviceInstance;
        deviceInstance.dwSize = sizeof(DIDEVICEINSTANCE);
        m_device->GetDeviceInfo(&deviceInstance);
        m_deviceGuid = deviceInstance.guidInstance;
    }
}

CJoystick::~CJoystick()
{

}

void CJoystick::ProcessEvents(const InputEventHandler& eventHandler)
{
	DIDEVICEOBJECTDATA deviceData[DIBUFFERSIZE];
    DWORD elementCount = DIBUFFERSIZE;
	HRESULT result = m_device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), deviceData, &elementCount, 0);
	if(FAILED(result))
	{
		m_device->Acquire();
		return;
	}
    for(DWORD i = 0; i < elementCount; i++)
    {
        eventHandler(m_deviceGuid, deviceData[i].dwOfs, deviceData[i].dwData);
    }
}

int CJoystick::GetButtonCount() const
{
    return m_buttonCount;
}

BOOL CALLBACK CJoystick::EnumObjectsCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
    return reinterpret_cast<CJoystick*>(pvRef)->EnumObjectsCallbackImpl(lpddoi);
}

BOOL CJoystick::EnumObjectsCallbackImpl(LPCDIDEVICEOBJECTINSTANCE lpddoi)
{
    if(lpddoi->guidType == GUID_Button)
    {
        m_buttonCount++;
    }
    if(lpddoi->guidType == GUID_XAxis)
    {
        int i = 0;
        i++;
    }
    if(lpddoi->guidType == GUID_YAxis)
    {
        int i = 0;
        i++;
    }
    return DIENUM_CONTINUE;
}
