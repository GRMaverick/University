#pragma once

#include <map>
#include <string>
#include <vector>

#include "IComponent.h"

class ComponentManager
{
public:
	~ComponentManager(void);
	static ComponentManager* Instance(void);

	void RegisterComponent(const std::string& ownerName, const std::string& componentName, IComponent* pComponent);
	void DeregisterComponent(const std::string& ownerName, const std::string& componentName);
	void DeregisterComponents(const std::string& ownerName);

	std::map<std::string, std::map<std::string, IComponent*>>		GetAllComponents(void) const;
	std::vector<IComponent*>															GetAllComponentsForEntity(const std::string& entity);
	IComponent*																				GetComponent(const std::string& ownerName, const std::string& componentName);
private:
	ComponentManager(void);
	
	static ComponentManager* m_pInstance;

	std::map<std::string, std::map<std::string, IComponent*>> m_Components;
};

#define ComponentsManager ComponentManager::Instance()