#include "pch.h"
#include "ExternalBallisticsSystem.h"

#include "IMediator.h"
#include "DelegateFactory.h"

#include "EntityManager.h"
#include "ComponentManager.h"

#include "PhysicsComponent.h"
#include "ProjectileComponent.h"
#include "TransformComponent.h"
#include "LineRenderComponent.h"

#include "UpdateFollowMessage.h"
#include "GetFollowTargetMessage.h"

#include "Integrators.h"

#include "TimerManager.h"
#include "ProjectileTracking.h"

ExternalBallisticsSystem::ExternalBallisticsSystem(void)
{
	m_Gravity = 0.0f;
	m_AirDensity = 0.0f;
	m_EarthTurnSpeed = 0.0f;
	m_WindVector = Vector3(0.0f, 0.0f, 0.0f);
	m_NorthVector = Vector3(0.0f, 0.0f, 0.0f);

	TimerManager::Instance()->CreateTimer("UpdateExternalBallistics");
}
ExternalBallisticsSystem::~ExternalBallisticsSystem(void)
{

}

bool ExternalBallisticsSystem::Initialise(void)
{
	return true;
}
void ExternalBallisticsSystem::RegisterMediator(std::shared_ptr<IMediator> mediator)
{
	m_pMediator = mediator;
	m_pMediator->RegisterReceiveCallback(DELEGATE(&ExternalBallisticsSystem::Receive, this));
}
void ExternalBallisticsSystem::Receive(IMessage* pMessage)
{
	if (SendFollowTargetMessage* pSendTargetMessage = dynamic_cast<SendFollowTargetMessage*>(pMessage))
	{
		m_FollowCamTarget = pSendTargetMessage->GetTargetName();
	}
}

void ExternalBallisticsSystem::Update(DX::StepTimer const& timer)
{
	GetFollowTargetMessage* pGetTargetMessage = new GetFollowTargetMessage();
	m_pMediator->Send(pGetTargetMessage);
	delete pGetTargetMessage;

	std::string trackingName = std::string("Frame" + std::to_string(timer.GetFrameCount()));
	TimerManager::Instance()->GetTimer("UpdateExternalBallistics")->StartTracking(trackingName, timer.GetFrameCount());
	{
		for (std::string entity : EntitiesManager->GetEntities())
		{
			PhysicsComponent* pPhysics = nullptr;
			TransformComponent* pTransform = nullptr;
			ProjectileComponent* pProjectile = nullptr;
			std::vector<LineRenderComponent*> pLineRenders;

			for (IComponent* component : ComponentsManager->GetAllComponentsForEntity(entity))
			{
				if (PhysicsComponent* c = dynamic_cast<PhysicsComponent*>(component))
				{
					pPhysics = c;
				}
				if (TransformComponent* c = dynamic_cast<TransformComponent*>(component))
				{
					pTransform = c;
				}
				if (ProjectileComponent* c = dynamic_cast<ProjectileComponent*>(component))
				{
					pProjectile = c;
				}
				if (LineRenderComponent* c = dynamic_cast<LineRenderComponent*>(component))
				{
					pLineRenders.push_back(c);
				}
			}

			if (pPhysics && pTransform && pProjectile)
			{
				LineRenderComponent* pForcesLine = nullptr;
				LineRenderComponent* pTrajectoryLine = nullptr;
				
				for (LineRenderComponent* pLineRender : pLineRenders)
				{
					if (pLineRender->GetLineName() == std::string(entity + "_Forces"))
					{
						pForcesLine = pLineRender;
					}

					if (pLineRender->GetLineName() == std::string(entity + "_Trajectory"))
					{
						pTrajectoryLine = pLineRender;
					}
				}

				if (pForcesLine)
				{
					auto forces = ApplyForces(pProjectile, pPhysics, pTransform);

					Integrators::RungeKutta4(pPhysics, pTransform, 0.0083f);

					pForcesLine->RemoveLines();

					for each(Vector3 v in forces)
					{
						RenderLine forceLine;
						forceLine.Start = pTransform->GetPosition();
						forceLine.End = pTransform->GetPosition() + (v.Normalise() / 2.0f);

						pForcesLine->AddLine(forceLine);
					}
				}
				else
				{
					ApplyForces(pProjectile, pPhysics, pTransform);

					Integrators::RungeKutta4(pPhysics, pTransform, 0.0083f);
				}

				if (entity == m_FollowCamTarget)
				{
					UpdateFollowMessage* pUpdateFollowMessage = new UpdateFollowMessage(entity, pTransform->GetPosition(), Vector3(1.0f, 1.0f, -1.0f));
					m_pMediator->Send(pUpdateFollowMessage);
					delete pUpdateFollowMessage;
				}

				ProjectileTracking::RegisterPosition(pProjectile->GetOwnerName(), timer.GetFrameCount(), pTransform->GetPosition());
				pProjectile->SetCurrentLifetime(pProjectile->GetCurrentLifetime() + timer.GetElapsedSeconds());

				if (pProjectile->GetFirstPass())
				{
					pProjectile->SetFirstPass(false);
				}
			}
		}
	}
	TimerManager::Instance()->GetTimer("UpdateExternalBallistics")->EndTracking(trackingName);
}
std::vector<Vector3> ExternalBallisticsSystem::ApplyForces(ProjectileComponent* pProjectile, PhysicsComponent* pPhysics, TransformComponent* pTransform)
{
	int forcesToApply = ProjectileComponent::GetApplicableForces();

	std::vector<Vector3> forces;
	
	if (forcesToApply & APPLICABLE_FORCE_GRAVITY)
	{
		forces.push_back(ApplyGravity(pPhysics));
	}
	if (forcesToApply & APPLICABLE_FORCE_DRAG)
	{
		forces.push_back(ApplyDrag(pPhysics, pProjectile));
	}
	if (forcesToApply & APPLICABLE_FORCE_LIFT)
	{
		forces.push_back(ApplyLift(pPhysics, pProjectile, pTransform));
	}
	if (forcesToApply & APPLICABLE_FORCE_WIND)
	{
		forces.push_back(ApplyWind(pPhysics, pProjectile));
	}
	if (forcesToApply & APPLICABLE_FORCE_CORIOLIS)
	{
		forces.push_back(ApplyCoriolis(pPhysics, pProjectile));
	}
	if (forcesToApply & APPLICABLE_FORCE_MAGNUS)
	{
		forces.push_back(ApplyMagnus(pPhysics, pProjectile, pTransform));
	}

	return forces;
}

Vector3 ExternalBallisticsSystem::ApplyWind(PhysicsComponent* pPhysics, ProjectileComponent* pProjectile)
{
	Vector3 wind = m_WindVector * pPhysics->GetMass();

	if (pProjectile->GetFirstPass())
	{
		pPhysics->AddForce(wind);
	}

	return wind;
}
Vector3 ExternalBallisticsSystem::ApplyGravity(PhysicsComponent* pPhysics)
{
	Vector3 gravity = Vector3(0.0f, m_Gravity * pPhysics->GetMass(), 0.0f);
	pPhysics->AddForce(gravity);

	return gravity;
}
Vector3 ExternalBallisticsSystem::ApplyCoriolis(PhysicsComponent* pPhysics, ProjectileComponent* pProjectile)
{
	int secondsPerHour = 3600;
	float metersPerMiles = 1609.34f;
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 east = m_NorthVector.Cross(up);
	Vector3 coriolisForce = east.Negate() * ((metersPerMiles * m_EarthTurnSpeed) / secondsPerHour);
	
	if (pProjectile->GetFirstPass())
	{
		pPhysics->AddForce(coriolisForce * pPhysics->GetMass());
	}

	return coriolisForce;
}
Vector3 ExternalBallisticsSystem::ApplyDrag(PhysicsComponent* pPhysics, ProjectileComponent* pProjectile)
{
	Vector3 velocity = pPhysics->GetVelocity();

	float frontalArea = pProjectile->GetFrontalArea();
	float dragCoef = pProjectile->GetDragCoefficient();

	Vector3 dragDirection = velocity.Negate();
	Vector3 dragDirectionNormalised;

	if (dragDirection.Magnitude() != 0.0f)
	{
		dragDirectionNormalised = dragDirection.Normalise();
	}

	float velocityMag = velocity.Magnitude();
	float dragScalar = m_AirDensity * frontalArea * dragCoef * velocityMag * velocityMag;

	Vector3 drag;
	drag = dragDirectionNormalised * dragScalar;

	pPhysics->AddForce(drag);

	return drag;
}

// TODO: Apply Lift
Vector3 ExternalBallisticsSystem::ApplyLift(PhysicsComponent* pPhysics, ProjectileComponent* pProjectile, TransformComponent* pTransform)
{
	return Vector3();
}

// TODO: Apply Magnus
Vector3	ExternalBallisticsSystem::ApplyMagnus(PhysicsComponent* pPhysics, ProjectileComponent* pProjectile, TransformComponent* pTransform)
{
	return Vector3();
}
