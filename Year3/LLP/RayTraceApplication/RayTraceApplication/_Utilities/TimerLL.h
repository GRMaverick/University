#pragma once

#include <map>
#include <ctime>
#include <vector>
#include <chrono>

class LLTimerInfo
{
public:
	std::string																Name;
	int																			Frame;
	double																	Duration;
	std::chrono::steady_clock::time_point					StartTime;
	std::chrono::steady_clock::time_point					EndTime;
	LLTimerInfo*															pNext;
	LLTimerInfo*															pPrevious;
};

class TimerLL
{
public:
	TimerLL(std::string type);
	~TimerLL(void);

	std::string GetName(void);

	void StartTracking(std::string name, int frame);
	void EndTracking(std::string name);
	double GetExecutionTime(std::string name);

	void ExportReport(void);
	
private:
	void DestroyList(LLTimerInfo* pNode);
	void EndTrackingNode(LLTimerInfo* pNode, std::string name);
	void PopulateReport(LLTimerInfo* pNode);
	double GetExecutionTimeRecursive(LLTimerInfo* pNode, std::string name);

	LLTimerInfo*									m_HeadNode;
	LLTimerInfo*									m_TailNode;

	std::string										m_Name;
	std::vector<LLTimerInfo*>				m_TimingInfo;
};