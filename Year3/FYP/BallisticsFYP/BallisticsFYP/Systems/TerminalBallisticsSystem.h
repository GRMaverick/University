#pragma once

#include <memory>

#include "ISystem.h"
#include "../Common/DeviceResources.h"

class IMessage;
class IMediator;
class PhysicsComponent;
class TransformComponent;
class CollisionComponent;
class ProjectileComponent;

struct CollidingPair
{
	PhysicsComponent*	pProjectilePhysics;
	CollisionComponent* pProjectileCollision;
	TransformComponent* pProjectileTransform;

	CollisionComponent* pTargetCollision;
	TransformComponent* pTargetTransform;
};


class TerminalBallisticsSystem : public ISystem
{
public:
	TerminalBallisticsSystem(void);
	virtual ~TerminalBallisticsSystem(void);

	bool							Initialise(void);
	void							RegisterMediator(std::shared_ptr<IMediator> mediator);
	void							Receive(IMessage* message);

	virtual void					Update(DX::StepTimer const& timer) override;

private:
	std::shared_ptr<IMediator>		m_pMediator;

	bool	HasExpired(ProjectileComponent* pProjectile);
	void	DetermineBroadPhaseCollidingPairs(const std::vector<CollisionComponent*>& collisionComponents, 
												const std::vector<TransformComponent*>& transformComponent, 
												const std::vector<PhysicsComponent*>& physicsComponents,
												std::vector<CollidingPair>& pairs);
	void	DetermineNarrowPhaseCollidingPairs(const std::vector<CollidingPair>& collidingPairs);
	void	ResolveCollision(const CollidingPair& collidingPair);
};