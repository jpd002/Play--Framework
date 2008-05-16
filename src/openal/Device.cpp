#include "openal/Device.h"
#include <stdexcept>

using namespace std;
using namespace OpenAl;

CDevice::CDevice(const char* deviceName)
{
	m_device = alcOpenDevice(deviceName);
	if(m_device == NULL)
	{
		throw runtime_error("Couldn't open device.");
	}
}

CDevice::~CDevice()
{
	alcCloseDevice(m_device);
}

CDevice::operator ALCdevice*() const
{
	return m_device;
}
