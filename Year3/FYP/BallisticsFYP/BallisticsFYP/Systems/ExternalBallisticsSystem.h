#pragma once

#include "ISystem.h"
#include <memory>
#include "../Common/DeviceResources.h"

#include "Vector3.h"

class IMessage;
class IMediator;
class PhysicsComponent;
class TransformComponent;
class ProjectileComponent;
class LineRenderComponent;

using namespace Mathematics::Structures;

class ExternalBallisticsSystem : public ISystem
{
public:
	ExternalBallisticsSystem(void);
	virtual ~ExternalBallisticsSystem(void);

	bool Initialise(void);

	// // Set Gravity [ Meters-Per-Second (m/s) ]
	ExternalBallisticsSystem*	SetGravity(const float& gravity) { m_Gravity = gravity; return this; }
	// // Set Air Density [ Kilograms-Per-Cubic-Meter (kg/m^3) ]
	ExternalBallisticsSystem*	SetAirDensity(const float& airDensity) { m_AirDensity = airDensity; return this; }
	// // Set Wind Vector 
	ExternalBallisticsSystem*	SetWindVector(const Vector3& windVector) { m_WindVector = windVector; return this; }
	// // Set Earth Turn Speed [ Miles-Per-Hour (MPH) ]
	ExternalBallisticsSystem*	SetEarthTurnSpeed(const float& turnSpeed) { m_EarthTurnSpeed = turnSpeed; return this; }
	// // Set North Vector's X and Z components.
	ExternalBallisticsSystem*	SetNorth(const float& xx, const float& zz) { m_NorthVector = Vector3(xx, 0.0f, zz); return this; }

	void						RegisterMediator(std::shared_ptr<IMediator> mediator);
	void						Receive(IMessage* pMessage);

	virtual void				Update(DX::StepTimer const& timer) override;

private:
	std::shared_ptr<IMediator>	m_pMediator;

	float						m_Gravity;				// Meters-Per-Second
	float						m_AirDensity;			// Kilograms-Per-Cubic-Meter
	float						m_EarthTurnSpeed;		// Miles-Per-Hour
	Vector3						m_WindVector;
	Vector3						m_NorthVector;
	std::string					m_FollowCamTarget;

	std::vector<Vector3>		ApplyForces(ProjectileComponent* pProjectile, PhysicsComponent* pPhysics, TransformComponent* pTransform);
	Vector3						ApplyWind(PhysicsComponent* pPhysics, ProjectileComponent* pProjectile);
	Vector3						ApplyGravity(PhysicsComponent* pPhysics);
	Vector3						ApplyCoriolis(PhysicsComponent* pPhysics, ProjectileComponent* pProjectile);
	Vector3						ApplyDrag(PhysicsComponent* pPhysics, ProjectileComponent* pProjectile);
	Vector3						ApplyLift(PhysicsComponent* pPhysics, ProjectileComponent* pProjectile, TransformComponent* pTransform);
	Vector3						ApplyMagnus(PhysicsComponent* pPhysics, ProjectileComponent* pProjectile, TransformComponent* pTransform);
};