#pragma once
#include <chrono>
#include <string>
#include <map>
#include <vector>
#include <iostream>

/// typedefs for easy type creation
using TIME_REGISTER = std::map <std::string, std::chrono::time_point<std::chrono::steady_clock>>;
using TIME_VECTOR_PAIR = std::pair<std::string, long long>;
using TIME_VECTOR = std::vector<TIME_VECTOR_PAIR>;

TIME_REGISTER m_beginTimerList;
TIME_REGISTER m_finishTimerList;
TIME_VECTOR m_finalTimerSheetMs;

// log start timer
void addStartTime(std::string displayName)
{
	auto startTimer = std::chrono::high_resolution_clock::now();
	m_beginTimerList.insert(std::make_pair(displayName, startTimer));
	m_finalTimerSheetMs.push_back(TIME_VECTOR_PAIR(displayName, 0));
};
// lof finish timer
void addFinishTime(std::string id)
{
	//log finish timer
	auto finishTimer = std::chrono::high_resolution_clock::now();
	m_finishTimerList.insert(std::make_pair(id, finishTimer));
};
// print time sheet of finihsed timers
void printFinalTimeSheet()
{
	// iterate through all values in timesheet and print them.
	for (auto obj : m_finalTimerSheetMs)
	{
		auto differenceInTime = m_finishTimerList[obj.first] - m_beginTimerList[obj.first];
		obj.second = std::chrono::duration_cast<std::chrono::milliseconds>(differenceInTime).count();
		std::cout << obj.first << " : " << std::to_string(obj.second) << "ms to execute\n" << std::endl;
	}
}
