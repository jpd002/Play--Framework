#ifndef _EVENTEX_H_
#define _EVENTEX_H_

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <list>

namespace Framework
{

	template <typename Parameter> class CEventEx
	{
	public:
		typedef boost::function< void (Parameter) > HandlerType;

		CEventEx()
		{
			m_nIsNotifying = false;
		}

		virtual ~CEventEx()
		{

		}

		void InsertHandler(HandlerType Handler)
		{
			boost::mutex::scoped_lock Lock(m_Mutex);
			m_Handlers.push_back(Handler);
		}

		void RemoveHandler(HandlerType Handler)
		{
			boost::mutex::scoped_lock Lock(m_Mutex);
		}

		void Notify(Parameter P)
		{
			boost::mutex::scoped_lock Lock(m_Mutex);

			HandlerList::iterator itHandler;

			for(HandlerList::iterator itHandler = m_Handlers.begin();
				itHandler != m_Handlers.end();
				itHandler++)
			{
				(*itHandler)(P);
			}
		}

	private:
		typedef std::list<HandlerType>		HandlerList;

		HandlerList							m_Handlers;
		boost::mutex						m_Mutex;
		boost::condition					m_Notifying;
		bool								m_nIsNotifying;
	};

}

#endif
