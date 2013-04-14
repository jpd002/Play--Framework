#include "ThreadPool.h"

using namespace Framework;

CThreadPool::CThreadPool(unsigned int threadCount)
: m_stop(false)
{
	for(unsigned int i = 0; i < threadCount; i++)
	{
		m_workers.push_back(std::thread([&] () { WorkerThreadProc(); }));
	}
}

CThreadPool::~CThreadPool()
{
	m_stop = true;
	m_condition.notify_all();

	for(auto& worker : m_workers)
	{
		worker.join();
	}
}

void CThreadPool::Enqueue(const TaskFunction& task)
{
	{
		std::unique_lock<std::mutex> lock(m_tasksMutex);
		m_tasks.push_back(task);
	}

	m_condition.notify_one();
}

void CThreadPool::WorkerThreadProc()
{
	while(1)
	{
		TaskFunction task;

		{
			std::unique_lock<std::mutex> lock(m_tasksMutex);

			while(!m_stop && m_tasks.empty())
			{
				m_condition.wait(lock);
			}

			if(m_stop && m_tasks.empty())
			{
				return;
			}

			task = m_tasks.front();
			m_tasks.pop_front();
		}

		task();
	}
}
