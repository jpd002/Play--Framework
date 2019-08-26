#pragma once

#include "nodiscard.h"

#include <algorithm>
#include <cassert>
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

		typedef std::shared_ptr<CConnection> Connection;
		typedef std::weak_ptr<CConnection> WeakConnection;
		typedef std::function<T (Args...)> SlotFunction;

		CSignal() = default;

		FRAMEWORK_NODISCARD
		Connection Connect(const SlotFunction& func, bool oneShot = false)
		{
			assert(func);

			std::unique_lock<std::mutex> lock(m_lock);

			auto connection = std::make_shared<CConnection>(func, oneShot);
			m_connections.push_back(connection);

			return connection;
		}

		FRAMEWORK_NODISCARD
		Connection ConnectOnce(const SlotFunction& func)
		{
			return Connect(func, true);
		}

		void Reset()
		{
			std::unique_lock<std::mutex> lock(m_lock);

			m_connections.clear();
		}

		void operator()(Args... args)
		{
			std::unique_lock<std::mutex> lock(m_lock);

			m_connections.erase(
				std::remove_if(
					m_connections.begin(), 
					m_connections.end(),
					[&](WeakConnection& connection)
					{
						auto connectionPtr = connection.lock();
						if(connectionPtr)
						{
							(*connectionPtr)(args...);
						}
						return !connectionPtr || (*connectionPtr).IsOneShot();
					}
				), 
				m_connections.end()
			);
		}

		class CConnection
		{
			public:
				CConnection(const SlotFunction slot, bool oneShot)
				: m_slot(slot)
				, m_oneShot(oneShot)
				{
				}

				void operator()(Args... args)
				{
					(m_slot)(args...);
				}
			
				bool IsOneShot() const
				{
					return m_oneShot;
				}

			private:
				SlotFunction m_slot;
				bool m_oneShot;
		};
	private:
		std::vector<WeakConnection> m_connections;
		std::mutex m_lock;
	};
}
