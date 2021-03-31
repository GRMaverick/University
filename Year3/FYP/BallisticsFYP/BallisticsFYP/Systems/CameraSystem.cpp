
#include "pch.h"
#include <iostream>
#include <DirectXMath.h>

#include "IEntity.h"
#include "IMediator.h"
#include "CameraSystem.h"

#include "SetActiveCamera.h"
#include "RequestActiveCamera.h"
#include "ActiveCameraMessage.h"
#include "UpdateFollowMessage.h"
#include "GetFollowTargetMessage.h"

#include "EntityManager.h"
#include "ComponentManager.h"
#include "DelegateFactory.h"

#include "TransformComponent.h"
#include "FPSCameraComponent.h"
#include "FollowCameraComponent.h"
#include "StaticCameraComponent.h"

CameraSystem::CameraSystem(void)
{
	m_Mediator = nullptr;
}
CameraSystem::~CameraSystem(void)
{

}

void CameraSystem::RegisterMediator(std::shared_ptr<IMediator> mediator)
{
	m_Mediator = mediator;
	m_Mediator->RegisterReceiveCallback(DELEGATE(&CameraSystem::Receive, this));
}
void CameraSystem::Receive(IMessage* pMessage)
{	
	if (RequestActiveCamera* pRequestMessage = dynamic_cast<RequestActiveCamera*>(pMessage))
	{
		ActiveCameraMessage* pActiveCameraMessage = new ActiveCameraMessage(m_ActiveCamera);
		m_Mediator->Send(pActiveCameraMessage);
		delete pActiveCameraMessage;
	}
	if (SetActiveCamera* pSetActiveMessage = dynamic_cast<SetActiveCamera*>(pMessage))
	{
		for (std::string entity : EntitiesManager->GetEntities())
		{
			for (IComponent* component : ComponentsManager->GetAllComponentsForEntity(entity))
			{
				if (ICameraComponent* cam = dynamic_cast<ICameraComponent*>(component))
				{
					std::string target = pSetActiveMessage->GetNewActiveCamera();
					if (entity != target)
					{
						cam->SetActive(false);
					}
					else
					{
						cam->SetActive(true);
						m_ActiveCamera = target;
					}
				}
			}
		}
	}
	if (UpdateFollowMessage* pFollowMessage = dynamic_cast<UpdateFollowMessage*>(pMessage))
	{
		for (std::string entity : EntitiesManager->GetEntities())
		{
			for (IComponent* pComponent : ComponentsManager->GetAllComponentsForEntity(entity))
			{
				if (FollowCameraComponent* pFollowCamera = dynamic_cast<FollowCameraComponent*>(pComponent))
				{
					m_FollowCameraTarget = pFollowMessage->GetTargetName();
					pFollowCamera->UpdateViewMatrix(pFollowMessage->GetTarget() + pFollowMessage->GetOffset(), pFollowMessage->GetTarget(), Vector3(0.0f, 1.0f, 0.0f));
				}
			}
		}
	}
	if (GetFollowTargetMessage* pFollowMessage = dynamic_cast<GetFollowTargetMessage*>(pMessage))
	{
		SendFollowTargetMessage* pSendTargetMessage = new SendFollowTargetMessage(m_FollowCameraTarget);
		m_Mediator->Send(pSendTargetMessage);
		delete pSendTargetMessage;
	}
}

void CameraSystem::Update(DX::StepTimer const& timer)
{
	std::vector<ICameraComponent*>	cameraComponents;

	for (std::string entity : EntitiesManager->GetEntities())
	{
		TransformComponent* pTransform = nullptr;
		FPSCameraComponent* pFPSCamera = nullptr;
		FollowCameraComponent* pFollowCamera = nullptr;

		for (IComponent* component : ComponentsManager->GetAllComponentsForEntity(entity))
		{
			if (ICameraComponent* pTemp = dynamic_cast<ICameraComponent*>(component))
			{
				cameraComponents.push_back(pTemp);
			}
			if (FPSCameraComponent* pTemp = dynamic_cast<FPSCameraComponent*>(component))
			{
				pFPSCamera = pTemp;
			}
			if (TransformComponent* pTemp = dynamic_cast<TransformComponent*>(component))
			{
				pTransform = pTemp;
			}
		}

		if (pFPSCamera && pTransform)
		{
			UpdateFPSCamera(pFPSCamera, pTransform);
			pTransform->Update();
		}
	}

	for (ICameraComponent* camera : cameraComponents)
	{
		camera->Update();
	}
}
void CameraSystem::UpdateFPSCamera(FPSCameraComponent* pCamera, TransformComponent* pTransform)
{
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(pCamera->GetPitch(), pCamera->GetYaw(), 0.0f);
	
	XMVECTOR camTarget = XMVector3TransformCoord(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), camRotationMatrix);
	camTarget = XMVector3Normalize(camTarget);

	XMFLOAT3 forward = XMFLOAT3(pTransform->GetForward().x, pTransform->GetForward().y, pTransform->GetForward().z);
	XMStoreFloat3(&forward, camTarget);
	pTransform->SetForward(forward.x, forward.y, forward.z);

	float xx = asin(-forward.y) * (180 / 3.14159);
	float yy = (float)((atan2(forward.z, forward.x) / XM_PI) * 180.0f);
	float zz = 0.0f;

	if (yy < 0.0f)
		yy += 360.0f;

	pTransform->SetRotation(xx, -yy - 270.0f, zz);
	
	XMMATRIX rotationYTemp;
	rotationYTemp = XMMatrixRotationY(pCamera->GetYaw());

	XMVECTOR camRight = XMVector3TransformCoord(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), rotationYTemp);
	XMVECTOR camUp = XMVector3TransformCoord(XMVectorSet(pTransform->GetUp().x, pTransform->GetUp().y, pTransform->GetUp().z, 0.0f), rotationYTemp);
	XMVECTOR camForward = XMVector3TransformCoord(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotationYTemp);

	XMFLOAT3 cameraUp = XMFLOAT3();
	XMStoreFloat3(&cameraUp, camUp);
	pTransform->SetUp(cameraUp.x, cameraUp.y, cameraUp.z);

	XMFLOAT3 camPosition = XMFLOAT3(pTransform->GetPosition().x, pTransform->GetPosition().y, pTransform->GetPosition().z);
	XMVECTOR camPosVector = XMLoadFloat3(&camPosition);

	camPosVector += pCamera->GetStrafe()*camRight;
	camPosVector += pCamera->GetAdvance()*camForward;

	XMStoreFloat3(&camPosition, camPosVector);
	pTransform->SetPosition(camPosition.x, camPosition.y, camPosition.z);

	camTarget = camPosVector + camTarget;

	XMStoreFloat3(&forward, camTarget);
	
	pCamera->UpdateViewMatrix(pTransform->GetPosition(), Vector3(forward.x, forward.y, forward.z), pTransform->GetUp());
}