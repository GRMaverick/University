#include "pch.h"
#include "EntityManager.h"
#include "IEntity.h"

EntityManager* EntityManager::m_pInstance = nullptr;

EntityManager::EntityManager(void)
{
	m_Entities = std::vector<std::string>();
	m_Entities.clear();
}
EntityManager::~EntityManager(void)
{

}

EntityManager* EntityManager::Instance(void)
{
	if (!m_pInstance)
	{
		m_pInstance = new EntityManager();
	}
	return m_pInstance;
}

void EntityManager::RegisterEntity(const std::string& entity)
{
	m_Entities.push_back(entity);
}
void EntityManager::DeregisterEntity(const std::string& name)
{
	int count = 0;
	for (int i = 0; i < m_Entities.size(); i++)
	{
		if (m_Entities[i] != name)
		{
			count++;
		}
		else
		{
			m_Entities.erase(m_Entities.begin() + count);
			break;
		}
	}
}

std::vector<std::string> EntityManager::GetEntities(void)
{
	return m_Entities;
}