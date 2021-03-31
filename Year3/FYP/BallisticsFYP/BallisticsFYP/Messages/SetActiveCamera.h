#pragma once
#include <string>

#include "IMessage.h"

class SetActiveCamera : public IMessage
{
public:
	SetActiveCamera(const std::string& name);
	~SetActiveCamera(void);

	std::string GetNewActiveCamera(void);
private:
	std::string m_Name;
};