#include "pch.h"
#include "TimerManager.h"

TimerManager* TimerManager::m_Instance = nullptr;

TimerManager::TimerManager(void)
{
	m_Timers.clear();
}
TimerManager::~TimerManager(void)
{
	for (int i = 0; i < m_Timers.size(); i++)
	{
		if (m_Timers[i]) delete m_Timers[i];
	}
}

TimerManager* TimerManager::Instance(void)
{
	if (!m_Instance)
		m_Instance = new TimerManager();
	return m_Instance;
}

void TimerManager::CreateTimer(const std::string& name)
{
	m_Timers.push_back(new Timer(name));
}
void TimerManager::DestroyTimer(const std::string& name)
{
	for (int i = 0; i < m_Timers.size(); i++)
	{
		if (m_Timers[i]->GetName() == name)
		{
			delete m_Timers[i];
		}
	}
}

Timer* TimerManager::GetTimer(const std::string& name)
{
	for (int i = 0; i < m_Timers.size(); i++)
	{
		if (m_Timers[i]->GetName() == name)
		{
			return m_Timers[i];
		}
	}

	return nullptr;
}

void TimerManager::ExportReport(const std::string& exportPath)
{
	for (int i = 0; i < m_Timers.size(); i++)
	{
		m_Timers[i]->ExportReport(exportPath);
	}
}