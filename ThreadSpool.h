#pragma once
#include <memory>
#include <map>
#include "ThreadScheduler.h"

enum THREAD_ID {
	ID0,
	ID1,
	ID2,
	ID3,
	ID4,
	ID5,
	ID6,
	ID7,
	ID_MAX
};

class ThreadSpool
{
public:

	static ThreadSpool&getInstance()
	{
		static ThreadSpool instance;
		return instance;
	}
	ThreadSpool(ThreadSpool&temp) = delete;
	void operator=(ThreadSpool const&temp) = delete;

	size_t count() { return m_threadPool.size(); };

	unsigned isAvaliable();

	ThreadScheduler * getAvaliable();

	ThreadScheduler * get(THREAD_ID);

private:
	ThreadSpool();

	unsigned m_maxThreadsSupported;
	std::map<THREAD_ID,std::unique_ptr<ThreadScheduler>> m_threadPool;
};

