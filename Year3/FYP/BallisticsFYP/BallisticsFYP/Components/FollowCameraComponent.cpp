#include "pch.h"
#include "FollowCameraComponent.h"

FollowCameraComponent::FollowCameraComponent(void)
{

}
FollowCameraComponent::FollowCameraComponent(const Vector3& position, const Vector3& target, const Vector3& up, const float& wWidth, const float& wHeight, const float& nDepth, const float& fDepth)
{
	m_FarDepth = fDepth;
	m_NearDepth = nDepth;
	m_WindowWidth = wWidth;
	m_WindowHeight = wHeight;

	m_UpVector = XMVectorSet(up.x, up.y, up.z, 0.0f);
	m_TargetVector = XMVectorSet(target.x, target.y, target.z, 0.0f);
	m_PositionVector = XMVectorSet(position.x, position.y, position.z, 0.0f);

	Update();
}
FollowCameraComponent::~FollowCameraComponent(void)
{

}

void FollowCameraComponent::Update(void)
{
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(0.25f * XM_PI, m_WindowWidth / m_WindowHeight, m_NearDepth, m_FarDepth);
}
void FollowCameraComponent::UpdateViewMatrix(const Vector3& position, const Vector3& target, const Vector3& up)
{
	XMVECTOR camUp = XMVectorSet(up.x, up.y, up.z, 0.0f);
	XMVECTOR camTarget = XMVectorSet(target.x, target.y, target.z, 0.0f);
	XMVECTOR camPosition = XMVectorSet(position.x, position.y, position.z, 0.0f);

	m_ViewMatrix = XMMatrixLookAtLH(camPosition, camTarget, camUp);
}
void FollowCameraComponent::Reshape(const float& windowWidth, const float& windowHeight, const float& nearDepth, const float& farDepth)
{
	m_FarDepth = farDepth;
	m_NearDepth = nearDepth;
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;
}
