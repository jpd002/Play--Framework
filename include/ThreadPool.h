#pragma once

#include <functional>
#include <thread>
#include <vector>
#include <deque>
#include <mutex>
#include <condition_variable>

namespace Framework
{
	class CThreadPool
	{
	public:
		typedef std::function<void ()> TaskFunction;

									CThreadPool(unsigned int);
		virtual						~CThreadPool();

		void						Enqueue(const TaskFunction&);

	private:
		typedef std::vector<std::thread> ThreadArray;
		typedef std::deque<TaskFunction> TaskArray;

		void						WorkerThreadProc();

		TaskArray					m_tasks;
		std::mutex					m_tasksMutex;

		std::condition_variable		m_condition;
		ThreadArray					m_workers;
		bool						m_stop;
	};
}
