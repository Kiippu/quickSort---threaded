#pragma once
#include <functional>

using TASK = std::function<void()>;
class Fiber
{
public:
	Fiber(std::function<void()> task) 
		: m_task(task){};

	~Fiber() {};

	void run() {
		m_task();
	}

private:
	TASK m_task;
};

