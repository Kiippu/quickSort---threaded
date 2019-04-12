#pragma once
#include <thread>
#include <memory>
#include <functional>
#include "Fiber.h"
#include <condition_variable>
#include <mutex>
#include <list>
#include <atomic>

class ThreadScheduler
{
public:
	ThreadScheduler();
	~ThreadScheduler();

	//ThreadScheduler(const ThreadScheduler& temp) = delete;
	//ThreadScheduler& operator=(const ThreadScheduler& temp) = delete;

public:

	void addFiber(Fiber job);

private:
	void process();

private:
	std::unique_ptr<std::thread>    m_masterThread;
	std::condition_variable         queuePending;
	std::mutex                      queueMutex;
	std::list<Fiber>                jobQueue;
	std::atomic<bool>               m_exit;

};

