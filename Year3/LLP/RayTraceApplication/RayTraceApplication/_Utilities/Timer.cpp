#include <fstream>
#include <iostream>
#include <Windows.h>

#include "Timer.h"
#include "RTAParameters.h"

Timer::Timer(std::string name)
{
	m_Name = name;
}
Timer::~Timer(void)
{

}

void Timer::StartTracking(std::string name, int iteration)
{
	auto finder = m_TimerInformation.find(name);
	if (finder == m_TimerInformation.end())
	{
		TimerInfo info = TimerInfo();
		info.Name = name;
		info.Frame = iteration;
		info.StartTime = std::chrono::steady_clock::now();

		m_TimerInformation[name] = info;
	}
	else
	{
		#ifdef _DEBUG
				std::cout << "Tracking for ID: " << name.c_str() << " already in progress - Resetting tracking!" << std::endl;
		#endif

		m_TimerInformation[name].Name = name;
		m_TimerInformation[name].Frame = iteration;
		m_TimerInformation[name].StartTime = std::chrono::steady_clock::now();
	}
}
void Timer::EndTracking(std::string name)
{
	auto finder = m_TimerInformation.find(name);
	if (finder == m_TimerInformation.end())
	{
		#ifdef _DEBUG
				std::cout << "No tracking for ID: " << name.c_str() << " in progress - Beginning Tracking!" << std::endl;
		#endif
		m_TimerInformation[name].StartTime = std::chrono::steady_clock::now();
	}
	else
	{
		auto finder = m_TimerInformation.find(name);
		if (finder == m_TimerInformation.end())
		{
			m_TimerInformation[name].EndTime = std::chrono::steady_clock::now();
		}
		else
		{
			#ifdef _DEBUG
						std::cout << "Tracking completed for ID: " << name.c_str() << " - Overwriting last entry!" << std::endl;
			#endif
			m_TimerInformation[name].EndTime = std::chrono::steady_clock::now();
		}

		std::chrono::duration<double, std::milli> ms = m_TimerInformation[name].EndTime - m_TimerInformation[name].StartTime;
		m_TimerInformation[name].Duration = ms.count();
	}
}

void Timer::ExportReport(void)
{
	std::ofstream ofs(std::string(RTAParameters::ReportPath + "Timings\\" + m_Name + "_TimingInfo.csv").c_str(), std::ofstream::out);
	if (ofs.is_open())
	{
		ofs << "NAME\tFRAME\tDURATION" << std::endl;
		for (auto it = m_TimerInformation.begin(); it != m_TimerInformation.end(); it++)
		{
			ofs << it->first.c_str() << "\t" << it->second.Frame << "\t" << it->second.Duration << std::endl;
		}
		ofs.close();
	}
	else
	{
		std::cout << std::string(RTAParameters::ReportPath + "Timings\\" + m_Name + "_TimingInfo.csv").c_str() << ": File IO FAILED!" << std::endl;
		return;
	}
}

double Timer::GetExecutionTime(std::string name)
{
	return m_TimerInformation[name].Duration;
}
std::string Timer::GetName(void)
{
	return m_Name;
}