#pragma once

#include <string>
#include <memory>

#include "IProjectilePrefab.h"

class M43_762_39 : public IProjectilePrefab
{
public:
	// Mass in Kilograms
	static float Mass;

	// Frontal Area in square-meters
	static float FrontalArea;

	// Muzzle Velocity in meters-per-second
	static float MuzzleVelocity;

	// Dimensionless Drag Coefficient
	static float DragCoefficient;

	M43_762_39(void);
	M43_762_39(const std::string& name);
	~M43_762_39(void);

	IProjectilePrefab* Clone(void) override;
	IProjectilePrefab* Clone(const std::string& name) override;

	std::string GetType(void) { return IProjectilePrefab::GetType(); }

private:
	std::string m_Name;

	bool Initialise(std::shared_ptr<DX::DeviceResources> deviceResources) override;
	bool InitialisePhysics(void);
	bool InitialiseCollision(void);
	bool InitialiseProjectile(void);
	bool InitialiseTransform(void);
	bool InitialiseRender(std::shared_ptr<DX::DeviceResources> deviceResources);
	bool InitialiseLineRender(std::shared_ptr<DX::DeviceResources> deviceResources);
};