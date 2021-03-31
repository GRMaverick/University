#pragma once

#include <map>
#include <ctime>
#include <vector>
#include <chrono>

class TimerInfo
{
public:
	std::string													Name;
	int																Frame;
	std::chrono::steady_clock::time_point		StartTime;
	std::chrono::steady_clock::time_point		EndTime;
	double														Duration;
};

class Timer
{
public:
	Timer(std::string name);
	~Timer(void);

	void StartTracking(std::string name, int iteration);
	void EndTracking(std::string name);

	void ExportReport(void);
	double GetExecutionTime(std::string name);

	std::string GetName(void);

private:
	std::string											m_Name;
	std::map<std::string, TimerInfo>		m_TimerInformation;
};