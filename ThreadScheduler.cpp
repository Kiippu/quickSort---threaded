#include "ThreadScheduler.h"


ThreadScheduler::ThreadScheduler()
{
	m_exit = false;
	m_masterThread = std::unique_ptr<std::thread>(new std::thread(std::bind(&ThreadScheduler::process, this)));
}


ThreadScheduler::~ThreadScheduler()
{
	{
		std::lock_guard<std::mutex> lock(queueMutex);
		m_exit = true;
		queuePending.notify_one();
	}
	m_masterThread->join();
}

void ThreadScheduler::addFiber(Fiber task)
{
	std::lock_guard<std::mutex> lock(queueMutex);
	jobQueue.push_back(task);
	queuePending.notify_one();
}

void ThreadScheduler::process()
{
	while (true)
	{
		{
			std::unique_lock<std::mutex> lock(queueMutex);
			queuePending.wait(lock, [&]() { return m_exit || !jobQueue.empty(); });

			if (m_exit)
				return;

			jobQueue.front().run();
			jobQueue.pop_front();
		}
	}
}
