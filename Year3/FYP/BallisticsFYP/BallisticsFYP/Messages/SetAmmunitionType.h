#pragma once

#include "IMessage.h"
#include <string>

class SetAmmunitionType : public IMessage
{
public:
	SetAmmunitionType(const std::string& name) { m_Name = name; }
	virtual ~SetAmmunitionType(void) { }

	std::string GetName(void) { return m_Name; }
private:
	std::string m_Name;
};