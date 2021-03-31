#include "pch.h"
#include <fstream>
#include <iostream>
#include <Windows.h>

#include "Timer.h"

Timer::Timer(std::string name)
{
	m_Name = name;
}
Timer::~Timer(void)
{

}

void Timer::StartTracking(const std::string& name, const int& iteration)
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
		m_TimerInformation[name].Name = name;
		m_TimerInformation[name].Frame = iteration;
		m_TimerInformation[name].StartTime = std::chrono::steady_clock::now();
	}
}
void Timer::EndTracking(const std::string& name)
{
	auto finder = m_TimerInformation.find(name);
	if (finder == m_TimerInformation.end())
	{
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
			m_TimerInformation[name].EndTime = std::chrono::steady_clock::now();
		}

		std::chrono::duration<double, std::milli> ms = m_TimerInformation[name].EndTime - m_TimerInformation[name].StartTime;
		m_TimerInformation[name].Duration = ms.count();
	}
}

void Timer::ExportReport(const std::string& exportPath)
{
	Platform::String^ localFolder = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	
	std::wstring folderNameW(localFolder->Begin());
	std::string folderNameA(folderNameW.begin(), folderNameW.end());

	const char* charStr = folderNameA.c_str();
	char filename[512];
	sprintf_s(filename, "%s\\%s\\%s", charStr, exportPath.c_str(), std::string(m_Name + "_TimingInfo.csv").c_str());
	
	std::ofstream ofs;
	ofs.open(filename, std::ofstream::out);
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
		std::cout << filename << ": File IO FAILED!" << std::endl;
		return;
	}
}

double Timer::GetExecutionTime(const std::string& name)
{
	return m_TimerInformation[name].Duration;
}
std::string Timer::GetName(void)
{
	return m_Name;
}