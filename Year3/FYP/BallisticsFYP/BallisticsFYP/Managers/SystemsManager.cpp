#include "pch.h"
#include "SystemsManager.h"
#include "ISystem.h"

#include <thread>
#include <iostream>

SystemsManager* SystemsManager::m_pInstance = nullptr;

void UpdateSystems(int threadId, std::vector<ISystem*> systems, const DX::StepTimer& timer);

SystemsManager::SystemsManager(void)
{

}
SystemsManager::~SystemsManager(void)
{

}

SystemsManager* SystemsManager::Instance(void)
{
	if (!m_pInstance)
	{
		m_pInstance = new SystemsManager();
	}
	return m_pInstance;
}

void SystemsManager::RegisterSystem(ISystem* system)
{
	m_SystemsPerThread[0].push_back(system);
}
void SystemsManager::RegisterConcurrentSystem(int threadId, ISystem* system)
{
	m_SystemsPerThread[threadId].push_back(system);
}

void SystemsManager::Update(const DX::StepTimer& timer)
{
	int i = 0;
	std::thread* pThreads = new std::thread[m_SystemsPerThread.size()];
	for (auto iter = m_SystemsPerThread.begin(); iter != m_SystemsPerThread.end(); ++iter)
	{
		pThreads[i] = std::thread(UpdateSystems, iter->first, m_SystemsPerThread[iter->first], timer);
		++i;
	}

	for (int i = 0; i < m_SystemsPerThread.size(); i++)
	{
		pThreads[i].join();
	}

	delete[] pThreads;
}

void UpdateSystems(int threadId, std::vector<ISystem*> systems, const DX::StepTimer& timer)
{
	for (ISystem* system : systems)
	{
		system->Update(timer);
	}
}