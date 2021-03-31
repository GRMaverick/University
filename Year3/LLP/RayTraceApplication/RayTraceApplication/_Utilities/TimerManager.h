#pragma once
#include <string>
#include <vector>

#include "Timer.h"
#include "TimerLL.h"

class TimerManager
{
public:
	~TimerManager(void);
	static TimerManager* Instance(void);

	void CreateTimer(std::string name);
	void DestroyTimer(std::string name);

	Timer* GetTimer(std::string name);

	void ExportReport(void);

private:
	static TimerManager* m_Instance;
	TimerManager(void);

	std::vector<Timer*> m_Timers;
};