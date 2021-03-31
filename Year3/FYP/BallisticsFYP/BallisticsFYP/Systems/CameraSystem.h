#pragma once

#include "ISystem.h"

class IEntity;
class IMediator;
class ICameraComponent;
class TransformComponent;
class FPSCameraComponent;

class CameraSystem : public ISystem
{
public:
	CameraSystem(void);
	~CameraSystem(void);

	void Receive(IMessage* pMessage);
	void RegisterMediator(std::shared_ptr<IMediator> mediator);
	
	void Update(DX::StepTimer const& timer) override;

private:
	std::shared_ptr<IMediator>							m_Mediator;
	std::string											m_ActiveCamera;
	std::string											m_FollowCameraTarget;

	void UpdateFPSCamera(FPSCameraComponent* pCamera, TransformComponent* pTransform);

};