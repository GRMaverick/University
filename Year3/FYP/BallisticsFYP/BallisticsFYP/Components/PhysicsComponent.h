#pragma once

#include "Vector3.h"
#include "IComponent.h"

using namespace Mathematics::Structures;

class PhysicsComponent : public IComponent
{
public:
	PhysicsComponent(void) 
	{
		m_Mass = 0.0f;
		m_Velocity = Vector3(0.0f, 0.0f, 0.0f);
		m_NetForce = Vector3(0.0f, 0.0f, 0.0f);
		m_Acceleration = Vector3(0.0f, 0.0f, 0.0f);
	}
	virtual ~PhysicsComponent(void) { }

	void SetOwnerName(const std::string& name) { IComponent::SetOwnerName(name); }
	std::string GetOwnerName(void) { return IComponent::GetOwnerName(); }

	PhysicsComponent* AddForce(const Vector3& force) { m_NetForce += force; return this; }

	PhysicsComponent* SetMass(const float& mass) { m_Mass = mass; return this; }
	PhysicsComponent* SetVelocity(const Vector3& velocity) { m_Velocity = velocity; return this; }
	PhysicsComponent* SetNetforce(const Vector3& netforce) { m_NetForce = netforce; return this; }
	PhysicsComponent* SetAcceleration(const Vector3& acceleration) { m_Acceleration = acceleration; return this; }

	float GetMass(void) const { return m_Mass; }
	Vector3 GetVelocity(void) const { return m_Velocity; }
	Vector3 GetNetforce(void) const { return m_NetForce; }
	Vector3 GetAcceleration(void) const { return m_Acceleration; }

private:
	float m_Mass;						// Kilograms
	Vector3 m_Velocity;				// Squared-Meters
	Vector3 m_NetForce;			// Newtons
	Vector3 m_Acceleration;		// Squared-Meters-Squared
};
