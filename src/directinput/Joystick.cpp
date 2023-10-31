#include "directinput/Joystick.h"
#include <stdexcept>
#include <assert.h>

#define DIBUFFERSIZE	(0x80)

using namespace Framework::DirectInput;

CJoystick::CJoystick(const DirectInputDevicePtr& device)
: CDevice(device)
, m_buttonCount(0)
{
	HRESULT result = S_OK;

	m_device->EnumObjects(&EnumObjectsCallback, this, DIDFT_ALL);
	if(FAILED(m_device->SetDataFormat(&c_dfDIJoystick)))
	{
		throw std::runtime_error("Couldn't SetDataFormat.");
	}

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

	{
		DIDEVICEINSTANCE deviceInstance;
		deviceInstance.dwSize = sizeof(DIDEVICEINSTANCE);
		result = m_device->GetDeviceInfo(&deviceInstance);
		assert(SUCCEEDED(result));

		m_deviceGuid = deviceInstance.guidInstance;
	}

	CreateVibrationEffects();
}

void CJoystick::CreateVibrationEffects()
{
	DICONSTANTFORCE constantForce;
	DIEFFECT diEffect;
	ZeroMemory(&diEffect, sizeof(diEffect));
	diEffect.dwSize = sizeof(DIEFFECT);
	diEffect.dwFlags = DIEFF_CARTESIAN;
	diEffect.dwDuration = 2000000;
	diEffect.cAxes = 1;
	diEffect.lpEnvelope = 0;
	diEffect.cbTypeSpecificParams = sizeof(DICONSTANTFORCE);
	diEffect.lpvTypeSpecificParams = &constantForce;

	constantForce.lMagnitude = 1000;
	auto res = m_device->CreateEffect(GUID_ConstantForce, &diEffect, &m_pEffectSmall, NULL);
	if(FAILED(res))
	{
		return;
	}

	constantForce.lMagnitude = 3000;
	if(FAILED(m_device->CreateEffect(GUID_ConstantForce, &diEffect, &m_pEffectMedium, NULL)))
	{
		return;
	}

	constantForce.lMagnitude = 5000;
	if(FAILED(m_device->CreateEffect(GUID_ConstantForce, &diEffect, &m_pEffectLarge, NULL)))
	{
		return;
	}
	m_hasVibrationSupport = true;
}

void CJoystick::SetVibration(uint8_t largeMotor, uint8_t smallMotor)
{
	if(!m_hasVibrationSupport)
		return;

	if(smallMotor)
	{
		m_pEffectSmall->Start(1, 0);
	}

	if(largeMotor <= 100)
	{
		m_pEffectMedium->Start(1, 0);
	}
	else
	{
		m_pEffectLarge->Start(1, 0);
	}
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
	return DIENUM_CONTINUE;
}
