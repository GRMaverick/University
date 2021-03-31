#include "pch.h"
#include "ComponentManager.h"

ComponentManager* ComponentManager::m_pInstance = nullptr;

ComponentManager::ComponentManager(void)
{

}
ComponentManager::~ComponentManager(void)
{

}
ComponentManager* ComponentManager::Instance(void)
{
	if (!m_pInstance)
	{
		m_pInstance = new ComponentManager();
	}
	return m_pInstance;
}

void ComponentManager::RegisterComponent(const std::string& ownerName, const std::string& componentName, IComponent* pComponent)
{
	pComponent->SetOwnerName(ownerName);
	m_Components[ownerName][componentName] = pComponent;
}
void ComponentManager::DeregisterComponent(const std::string& ownerName, const std::string& componentName)
{
	delete m_Components[ownerName][componentName];
	m_Components[ownerName].erase(componentName);
}
void ComponentManager::DeregisterComponents(const std::string& ownerName)
{
	auto components = m_Components[ownerName];
	for (auto iter = components.begin(); iter != components.end(); ++iter)
	{
		delete iter->second;
	}
	m_Components.erase(ownerName);
}

		
std::map<std::string, std::map<std::string, IComponent*>> 
ComponentManager::GetAllComponents(void) const
{
	return m_Components;
}

std::vector<IComponent*>
ComponentManager::GetAllComponentsForEntity(const std::string& entity)
{
	std::vector<IComponent*> components;

	auto it = m_Components[entity].begin();
	for (; it != m_Components[entity].end(); ++it)
		components.push_back(it->second);

	return components;
}

IComponent* 
ComponentManager::GetComponent(const std::string& ownerName, const std::string& componentName)
{
	return m_Components[ownerName][componentName];
}