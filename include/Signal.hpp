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

		typedef std::shared_ptr<CConnection> CConnectionPtr;
		typedef std::weak_ptr<CConnection> CConnectionWeakPtr;
		typedef std::vector<CConnectionPtr> CConnectionListPtr;

		typedef CSignal<T (Args...)> CSignalProto;
		typedef std::function<void()> CConectionFunction;
		typedef std::function<T (Args...)> CSlotFunction;
		typedef std::weak_ptr<const CSlotFunction> CSlotFunctionPtr;

		CSignal() = default;

		FRAMEWORK_NODISCARD
		CConnectionPtr Connect(const CSlotFunction& func, bool oneShot = false)
		{
			assert(func);

			std::unique_lock<std::mutex> lock(m_lock);

			CConnectionPtr connection = std::make_shared<CConnection>(func, oneShot);
			m_connections.push_back(connection);

			return connection;
		}

		FRAMEWORK_NODISCARD
		CConnectionPtr ConnectOnce(const CSlotFunction& func)
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
					[&](CConnectionWeakPtr& connection)
					{
						auto connectionPtr = connection.lock();
						if(connectionPtr)
							(*connectionPtr)(args...);
						return !connectionPtr || (*connectionPtr).IsOneShot();
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
				CSlotFunction m_slot;
				bool m_oneShot;
		};
	private:
		std::vector<CConnectionWeakPtr> m_connections;
		std::mutex m_lock;
	};
}
