#include "Semaphore.h"

using namespace Framework;

CSemaphore::CSemaphore(unsigned int nCount)
{
#ifdef WIN32
	m_hSemaphore = CreateSemaphore(NULL, nCount, 256, NULL);
#endif
}

CSemaphore::~CSemaphore()
{
#ifdef WIN32
	CloseHandle(m_hSemaphore);
	m_hSemaphore = NULL;
#endif
}

void CSemaphore::Wait()
{
#ifdef WIN32
	WaitForSingleObject(m_hSemaphore, INFINITE);
#endif
}

void CSemaphore::Signal()
{
#ifdef WIN32
	ReleaseSemaphore(m_hSemaphore, 1, NULL);
#endif
}
