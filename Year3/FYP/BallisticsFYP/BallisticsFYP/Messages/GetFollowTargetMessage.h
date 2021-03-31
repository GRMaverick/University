#pragma once

#include "IMessage.h"

#include <string>

class GetFollowTargetMessage : public IMessage
{
public:
	GetFollowTargetMessage(void) { }
	virtual ~GetFollowTargetMessage(void) { }
};

class SendFollowTargetMessage : public IMessage
{
public:
	SendFollowTargetMessage(const std::string name) { m_Name = name; }
	virtual ~SendFollowTargetMessage(void) { }

	std::string GetTargetName(void) { return m_Name; }
private:
	std::string m_Name;
};