#include <fstream>
#include <iostream>
#include <Windows.h>

#include "TimerLL.h"
#include "RTAParameters.h"

TimerLL::TimerLL(std::string type)
{
	m_Name = type;

	m_HeadNode = nullptr;
	m_TimingInfo = std::vector<LLTimerInfo*>();
}
TimerLL::~TimerLL(void)
{
	this->DestroyList(m_HeadNode);
}

std::string TimerLL::GetName(void)
{
	return m_Name;
}

void TimerLL::StartTracking(std::string name, int frame)
{
	LLTimerInfo* node = new LLTimerInfo();
	node->pNext = nullptr;
	node->Name = name;
	node->Frame = frame;
	node->StartTime = std::chrono::steady_clock::now();

	if (!m_HeadNode)
	{
		m_HeadNode = node;
		m_TailNode = node;
	}
	else
	{
		m_TailNode->pNext = node;
		m_TailNode = m_TailNode->pNext;
	}
}
void TimerLL::EndTracking(std::string name)
{
	this->EndTrackingNode(m_HeadNode, name);
}

void TimerLL::ExportReport(void)
{
	this->PopulateReport(m_HeadNode);

	std::ofstream ofs(std::string(RTAParameters::ReportPath + "\\Timings\\" + m_Name + "_TimingInfo.csv").c_str(), std::ofstream::out);
	if (ofs.is_open())
	{
		ofs << "ENTRY_NAME\tFRAME\tDURATION" << std::endl;
		for (LLTimerInfo* info : m_TimingInfo)
		{
			ofs << info->Name << "\t" << info->Frame << "\t" << GetExecutionTimeRecursive(m_HeadNode, info->Name) << std::endl;
		}
	}
	else
	{
		std::cout << RTAParameters::ReportPath + "\\Timings\\" + m_Name + "_TimingInfo.csv IO FAILED" << std::endl;
	}
}
double TimerLL::GetExecutionTime(std::string name)
{
	return GetExecutionTimeRecursive(m_HeadNode, name);
}

void TimerLL::EndTrackingNode(LLTimerInfo* pNode, std::string name)
{
	if (pNode->Name != name)
	{
		EndTrackingNode(pNode->pNext, name);
	}
	else
	{
		pNode->EndTime = std::chrono::steady_clock::now();

		std::chrono::duration<double, std::milli> ms = pNode->EndTime - pNode->StartTime;
		pNode->Duration = ms.count();
	}
}
void TimerLL::PopulateReport(LLTimerInfo* pNode)
{
	if (pNode)
	{
		m_TimingInfo.push_back(pNode);
		PopulateReport(pNode->pNext);
	}
}
void TimerLL::DestroyList(LLTimerInfo* pNode)
{
	if (pNode->pNext)
	{
		DestroyList(pNode->pNext);
	}
	delete pNode;
}
double TimerLL::GetExecutionTimeRecursive(LLTimerInfo* pNode, std::string name)
{
	while (pNode != nullptr)
		if (pNode->Name == name)
			return pNode->Duration;
		else
			return GetExecutionTimeRecursive(pNode->pNext, name);

	return 0.0;
}