#pragma once

namespace DX
{
	class DeviceResources;
}

class IProjectilePrefab
{
public:
	virtual ~IProjectilePrefab(void) { };	
	virtual bool Initialise(std::shared_ptr<DX::DeviceResources> deviceResources) = 0;

	virtual IProjectilePrefab* Clone(void) = 0;
	virtual IProjectilePrefab* Clone(const std::string& name) = 0;
	
	std::string GetType(void) { return m_ProjectileType; }

protected:
	std::string m_ProjectileType;
};