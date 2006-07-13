#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#ifdef WIN32
#include <windows.h>
#endif

namespace Framework
{

	class CSemaphore
	{
	public:
				CSemaphore(unsigned int);
				~CSemaphore();
		void	Wait();
		void	Signal();

	private:
#ifdef WIN32
		HANDLE	m_hSemaphore;
#endif

	};

}

#endif
