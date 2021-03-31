#pragma once
#include "Vector3.h"
#include "IMessage.h"

using namespace Mathematics::Structures;

class UpdateFollowMessage : public IMessage
{
public:
	UpdateFollowMessage(const std::string& name, const Vector3& target, const Vector3& offset)
	{
		m_Name = name;
		m_Target = target;
		m_Offset = offset;
	}
	virtual ~UpdateFollowMessage(void)
	{

	}

	Vector3 GetTarget(void) { return m_Target; }
	Vector3 GetOffset(void) { return m_Offset; }
	std::string GetTargetName(void) { return m_Name; }

private:
	Vector3 m_Target;
	Vector3 m_Offset;
	std::string m_Name;
};