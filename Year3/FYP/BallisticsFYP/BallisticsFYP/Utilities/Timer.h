#pragma once

#pragma once

#include <map>
#include <ctime>
#include <vector>
#include <chrono>

class TimerInfo
{
public:
	std::string													Name;
	int															Frame;
	std::chrono::steady_clock::time_point		StartTime;
	std::chrono::steady_clock::time_point		EndTime;
	double														Duration;
};

class Timer
{
public:
	Timer(std::string name);
	~Timer(void);

	void StartTracking(const std::string& name, const int& iteration);
	void EndTracking(const std::string& name);

	void ExportReport(const std::string& exportPath);
	double GetExecutionTime(const std::string& name);

	std::string GetName(void);

private:
	std::string											m_Name;
	std::map<std::string, TimerInfo>		m_TimerInformation;
};