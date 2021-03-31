#pragma once

#include "ISystem.h"
#include "WeaponComponent.h"

class IMessage;
class IMediator;

class InternalBallisticsSystem : public ISystem
{
public:
	InternalBallisticsSystem(void);
	virtual ~InternalBallisticsSystem(void);

	bool Initialise(std::shared_ptr<DX::DeviceResources> resources);
	void RegisterMediator(std::shared_ptr<IMediator> mediator);
	void Receive(IMessage* message);

	virtual void Update(DX::StepTimer const& timer) override;

private:
	DX::StepTimer								m_Timer;
	std::shared_ptr<IMediator>					m_pMediator;
	WeaponComponent*							m_pCurrentWeapon;
	std::shared_ptr<DX::DeviceResources>		m_pDeviceResources;

	int											m_BurstFireLimit;
	int											m_MagazinesUsed;
	int											m_BurstFireRoundsLeft;
	bool										m_HammerIsRetracted;

	void FireProjectile(void);
	void ReloadWeapon(void);
	void RetractHammer(void);
	bool CanFire(WeaponComponent* pWeapon);
};