#include <fstream>
#include <iostream>

#include "RTAParameters.h"
#include "MethodProfiler.h"

MethodInfo*							MethodProfiler::m_HeadNode		= nullptr;
MethodInfo*							MethodProfiler::m_TailNode		= nullptr;
std::vector<MethodInfo*>	MethodProfiler::m_MethodInfo	= std::vector<MethodInfo*>();

void MethodProfiler::StartTracking(std::string& methodName, std::string& entryName, int& frame)
{
	StartTrackingSearch(m_HeadNode, methodName, entryName, frame);
}
void MethodProfiler::StartTrackingSearch(MethodInfo*& pNode, std::string& methodName, std::string& entryName, int& frame)
{
	if (!pNode)
	{
		pNode = new MethodInfo();
		pNode->pNext = nullptr;
		pNode->pPrevious = nullptr;
		pNode->Duration = 0;
		pNode->Frame = frame;
		pNode->TimesCalled = 1;
		pNode->EntryName = entryName;
		pNode->MethodName = methodName; 
		pNode->StartTime = std::chrono::steady_clock::now();
	}
	else
	{
		if (pNode->MethodName == methodName)
		{
			pNode->TimesCalled++;
			pNode->StartTime = std::chrono::steady_clock::now();
		}
		else
		{
			StartTrackingSearch(pNode->pNext, methodName, entryName, frame);
		}
	}
}

void MethodProfiler::EndTracking(std::string& methodName, std::string& entryName)
{
	EndTrackingSearch(m_HeadNode, methodName, entryName);
}
void MethodProfiler::EndTrackingSearch(MethodInfo* pNode, std::string& methodName, std::string& entryName)
{
	if ((pNode->EntryName != entryName) && (pNode->MethodName != methodName))
	{
		EndTrackingSearch(pNode->pNext, methodName, entryName);
	}
	else
	{
		pNode->EndTime = std::chrono::steady_clock::now();

		std::chrono::duration<double, std::milli> ms = pNode->EndTime - pNode->StartTime;
		pNode->Duration += ms.count();
	}
}

void MethodProfiler::ExportReport()
{
	std::cout << "MethodProfiler::ExportReport() :-" << std::endl;

	m_MethodInfo.clear();
	PopulateReport(m_HeadNode);

	std::ofstream ofs(std::string(RTAParameters::ReportPath + "\\MethodCalls\\MethodProfiling.csv"), std::ofstream::out);
	if (ofs.is_open())
	{
		ofs << "METHOD_NAME\tTIMES_CALLED\tTOTAL_TIME_SPENT" << std::endl;
		for (MethodInfo* data : m_MethodInfo)
		{
			ofs << data->MethodName << "\t" << data->TimesCalled << "\t" << data->Duration << std::endl;
			std::cout << data->MethodName << "\t" << data->TimesCalled << "\t" << data->Duration << std::endl;
		}
	}
	else
	{
		std::cout << std::string(RTAParameters::ReportPath + "\\MethodCalls\\MethodProfiling_" + std::to_string(m_HeadNode->Frame) + ".csv").c_str() << " File IO FAILED" << std::endl;
		return;
	}
}
void MethodProfiler::PopulateReport(MethodInfo* pNode)
{
	if (pNode)
	{
		m_MethodInfo.push_back(pNode);
		PopulateReport(pNode->pNext);
	}
}