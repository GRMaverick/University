#pragma once

#include <string>
#include <chrono>
#include <vector>

class MethodInfo
{
public:
	int																			Frame;
	int																			TimesCalled;
	double																	Duration;
	std::string																EntryName;
	std::string																MethodName;

	std::chrono::steady_clock::time_point					StartTime;
	std::chrono::steady_clock::time_point					EndTime;

	MethodInfo*															pNext;
	MethodInfo*															pPrevious;
};

class MethodProfiler
{
public:
	static void StartTracking(std::string& methodName, std::string& entryName, int& frame);
	static void EndTracking(std::string& methodName, std::string& entryName);
	static void ExportReport();

private:
	static MethodInfo* m_HeadNode;
	static MethodInfo* m_TailNode;
	static std::vector<MethodInfo*> m_MethodInfo;

	static void StartTrackingSearch(MethodInfo*& pNode, std::string& methodName, std::string& entryName, int& frame);
	static void EndTrackingSearch(MethodInfo* pNode, std::string& methodName, std::string& entryName);
	static void PopulateReport(MethodInfo* pNode);
};