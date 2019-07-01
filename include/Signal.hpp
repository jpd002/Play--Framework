#pragma once

#include <algorithm>
#include <mutex>
#include <memory>
#include <vector>
#include <functional>

namespace Framework
{

	template<typename> class CSignal;
	template<typename T, typename... Args>
	class CSignal<T (Args...)>
	{

	public:
		class CConnection;

		typedef std::shared_ptr<CConnection> CConnectionPtr;
		typedef std::weak_ptr<CConnection> CConnectionWeakPtr;
		typedef std::vector<CConnectionPtr> CConnectionListPtr;

		typedef CSignal<T (Args...)> CSignalProto;
		typedef std::function<void()> CConectionFunction;
		typedef std::function<T (Args...)> CSlotFunction;
		typedef std::weak_ptr<const CSlotFunction> CSlotFunctionPtr;

		CSignal() = default;

		CConnectionPtr connect(const CSlotFunction& func, bool oneShot = false)
		{
			if(func)
			{
				std::unique_lock<std::mutex> lock(m_lock);

				CConnectionPtr connection = std::make_shared<CConnection>(func, oneShot);
				m_connections.push_back(connection);

				return connection;
			}

			return nullptr;
		}

		CConnectionPtr connectOnce(const CSlotFunction& func)
		{
			return connect(func, true);
		}

		void operator()(Args... args)
		{
			m_connections.erase(
				std::remove_if(
					m_connections.begin(), 
					m_connections.end(),
					[&](CConnectionWeakPtr& connection)
					{
						auto connectionPtr = connection.lock();
						if(connectionPtr)
							(*connectionPtr)(args...);
						return !connectionPtr || (*connectionPtr).isOneShot() || !(*connectionPtr).isConnected();
					}
				), 
				m_connections.end()
			);
		}

		class CConnection
		{
			public:
				CConnection(const CSlotFunction slot, bool oneShot)
				: m_slot(slot)
				, m_oneShot(oneShot)
				, m_connected(true)
				{
				}

				~CConnection()
				{
				}

				void operator()(Args... args)
				{
					if(m_connected)
					{
						if(m_slot)
							(m_slot)(args...);

						if(m_oneShot)
							m_connected = false;
					}
				}
			
				bool isOneShot()
				{
					return m_oneShot;
				}

				bool isConnected()
				{
					return m_connected;
				}

			private:
				CSlotFunction m_slot;
				bool m_connected;
				bool m_oneShot;
		};
	private:
		std::vector<CConnectionWeakPtr> m_connections;
		std::mutex m_lock;
	};
}