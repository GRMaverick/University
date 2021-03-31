#pragma once

#include "IComponent.h"

#include "IProjectilePrefab.h"

class WeaponComponent : public IComponent
{
public:
	enum FiringMode
	{
		FiringMode_None					= 0x01,
		FiringMode_SemiAutomatic	= 0x02,
		FiringMode_BurstFire				= 0x04,
		FiringMode_FullAutomatic		= 0x08,
		FiringMode_Max						= 0x10
	};

	WeaponComponent(void) 
	{
		m_IsActive = false;
		m_RateOfFire = 0;
		m_RoundsRemaining = 0;
		m_RoundsPerMagazine = 0;
		m_FiringMode = FiringMode_None;
		m_ProjectileType = nullptr;
	}
	WeaponComponent(const WeaponComponent& rhs)
	{
		this->m_Name = rhs.m_Name;
		this->m_IsActive = rhs.m_IsActive;
		this->m_RateOfFire = rhs.m_RateOfFire;
		this->m_RoundsRemaining = rhs.m_RoundsRemaining;
		this->m_RoundsPerMagazine = rhs.m_RoundsPerMagazine;
		this->m_FiringMode = rhs.m_FiringMode;

		if (rhs.m_ProjectileType)
		{
			this->m_ProjectileType = rhs.m_ProjectileType->Clone();
		}
		else
		{
			this->m_ProjectileType = nullptr;
		}
	}
	virtual ~WeaponComponent(void) 
	{
		if (m_ProjectileType) delete m_ProjectileType;
	}

	void						SetOwnerName(const std::string& name) { IComponent::SetOwnerName(name); }
	std::string					GetOwnerName(void) { return IComponent::GetOwnerName(); }


	WeaponComponent*			SetName(const std::string& name) { m_Name = name; return this; }
	WeaponComponent*			SetActive(const bool& isActive) { m_IsActive = isActive; return this; }
	WeaponComponent*			SetFiringMode(const FiringMode& mode) { m_FiringMode = mode; return this; }
	//	--> Set Rate of Fire [Rounds Per Minute (RPM)]
	WeaponComponent*			SetRateOfFire(const int& rateOfFire) { m_RateOfFire = rateOfFire; return this; }
	//	--> Set Twist Rate [ millimeters ]
	WeaponComponent*			SetBarrelTwistRate(const int& twistRate) { m_BarrelTwistRate = twistRate; return this; }
	WeaponComponent*			SetRoundsRemaining(const int& remaining) { m_RoundsRemaining = remaining; return this; }
	WeaponComponent*			SetRoundsPerMagazine(const int& roundsPerMag) { m_RoundsPerMagazine = roundsPerMag; return this; }
	WeaponComponent*			SetTimeSinceLastFired(const float& timeSinceLastFired) { m_TimeSinceLastFired = timeSinceLastFired; return this; }
	WeaponComponent*			SetProjectile(IProjectilePrefab* projectile) { if (m_ProjectileType) delete m_ProjectileType; m_ProjectileType = projectile; return this; }

	std::string					GetName(void) { return m_Name; }
	bool						IsActive(void) { return m_IsActive; }
	FiringMode					GetFiringMode(void) { return m_FiringMode; }
	int							GetRateOfFire(void) { return m_RateOfFire; }
	int							GetTwistRate(void) { return m_BarrelTwistRate; }
	IProjectilePrefab*			GetProjectile(void) { return m_ProjectileType; }
	int							GetRoundsRemaining(void) { return m_RoundsRemaining; }
	int							GetRoundsPerMagazine(void) { return m_RoundsPerMagazine; }
	float						GetTimeSinceLastFired(void) { return m_TimeSinceLastFired; }

private:
	std::string					m_Name;
	bool						m_IsActive;
	int							m_RateOfFire;			// Rounds-Per-Minute (RPM)
	FiringMode					m_FiringMode;				
	IProjectilePrefab*			m_ProjectileType;
	int							m_BarrelTwistRate;		// Millimeters
	int							m_RoundsRemaining;
	int							m_RoundsPerMagazine;
	float						m_TimeSinceLastFired;	// Milliseconds

};