#pragma once
#include <string>
#include <vector>

#include "Timer.h"

class TimerManager
{
public:
	~TimerManager(void);
	static TimerManager* Instance(void);

	void CreateTimer(const std::string& name);
	void DestroyTimer(const std::string& name);

	Timer* GetTimer(const std::string& name);

	void ExportReport(const std::string& exportPath);

private:
	static TimerManager* m_Instance;
	TimerManager(void);

	std::vector<Timer*> m_Timers;
};