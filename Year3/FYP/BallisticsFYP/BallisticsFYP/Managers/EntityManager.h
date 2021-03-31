#pragma once

#include <string>
#include <vector>

class IEntity;

class EntityManager
{
public:
	~EntityManager(void);
	static EntityManager* Instance(void);

	void RegisterEntity(const std::string& name);
	void DeregisterEntity(const std::string& name);

	std::vector<std::string> GetEntities(void);
	
private:
	EntityManager(void);

	static EntityManager* m_pInstance;


	std::vector<std::string> m_Entities;
};

#define EntitiesManager EntityManager::Instance()