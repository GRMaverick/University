#include "pch.h"
#include <random>
#include <iostream>

#include "TerminalBallisticsSystem.h"

#include "IMediator.h"
#include "IMessage.h"
#include "DelegateFactory.h"

#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "ProjectileComponent.h"
#include "LineRenderComponent.h"

#include "TimerManager.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "ProjectileTracking.h"

#include "NarrowPhaseCollisionDetection.h"

#include "Plane.h"
#include "Intersections.h"

using namespace Mathematics::Structures;
using namespace Mathematics::Intersections;

TerminalBallisticsSystem::TerminalBallisticsSystem(void)
{
	TimerManager::Instance()->CreateTimer("UpdateTerminalBallistics");
}
TerminalBallisticsSystem::~TerminalBallisticsSystem(void)
{

}

bool TerminalBallisticsSystem::Initialise(void)
{
	return true;
}
void TerminalBallisticsSystem::RegisterMediator(std::shared_ptr<IMediator> pMediator)
{
	m_pMediator = pMediator;
	m_pMediator->RegisterReceiveCallback(DELEGATE(&TerminalBallisticsSystem::Receive, this));
}
void TerminalBallisticsSystem::Receive(IMessage* pMessage)
{
}

void TerminalBallisticsSystem::Update(DX::StepTimer const& timer)
{
	std::string trackingName = std::string("Frame" + std::to_string(timer.GetFrameCount()));
	TimerManager::Instance()->GetTimer("UpdateTerminalBallistics")->StartTracking(trackingName, timer.GetFrameCount());
	{
		std::vector<CollidingPair> pairs;
		std::vector<PhysicsComponent*> physicsComponents;
		std::vector<TransformComponent*> transformComponents;
		std::vector<CollisionComponent*> collisionComponents;
		std::vector<ProjectileComponent*> projectileComponents;
		std::map<string, std::vector<LineRenderComponent*>> pLineRenders;

		TransformComponent* pFloorTransform = nullptr;
		for (std::string entity : EntitiesManager->GetEntities())
		{
			PhysicsComponent* pTempPhysics = nullptr;
			CollisionComponent* pTempCollider = nullptr;
			TransformComponent* pTempTransform = nullptr;
			ProjectileComponent* pTempProjectile = nullptr;

			for (IComponent* pComponent : ComponentsManager->GetAllComponentsForEntity(entity))
			{
				if (CollisionComponent* pColliderTemp = dynamic_cast<CollisionComponent*>(pComponent))
				{
					pTempCollider = pColliderTemp;
				}
				if (ProjectileComponent* pProjectileTemp = dynamic_cast<ProjectileComponent*>(pComponent))
				{
					pTempProjectile = pProjectileTemp;
				}
				if (TransformComponent* pTransformTemp = dynamic_cast<TransformComponent*>(pComponent))
				{
					pTempTransform = pTransformTemp;
				}
				if (PhysicsComponent* pPhysicsTemp = dynamic_cast<PhysicsComponent*>(pComponent))
				{
					pTempPhysics = pPhysicsTemp;
				}				
				if (LineRenderComponent* c = dynamic_cast<LineRenderComponent*>(pComponent))
				{
					pLineRenders[entity].push_back(c);
				}
			}

			//if (entity == "Floor")
			//{
			//	physicsComponents.push_back(nullptr);
			//	collisionComponents.push_back(nullptr);
			//	transformComponents.push_back(pTempTransform);
			//}

			if (pTempCollider && pTempTransform && !pTempProjectile)
			{
				// Entity is a Target
				physicsComponents.push_back(nullptr);
				collisionComponents.push_back(pTempCollider);
				transformComponents.push_back(pTempTransform);
			}

			if (pTempCollider && pTempProjectile && pTempTransform && pTempPhysics)
			{
				// Entity is a Projectile
				if (!HasExpired(pTempProjectile))
				{
					physicsComponents.push_back(pTempPhysics);
					collisionComponents.push_back(pTempCollider);
					transformComponents.push_back(pTempTransform);
					projectileComponents.push_back(pTempProjectile);
					pTempProjectile->SetCurrentLifetime(pTempProjectile->GetCurrentLifetime() + timer.GetElapsedSeconds());
				}
				else
				{
					EntitiesManager->DeregisterEntity(pTempProjectile->GetOwnerName());
					ComponentsManager->DeregisterComponents(pTempProjectile->GetOwnerName());
				}
			}
		}
				
		DetermineBroadPhaseCollidingPairs(collisionComponents, transformComponents, physicsComponents, pairs);
		DetermineNarrowPhaseCollidingPairs(pairs);

		for (TransformComponent* pTransform : transformComponents)
		{
			LineRenderComponent* pTrajectoryLine = nullptr;
			for (LineRenderComponent* pLineRender : pLineRenders[pTransform->GetOwnerName()])
			{
				if (pLineRender->GetLineName().find("Trajectory") != std::string::npos)
				{
					pTrajectoryLine = pLineRender;
					break;
				}
			}
			if (pTrajectoryLine)
			{
				pTrajectoryLine->AddLine(pTransform->GetLastPosition(), pTransform->GetPosition());
			}
		}
	}
	TimerManager::Instance()->GetTimer("UpdateTerminalBallistics")->EndTracking(trackingName);
}

bool TerminalBallisticsSystem::HasExpired(ProjectileComponent* pComponent)
{
	float maxLifetime = pComponent->GetMaxLifetime();
	float currentLifetime = pComponent->GetCurrentLifetime();

	if (currentLifetime > maxLifetime)
	{
		return true;
	}

	return false;
}
void TerminalBallisticsSystem::DetermineBroadPhaseCollidingPairs(const std::vector<CollisionComponent*>& collisionComponents, const std::vector<TransformComponent*>& transformComponents, const std::vector<PhysicsComponent*>& physicsComponent, std::vector<CollidingPair>& pairs)
{
	std::vector<CollidingPair> resultingPairs;

	if (collisionComponents.size() != transformComponents.size())
	{
		pairs = resultingPairs;
		return;
	}

	for (int i = 0; i < collisionComponents.size(); ++i)
	{
		for (int j = 0; j < collisionComponents.size(); ++j)
		{
			if (i != j)
			{
				CollidingPair pair;

				// Stop Bullet-Bullet collisions
				if ((transformComponents[i]->GetOwnerName().find("Projectile") != std::string::npos)
					&& (transformComponents[j]->GetOwnerName().find("Projectile") != std::string::npos))
				{
					continue;
				}

				// Add Floor
				if (collisionComponents[i] == nullptr)
				{
					pair.pTargetCollision = nullptr;
					pair.pTargetTransform = transformComponents[i];

					if (transformComponents[j]->GetOwnerName().find("Projectile") != std::string::npos)
					{
						pair.pProjectilePhysics = physicsComponent[j];
						pair.pProjectileCollision = collisionComponents[j];
						pair.pProjectileTransform = transformComponents[j];

						pairs.push_back(pair);
					}

					continue;
				}

				if (collisionComponents[j] == nullptr)
				{
					pair.pTargetCollision = nullptr;
					pair.pTargetTransform = transformComponents[j];

					if (transformComponents[i]->GetOwnerName().find("Projectile") != std::string::npos)
					{
						pair.pProjectilePhysics = physicsComponent[i];
						pair.pProjectileCollision = collisionComponents[i];
						pair.pProjectileTransform = transformComponents[i];

						pairs.push_back(pair);
					}

					continue;
				}

				// Add Target
				if (physicsComponent[i] == nullptr)
				{
					pair.pTargetCollision = collisionComponents[i];
					pair.pTargetTransform = transformComponents[i];

					if (transformComponents[j]->GetOwnerName().find("Projectile") != std::string::npos)
					{
						pair.pProjectilePhysics = physicsComponent[j];
						pair.pProjectileCollision = collisionComponents[j];
						pair.pProjectileTransform = transformComponents[j];

						pairs.push_back(pair);
					}

					continue;
				}

				if (physicsComponent[j] == nullptr)
				{
					pair.pTargetCollision = collisionComponents[j];
					pair.pTargetTransform = transformComponents[j];

					if (transformComponents[i]->GetOwnerName().find("Projectile") != std::string::npos)
					{
						pair.pProjectilePhysics = physicsComponent[i];
						pair.pProjectileCollision = collisionComponents[i];
						pair.pProjectileTransform = transformComponents[i];

						pairs.push_back(pair);
					}

					continue;
				}
			}
		}				
	}
}
void TerminalBallisticsSystem::DetermineNarrowPhaseCollidingPairs(const std::vector<CollidingPair>& collidingPairs)
{
	for (CollidingPair pair : collidingPairs)
	{
		Vector3 intersectionPoint = Vector3(-1.0f, -1.0f, -1.0f);
		Mathematics::Structures::Line bulletLine = Mathematics::Structures::Line(pair.pProjectileTransform->GetPosition(), pair.pProjectilePhysics->GetVelocity().Normalise());
		Mathematics::Structures::Plane targetPlane = pair.pTargetCollision->GetCollidingPlane();

		if (Mathematics::Intersections::LinePlaneIntersection(targetPlane, bulletLine, intersectionPoint))
		{			
			std::mt19937 generator;
			generator.seed(std::random_device()());
			std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

			Vector3 position = pair.pProjectileTransform->GetPosition();
			if (!pair.pProjectileCollision->HasCollided())
			{
				pair.pProjectileTransform->SetPosition(Vector3(position.x, position.y, intersectionPoint.z));

				Vector3 incoming = pair.pProjectilePhysics->GetVelocity();
				Vector3 normal = targetPlane.GetNormal().Normalise();

				float incidence = incoming.AngleInDegrees(normal.Negate());

				if (incidence < 45.0f)
				{
					float radius = 0.05f;
					std::uniform_real_distribution<float> randomX(-radius, radius);
					std::uniform_real_distribution<float> randomY(-radius, radius);

					std::uniform_real_distribution<float> randomTheta(-radius, radius);
					std::uniform_real_distribution<float> randomZ(-1.0f, 1.0f);

					float x = randomX(generator);
					float y = randomY(generator);
					float z = randomZ(generator);
					float theta = randomTheta(generator);

					Vector3 incoming = pair.pProjectilePhysics->GetVelocity();
					Vector3 incomingNormalised = incoming.Normalise();
					float magnitude = (incoming.Magnitude() / 10);
					Vector3 postPenetrativeVector = Vector3(x, y, 1.0f).Normalise();

					pair.pProjectileCollision->SetCollided(true);
					pair.pProjectilePhysics->SetVelocity(postPenetrativeVector * magnitude);
				}
				else
				{
					Vector3 reflection = incoming - (normal * (2 * incoming.Dot(normal)));

					pair.pProjectileCollision->SetCollided(true);
					pair.pProjectilePhysics->SetVelocity(reflection * 0.2f);
				}
			}
		}
	}
}
void TerminalBallisticsSystem::ResolveCollision(const CollidingPair& collidingPair)
{

}