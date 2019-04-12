#include "ThreadSpool.h"
#include "pthread.h"
#include "sched.h"
#include "semaphore.h"
#include <iostream>



ThreadScheduler * ThreadSpool::get(THREAD_ID id)
{
	auto iter = m_threadPool.end();
	iter = m_threadPool.find(id);
	if (iter == m_threadPool.end())
	{
		return iter->second.get();
	}
	return nullptr;
}

ThreadSpool::ThreadSpool()
{
	m_maxThreadsSupported = std::thread::hardware_concurrency();
	for (unsigned i = 0; i < m_maxThreadsSupported; i++)
	{
		if (i == THREAD_ID::ID_MAX)
			break;
		m_threadPool.insert(std::make_pair(THREAD_ID(i),std::unique_ptr<ThreadScheduler>()));
	}
}


ThreadSpool::~ThreadSpool()
{
}
