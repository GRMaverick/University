#pragma once

#include "Vector3.h"
#include "IComponent.h"

#define APPLICABLE_FORCE_NONE		0x01			// 0000 0001
#define APPLICABLE_FORCE_GRAVITY	0x02			// 0000 0010
#define APPLICABLE_FORCE_DRAG		0x04			// 0000 0100
#define APPLICABLE_FORCE_WIND		0x08			// 0000 1000
#define APPLICABLE_FORCE_CORIOLIS	0x10			// 0001 0000
#define APPLICABLE_FORCE_MAGNUS		0x20			// 0010 0000
#define APPLICABLE_FORCE_LIFT		0x40			// 0100 0000

class ProjectileComponent : public IComponent
{
public:
	enum BallisticPipelineState
	{
		PipelineState_None				= 0x01,
		PipelineState_Internal			= 0x02,
		PipelineState_External			= 0x04,
		PipelineState_Terminal			= 0x08,
		PipelineState_Max				= 0x10,
	};

	ProjectileComponent(void) : m_PipelineState(PipelineState_Internal) { m_FirstPass = true; }
	virtual ~ProjectileComponent(void) { }

	void					SetOwnerName(const std::string& name) { IComponent::SetOwnerName(name); }
	std::string				GetOwnerName(void) { return IComponent::GetOwnerName(); }

	static void				SetApplicableForces(const int& forces) { m_ApplicableForces = forces; }

	ProjectileComponent*	SetLength(const float& length) { m_Length = length; return this; }
	ProjectileComponent*	SetFirstPass(const bool& firstPass) { m_FirstPass = firstPass; return this; }
	ProjectileComponent*	SetFrontalArea(const float& frontalArea) { m_FrontalArea = frontalArea; return this; }
	ProjectileComponent*	SetMaxLifetime(const float& maxLifetime) { m_MaxLifetime = maxLifetime; return this; }
	ProjectileComponent*	SetRevolutionsPerMinute(const float& rpm) { m_RevolutionsPerMinute = rpm; return this; }
	ProjectileComponent*	SetMuzzleVelocity(const float& muzzleVelocity) { m_MuzzleVelocity = muzzleVelocity; return this; }
	ProjectileComponent*	SetLiftCoefficient(const float& liftCoefficient) { m_LiftCoefficient = liftCoefficient; return this; }
	ProjectileComponent*	SetCurrentLifetime(const float& currentLifetime) { m_CurrentLifetime = currentLifetime; return this; }
	ProjectileComponent*	SetDragCoefficient(const float& dragCoefficient) { m_DragCoefficient = dragCoefficient; return this; }
	ProjectileComponent*	SetBallisticPipelineState(const BallisticPipelineState& state) { m_PipelineState = state; return this; }

	
	float					GetLength(void) { return m_Length; }
	bool					GetFirstPass(void) { return m_FirstPass; }
	float					GetFrontalArea(void) { return m_FrontalArea; }
	float					GetMaxLifetime(void) { return m_MaxLifetime; }
	float					GetLiftCoefficient(void) { return m_LiftCoefficient; }
	float					GetMuzzleVelocity(void) { return m_MuzzleVelocity; }
	float					GetCurrentLifetime(void) { return m_CurrentLifetime; }
	float					GetDragCoefficient(void) { return m_DragCoefficient; }
	static int				GetApplicableForces(void) { return m_ApplicableForces; }
	BallisticPipelineState	GetBallisticPipelineState(void) { return m_PipelineState; }
	float					GetRevolutionsPerMinute(void) { return m_RevolutionsPerMinute; }


private:
	float					m_Length;
	bool					m_FirstPass;
	float					m_FrontalArea;				// Squared-Meters
	float					m_MaxLifetime;				// Seconds
	BallisticPipelineState	m_PipelineState;
	float					m_MuzzleVelocity;			// Squared-Meters
	float					m_LiftCoefficient;			// Dimensionless
	float					m_CurrentLifetime;			// Seconds
	float					m_DragCoefficient;			// Dimensionless
	static int				m_ApplicableForces;
	float					m_RevolutionsPerMinute;
};