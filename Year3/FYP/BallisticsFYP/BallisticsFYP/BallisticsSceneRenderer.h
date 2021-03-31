#pragma once

#include <vector>
#include <memory>

#include "..\Common\StepTimer.h"
#include "..\Common\DeviceResources.h"

#include "ISystem.h"
#include "IMediator.h"

namespace BallisticsFYP
{
	class BallisticsSceneRenderer
	{
	public:
		BallisticsSceneRenderer(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~BallisticsSceneRenderer(void);

		void CreateDeviceDependentResources(void);
		void CreateWindowSizeDependentResources(void);

		void ReleaseDeviceDependentResources(void);

		void Update(DX::StepTimer const& timer);
	
	private:
		void InitialiseEntities(void);
		void InitialiseComponents(void);
		void InitialiseSystems(void);
		void InitialiseControls(void);

		bool																m_IsFPSActive;
		bool																m_BulletTimeActivated;

		std::vector<ISystem*>									m_Systems;
		std::shared_ptr<IMediator>						m_pMediator;
		std::shared_ptr<DX::DeviceResources>		m_DeviceResources;
	};
}