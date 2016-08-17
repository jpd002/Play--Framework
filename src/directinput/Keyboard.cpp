#include "directinput/Keyboard.h"
#include <assert.h>

#define DIBUFFERSIZE	(0x80)

using namespace Framework::DirectInput;

CKeyboard::CKeyboard(const DirectInputDevicePtr& device, HWND window)
: CDevice(device)
{
	HRESULT result = S_OK;

	result = m_device->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));

	result = m_device->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	assert(SUCCEEDED(result));

	{
		DIPROPDWORD p;
		memset(&p, 0, sizeof(DIPROPDWORD));
		p.diph.dwSize		= sizeof(DIPROPDWORD);
		p.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		p.diph.dwHow		= DIPH_DEVICE;
		p.diph.dwObj		= 0;
		p.dwData			= DIBUFFERSIZE;

		result = m_device->SetProperty(DIPROP_BUFFERSIZE, &p.diph);
		assert(SUCCEEDED(result));
	}

	m_device->Acquire();
}

CKeyboard::~CKeyboard()
{

}

void CKeyboard::ProcessEvents(const InputEventHandler& eventHandler)
{
	DIDEVICEOBJECTDATA deviceData[DIBUFFERSIZE];
	DWORD elementCount = DIBUFFERSIZE;
	HRESULT result = m_device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), deviceData, &elementCount, 0);
	assert(result != DI_BUFFEROVERFLOW);
	if(FAILED(result))
	{
		m_device->Acquire();
		return;
	}
	for(DWORD i = 0; i < elementCount; i++)
	{
		eventHandler(GUID_SysKeyboard, deviceData[i].dwOfs, deviceData[i].dwData);
	}
}
