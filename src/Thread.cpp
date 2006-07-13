#include "Thread.h"

using namespace Framework;

CThread::CThread(ThreadProc pThreadProc, void* pParam)
{
#ifdef WIN32
	m_hThread = CreateThread(NULL, NULL, (PTHREAD_START_ROUTINE)pThreadProc, pParam, NULL, &m_nThreadID);
#endif
}

CThread::~CThread()
{

}

void CThread::Join()
{
#ifdef WIN32
	WaitForSingleObject(m_hThread, INFINITE);
#endif
}

uint32 CThread::GetThreadID()
{
#ifdef WIN32
	return m_nThreadID;
#endif
}

uint32 CThread::GetCurrentThreadID()
{
#ifdef WIN32
	return GetCurrentThreadId();
#endif
}
