#pragma once

#include <map>
#include <vector>

#include "../Common//StepTimer.h"

class ISystem;

class SystemsManager
{
public:
	static SystemsManager* Instance(void);

	~SystemsManager(void);

	void RegisterSystem(ISystem* system);
	void RegisterConcurrentSystem(int threadId, ISystem* system);

	void Update(const DX::StepTimer& timer);

private:
	SystemsManager(void);

	static SystemsManager* m_pInstance;
	std::map<int, std::vector<ISystem*>> m_SystemsPerThread;
};

#define SystemManager SystemsManager::Instance()