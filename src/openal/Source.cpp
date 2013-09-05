#include "openal/Source.h"
#include <stdexcept>

using namespace OpenAl;

CSource::CSource()
{
	alGenSources(1, &m_name);
	ALuint errorCode = alGetError();
	if(errorCode != AL_NO_ERROR)
	{
		throw std::runtime_error("Couldn't create source.");
	}
}

CSource::~CSource()
{
	alDeleteSources(1, &m_name);
}

CSource::operator ALuint() const
{
	return m_name;
}

ALint CSource::GetState()
{
	ALint sourceState = AL_INITIAL;
	alGetSourcei(m_name, AL_SOURCE_STATE, &sourceState);
	return sourceState;
}

void CSource::Play()
{
	alSourcePlay(m_name);
}

void CSource::Stop()
{
	alSourceStop(m_name);
}

void CSource::QueueBuffer(ALuint bufferName)
{
	alSourceQueueBuffers(m_name, 1, &bufferName);
}

int CSource::GetBuffersProcessed() const
{
	ALint bufferCount;
	alGetSourcei(m_name, AL_BUFFERS_PROCESSED, &bufferCount);
	return bufferCount;
}
