#include "openal/Context.h"
#include <stdexcept>

using namespace OpenAl;
using namespace std;

CContext::CContext(ALCdevice* device, ALCint* attrList, bool makeCurrent)
{
	m_context = alcCreateContext(device, attrList);
	if(m_context == NULL)
	{
		throw runtime_error("Couldn't create context.");
	}
	if(makeCurrent)
	{
		MakeCurrent();
	}
}

CContext::~CContext()
{
	alcDestroyContext(m_context);
}

void CContext::MakeCurrent()
{
	alcMakeContextCurrent(m_context);
}
