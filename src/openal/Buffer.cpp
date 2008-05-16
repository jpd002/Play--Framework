#include "openal/Buffer.h"
#include <stdexcept>

using namespace OpenAl;
using namespace std;

CBuffer::CBuffer()
{
	alGenBuffers(1, &m_name);
	if(alGetError())
	{
		throw runtime_error("Couldn't create buffer.");
	}
}

CBuffer::~CBuffer()
{
	alDeleteBuffers(1, &m_name);
}

CBuffer::operator ALuint() const
{
	return m_name;
}
