#include "pch.h"
#include "IMediator.h"
#include "InternalBallisticsSystem.h"

#include "Integrators.h"
#include "DelegateFactory.h"

#include "TimerManager.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "ProjectileTracking.h"

#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "ProjectileComponent.h"
#include "LineRenderComponent.h"

#include "SetAmmunitionType.h"
#include "UpdateFollowMessage.h"
#include "ReloadWeaponMessage.h"
#include "RetractHammerMessage.h"
#include "FireProjectileMessage.h"

#include "M43_762_39.h"
#include "NATO_556x45.h"
#include "Parabellum9x19mm.h"

#include <iostream>

InternalBallisticsSystem::InternalBallisticsSystem(void)
{
	m_BurstFireLimit = 3;										// Burst-Fire allows three bullets to be fired with one pull of the trigger.	
	m_MagazinesUsed = 0;
	m_HammerIsRetracted = true;
	m_BurstFireRoundsLeft = m_BurstFireLimit;

	TimerManager::Instance()->CreateTimer("FireProjectile");
}
InternalBallisticsSystem::~InternalBallisticsSystem(void)
{
}

bool InternalBallisticsSystem::Initialise(std::shared_ptr<DX::DeviceResources> resources)
{
	m_pDeviceResources = resources;
	return true;
}
void InternalBallisticsSystem::RegisterMediator(std::shared_ptr<IMediator> mediator)
{
	m_pMediator = mediator;
	m_pMediator->RegisterReceiveCallback(DELEGATE(&InternalBallisticsSystem::Receive, this));
}
void InternalBallisticsSystem::Receive(IMessage* pMessage)
{
	if (FireProjectileMessage* pMsg = dynamic_cast<FireProjectileMessage*>(pMessage))
	{
		FireProjectile();
	}
	if (ReloadWeaponMessage* pMsg = dynamic_cast<ReloadWeaponMessage*>(pMessage))
	{
		ReloadWeapon();
	}
	if (RetractHammerMessage* pMsg = dynamic_cast<RetractHammerMessage*>(pMessage))
	{
		RetractHammer();
	}
	if (SetAmmunitionType* pMsg = dynamic_cast<SetAmmunitionType*>(pMessage))
	{
		if (pMsg->GetName() == "5.56x45mm")
		{
			m_pCurrentWeapon->SetProjectile(new NATO_556x45());
		}
		else if (pMsg->GetName() == "7.62x39mm")
		{
			m_pCurrentWeapon->SetProjectile(new M43_762_39());
		}
		else if (pMsg->GetName() == "9x19mm")
		{
			m_pCurrentWeapon->SetProjectile(new Parabellum9x19mm());
		}
	}
}

void InternalBallisticsSystem::Update(DX::StepTimer const& timer)
{
	m_Timer = timer;
	for (std::string entity : EntitiesManager->GetEntities())
	{
		WeaponComponent* pWeaponComponent;

		for (IComponent* component : ComponentsManager->GetAllComponentsForEntity(entity))
		{
			if (WeaponComponent* pComponent = dynamic_cast<WeaponComponent*>(component))
			{ 
				if (pComponent->IsActive())
				{
					m_pCurrentWeapon = pComponent;
				}
			}
		}
	}
}

void InternalBallisticsSystem::FireProjectile(void)
{
	std::cout << "Firing projectile" << std::endl;

	if (CanFire(m_pCurrentWeapon))
	{
		std::string weaponName = m_pCurrentWeapon->GetName();
		std::string projectileName = std::string("Projectile_") + m_pCurrentWeapon->GetProjectile()->GetType() + "_" + std::to_string(m_MagazinesUsed) + std::string("_") + std::to_string(m_pCurrentWeapon->GetRoundsPerMagazine() - m_pCurrentWeapon->GetRoundsRemaining());

		TimerManager::Instance()->GetTimer("FireProjectile")->StartTracking(projectileName, m_Timer.GetFrameCount());
		{
			IProjectilePrefab* pNewProjectile = m_pCurrentWeapon->GetProjectile()->Clone(projectileName);
			pNewProjectile->Initialise(m_pDeviceResources);

			PhysicsComponent* pPhysicsComponent = dynamic_cast<PhysicsComponent*>(ComponentsManager->GetComponent(projectileName, "Physics"));
			ProjectileComponent* pProjectileComponent = dynamic_cast<ProjectileComponent*>(ComponentsManager->GetComponent(projectileName, "Projectile"));
			TransformComponent* pWeaponTransformComponent = dynamic_cast<TransformComponent*>(ComponentsManager->GetComponent(weaponName, "Transform"));
			TransformComponent* pProjectileTransformComponent = dynamic_cast<TransformComponent*>(ComponentsManager->GetComponent(projectileName, "Transform"));

			XMVECTOR s, r, t;
			bool temp = XMMatrixDecompose(&s, &r, &t, pWeaponTransformComponent->GetWorldMatrix());

			XMFLOAT3 translation;
			XMStoreFloat3(&translation, t);
			Vector3 rotation = pWeaponTransformComponent->GetParent()->GetRotation();

			pProjectileTransformComponent->SetRotation(rotation.x + 90.0f, rotation.y, rotation.z);
			pProjectileTransformComponent->SetForward(pWeaponTransformComponent->GetForward());
			pProjectileTransformComponent->SetPosition(Vector3(translation.x, translation.y + 0.05f, translation.z));

			Vector3 muzzleVelocity = pProjectileTransformComponent->GetForward() * pProjectileComponent->GetMuzzleVelocity();
			pPhysicsComponent->AddForce(muzzleVelocity);

			pProjectileComponent->SetMaxLifetime(7.5f);
			//pProjectileComponent->SetMaxLifetime(60.0f);
			pProjectileComponent->SetCurrentLifetime(0.0f);
			pProjectileComponent->SetRevolutionsPerMinute((pProjectileComponent->GetMuzzleVelocity() * 3.28084f) * (12.0f / ((float)m_pCurrentWeapon->GetTwistRate())) * 60.0f);
									
			m_pCurrentWeapon->SetTimeSinceLastFired(0.0f);
			m_pCurrentWeapon->SetRoundsRemaining(m_pCurrentWeapon->GetRoundsRemaining() - 1);
			ProjectileTracking::RegisterPosition(pProjectileComponent->GetOwnerName(), m_Timer.GetFrameCount(), pProjectileTransformComponent->GetPosition());

			UpdateFollowMessage* pUpdateFollowMessage = new UpdateFollowMessage(projectileName, pProjectileTransformComponent->GetPosition(), Vector3(1.0f, 1.0f, -1.0f));
			m_pMediator->Send(pUpdateFollowMessage);
			delete pUpdateFollowMessage;
		}
		TimerManager::Instance()->GetTimer("FireProjectile")->EndTracking(projectileName);
	}
}
void InternalBallisticsSystem::ReloadWeapon(void)
{
	m_MagazinesUsed++;
	m_pCurrentWeapon->SetRoundsRemaining(m_pCurrentWeapon->GetRoundsPerMagazine());
}
bool InternalBallisticsSystem::CanFire(WeaponComponent* pWeapon)
{
	if (pWeapon->GetRoundsRemaining() > 0)
	{
		switch (pWeapon->GetFiringMode())
		{
			case WeaponComponent::FiringMode_SemiAutomatic:
			{
				if (m_HammerIsRetracted)
				{
					m_HammerIsRetracted = false;
					return true;
				}
				break;
			}
			case WeaponComponent::FiringMode_BurstFire:			// Boolean Persistance Problems
			{
				if (m_HammerIsRetracted)
				{
					float aSecond = 1000; // Milliseconds
					float TimePerRound = 60.0f / pWeapon->GetRateOfFire();

					if (pWeapon->GetTimeSinceLastFired() >= TimePerRound)
					{
						if (m_BurstFireRoundsLeft > 0)
						{
							if (m_BurstFireLimit <= 0)
							{
								m_HammerIsRetracted = false;
								return false;
							}
							else
							{
								m_BurstFireRoundsLeft--;
								return true;
							}
						}
					}
					pWeapon->SetTimeSinceLastFired(pWeapon->GetTimeSinceLastFired() + m_Timer.GetElapsedSeconds());
				}
				break;
			}
			case WeaponComponent::FiringMode_FullAutomatic:
			{
				float aSecond = 1000; // Milliseconds
				float TimePerRound = 60.0f / pWeapon->GetRateOfFire();

				if (pWeapon->GetTimeSinceLastFired() >= TimePerRound)
				{
					return true;
				}
				pWeapon->SetTimeSinceLastFired(pWeapon->GetTimeSinceLastFired() + m_Timer.GetElapsedSeconds());
				break;
			}
			case WeaponComponent::FiringMode_None:
			case WeaponComponent::FiringMode_Max:
			default:
				break;
		}
	}
	return false;
}
void InternalBallisticsSystem::RetractHammer(void)
{
	if (m_BurstFireRoundsLeft <= 0)
	{
		m_BurstFireRoundsLeft = m_BurstFireLimit;
	}
	m_HammerIsRetracted = true;
}