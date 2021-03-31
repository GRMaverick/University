#pragma once

#include <string>
#include <map>
#include <d3d11_1.h>
#include <directxmath.h>

class IComponent;

class IEntity
{
public:
	//
	// DTOR
	//
	virtual ~IEntity(void) {}
	//
	// Method:					SetName
	// Description:				Sets the entities name
	// Parameters:
	//		(IN)						std::string name
	//
	virtual void					SetName(const std::string& name) { m_Name = name; }
	//
	// Method:					AddComponent
	// Description:				Adds a component to the entity
	// Parameters:
	//		(IN)						std::string			componentName
	//		(IN)						IComponent*	component
	//
	virtual void					AddComponent(const std::string& componentName, IComponent* component) { m_Components[componentName] = component; };
	//
	// Method:					RemoveComponent
	// Description:				Removes a component to the entity
	// Parameters:
	//		(IN)						std::string name
	//
	virtual void					RemoveComponent(std::string componentName) 
	{
		delete m_Components[componentName];
		m_Components.erase(componentName);
	}
	//
	// Method:					GetName
	// Description:				Returns the name of the entity
	// Returns:					m_Name
	// 
	virtual std::string			GetName(void) { return m_Name; };
	//
	// Method:					GetComponent
	// Description:				Returns the component mapped to name
	// Parameters:				
	//		(IN)						std::string componentName			
	// Returns:					m_Components[componentName]
	// 
	virtual IComponent*	GetComponent(std::string componentName) { return m_Components[componentName]; }

protected:
	std::string												m_Name;
	std::map<std::string, IComponent*>	m_Components;
};

