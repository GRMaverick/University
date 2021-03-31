#include "pch.h"
#include "StaticCameraComponent.h"

StaticCameraComponent::StaticCameraComponent(void)
{
	m_Up = Vector3();
	m_Target = Vector3();
	m_Position = Vector3();

	m_FarDepth = 0;
	m_NearDepth = 0;
	m_WindowWidth = 0;
	m_WindowHeight = 0;

	m_View = XMFLOAT4X4();
	m_Projection = XMFLOAT4X4();
}
StaticCameraComponent::StaticCameraComponent(const Vector3& position, const Vector3& target, const Vector3& up, const float& windowWidth, const float& windowHeight, const float& nearDepth, const float& farDepth)
{
	m_Up = up;
	m_Target = target;
	m_Position = position;

	m_FarDepth = farDepth;
	m_NearDepth = nearDepth;
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;

	Update();
}
StaticCameraComponent::~StaticCameraComponent(void)
{
}

void StaticCameraComponent::Update(void)
{
	XMFLOAT4 up = XMFLOAT4(m_Up.x, m_Up.y, m_Up.z, 1.0f);
	XMFLOAT4 target = XMFLOAT4(m_Target.x, m_Target.y, m_Target.z, 1.0f);
	XMFLOAT4 position = XMFLOAT4(m_Position.x, m_Position.y, m_Position.z, 1.0f);

	XMVECTOR upVector = XMLoadFloat4(&up);
	XMVECTOR targetVector = XMLoadFloat4(&target);
	XMVECTOR positionVector = XMLoadFloat4(&position);

	XMStoreFloat4x4(&m_View, XMMatrixLookAtLH(positionVector, targetVector, upVector));
	XMStoreFloat4x4(&m_Projection, XMMatrixPerspectiveFovLH(0.25f * XM_PI, m_WindowWidth / m_WindowHeight, m_NearDepth, m_FarDepth));
}

void StaticCameraComponent::Reshape(const float& windowWidth, const float& windowHeight, const float& nearDepth, const float& farDepth)
{
	m_FarDepth = farDepth;
	m_NearDepth = nearDepth;
	m_WindowWidth = windowWidth;
	m_WindowHeight = windowHeight;
}

void StaticCameraComponent::SetUp(const Vector3& up)
{ 
	m_Up = up; 
}
void StaticCameraComponent::SetTarget(const Vector3& target)
{ 
	m_Target = target;
}
void StaticCameraComponent::SetPosition(const Vector3& position)
{ 
	m_Position = position;
}

void StaticCameraComponent::SetFarDepth(const float& farDepth)
{
	m_FarDepth = farDepth;
}
void StaticCameraComponent::SetNearDepth(const float& nearDepth)
{
	m_NearDepth = nearDepth;
}
void StaticCameraComponent::SetWindowWidth(const float& windowWidth)
{
	m_WindowWidth = windowWidth;
}
void StaticCameraComponent::SetWindowHeight(const float& windowHeight)
{
	m_WindowHeight = windowHeight;
}

XMVECTOR StaticCameraComponent::GetUp(void)
{ 
	return XMLoadFloat3(&XMFLOAT3(m_Up.x, m_Up.y, m_Up.z));
}
XMVECTOR StaticCameraComponent::GetLookAt(void)
{
	return XMLoadFloat3(&XMFLOAT3(m_Target.x, m_Target.y, m_Target.z));
}
XMVECTOR StaticCameraComponent::GetPosition(void)
{
	return XMLoadFloat3(&XMFLOAT3(m_Position.x, m_Position.y, m_Position.z));
}

XMMATRIX StaticCameraComponent::GetView(void)
{ 
	return XMLoadFloat4x4(&m_View);
}
XMMATRIX StaticCameraComponent::GetProjection(void)
{
	return XMLoadFloat4x4(&m_Projection);
}

XMFLOAT4X4 StaticCameraComponent::GetViewProjection(void)
{
	XMMATRIX view = XMLoadFloat4x4(&m_View);
	XMMATRIX projection = XMLoadFloat4x4(&m_Projection);

	XMFLOAT4X4 viewProj;
	XMStoreFloat4x4(&viewProj, view * projection);

	return viewProj;
}

bool StaticCameraComponent::IsActive(void)
{
	return m_IsActive;
}