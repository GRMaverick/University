#pragma once

#include <string>
#include <memory>

#include "IProjectilePrefab.h"

class Parabellum9x19mm : public IProjectilePrefab
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

	// Dimensionless Lift Coefficient
	static float LiftCoefficient;

	// Length in meters
	static float Length;

	Parabellum9x19mm(void);
	Parabellum9x19mm(const std::string& name);
	~Parabellum9x19mm(void);

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