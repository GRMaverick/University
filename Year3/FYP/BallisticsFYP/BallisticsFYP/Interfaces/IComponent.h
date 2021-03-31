#pragma once
#include <string>

class IComponent
{
public:
	virtual ~IComponent(void) {}

	virtual void SetOwnerName(const std::string& name) { m_OwnerName = name; }
	virtual std::string GetOwnerName(void) { return m_OwnerName; }

private:
	std::string m_OwnerName;
};