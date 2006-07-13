#ifndef _EVENT_H_
#define _EVENT_H_

#include <assert.h>
#include "Semaphore.h"
#include "EventHandler.h"
#include "List.h"

namespace Framework
{
	template <typename Parameter> class CEvent
	{
	public:
		CEvent() :
		m_Mutex(1)
		{
			m_nIsNotifying = false;
		}

		~CEvent()
		{
			m_Mutex.Wait();

			while(m_Handler.Count() != 0)
			{
				delete m_Handler.Pull();
			}

			m_Mutex.Signal();
		}

		void InsertHandler(CEventHandler<Parameter>* pHandler)
		{
			m_Mutex.Wait();

			m_Handler.Insert(pHandler, 0);
			
			m_Mutex.Signal();
		}

		void RemoveHandler(CEventHandler<Parameter>* pHandler)
		{
			CEventHandler<Parameter>* pStoredHandler;
			CList< CEventHandler<Parameter> >::ITERATOR itHandler;
			bool bFound;

			m_Mutex.Wait();

			bFound = false;
			for(itHandler = m_Handler.Begin(); itHandler.HasNext(); itHandler++)
			{
				pStoredHandler = (*itHandler);
				if(pStoredHandler == pHandler)
				{
					m_Handler.RemoveAt(itHandler);
					delete pStoredHandler;
					bFound = true;
					break;
				}
			}

			m_Mutex.Signal();

			if(!bFound)
			{
				assert(0);
			}

		}

		void Notify(Parameter P)
		{
			bool nReleaseMutex;
			CList< CEventHandler<Parameter> >::ITERATOR itHandler;

			//This is for allowing "re-entrant" calls to notify, which shouldn't be harmful
			if(!m_nIsNotifying)
			{
				m_Mutex.Wait();
				m_nIsNotifying = true;
				nReleaseMutex = true;
			}
			else
			{
				nReleaseMutex = false;
			}

			for(itHandler = m_Handler.Begin(); itHandler.HasNext(); itHandler++)
			{
				(*itHandler)->Invoke(P);
			}

			if(nReleaseMutex)
			{
				m_Mutex.Signal();
				m_nIsNotifying = false;
			}
		}

	private:
		CList< CEventHandler<Parameter> >	m_Handler;
		CSemaphore							m_Mutex;
		bool								m_nIsNotifying;
	};
}

#endif
