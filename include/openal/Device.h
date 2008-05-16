#ifndef _OPENAL_DEVICE_H_
#define _OPENAL_DEVICE_H_

#include <alc.h>

namespace OpenAl
{
	class CDevice
	{
	public:
					CDevice(const char* = 0);
		virtual		~CDevice();

					operator ALCdevice*() const;

	private:
		ALCdevice*	m_device;
	};
}

#endif
