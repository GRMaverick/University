#include <iostream>
#include "TestApp.h"
#include "AppManager.h"
#include "ApplicationEnum.h"
#include "ParallelStaticApp.h"
#include "ParallelPhysicsApp.h"
#include "SequentialStaticApp.h"
#include "SequentialPhysicsApp.h"
#include "SequentialStaticBVApp.h"


AppManager* AppManager::m_Instance = nullptr;

AppManager::AppManager(void)
{

}
AppManager::~AppManager(void)
{

}

AppManager* AppManager::Instance(void)
{
	if (!m_Instance)
		m_Instance = new AppManager();

	return m_Instance;
}

BaseApplication* AppManager::GetApplication(int application)
{
	switch (application)
	{
		case Application_Dummy:
			return new TestApp();
		case Application_SequentialStatic:
			return new SequentialStaticApp();
		case Application_SequentialPhysics:
			return new SequentialPhysicsApp();
		case Application_SequentialStaticBV:
			return new SequentialStaticBVApp();
		case Application_ParallelStatic:
			return new ParallelStaticApp();
		case Application_ParallelPhysics:
			return new ParallelPhysicsApp();
		case Application_SequentialPhysicsBV:
		case Application_ParallelStaticBV:
		case Application_ParallelPhysicsBV:
		default:
			std::cout << "Invalid Selection" << std::endl;
			return nullptr;
	}
}