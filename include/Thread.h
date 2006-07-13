#ifndef _THREAD_H_
#define _THREAD_H_

#ifdef WIN32
#include <windows.h>
#endif
#include "Types.h"

namespace Framework
{

	class CThread
	{
	public:
		typedef void*		(*ThreadProc)(void*);

	public:
							CThread(ThreadProc, void*);
							~CThread();
		void				Join();
		uint32				GetThreadID();
		static uint32		GetCurrentThreadID();

	private:
#ifdef WIN32
		HANDLE				m_hThread;
		uint32				m_nThreadID;
#endif

	};

}

#endif
