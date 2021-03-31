#include "pch.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(void)
{
	m_Parent = nullptr;
	m_World = XMFLOAT4X4();

	m_Up = Vector3(0.0f, 1.0f, 0.0f);
	m_Right = Vector3(1.0f, 0.0f, 0.0f);
	m_Forward = Vector3(0.0f, 0.0f, 1.0f);

	m_Scale = Vector3(1.0f, 1.0f, 1.0f);
	m_Position = Vector3(0.0f, 0.0f, 0.0f);
	m_Rotation = Vector3(0.0f, 0.0f, 0.0f);
	m_PreviousPosition = Vector3(0.0f, 0.0f, 0.0f);
}
TransformComponent::~TransformComponent(void)
{
	if (m_Parent != nullptr)
	{
		delete m_Parent;
		m_Parent = nullptr;
	}
}

void TransformComponent::Update()
{
	XMMATRIX scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	XMMATRIX translation = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMMATRIX rotation = XMMatrixRotationQuaternion(XMQuaternionRotationRollPitchYaw(XMConvertToRadians(m_Rotation.x), XMConvertToRadians(m_Rotation.y), XMConvertToRadians(m_Rotation.z)));
	
	if (m_Parent)
	{
		m_Forward = m_Parent->GetForward();
	}

	XMStoreFloat4x4(&m_World, scale * rotation * translation);

	if (m_Parent != nullptr)
		XMStoreFloat4x4(&m_World, this->GetWorldMatrix() * m_Parent->GetWorldMatrix());
}

TransformComponent* TransformComponent::SetUp(Vector3 up) { m_Up = up; return this; }
TransformComponent* TransformComponent::SetUp(float x, float y, float z) { m_Up = Vector3(x, y, z); return this; }

TransformComponent* TransformComponent::SetScale(Vector3 scale) { m_Scale = scale; return this; }
TransformComponent* TransformComponent::SetScale(float x, float y, float z) { m_Scale = Vector3(x, y, z); return this; }

TransformComponent* TransformComponent::SetForward(Vector3 forward) { m_Forward = forward; return this; }
TransformComponent* TransformComponent::SetForward(float x, float y, float z) { m_Forward = Vector3(x, y, z); return this; }

TransformComponent* TransformComponent::SetPosition(Vector3 position) { m_Position = position; return this; }
TransformComponent* TransformComponent::SetPosition(float x, float y, float z) { m_Position = Vector3(x, y, z); return this; }

TransformComponent* TransformComponent::SetRotation(Vector3 rotation) { m_Rotation = rotation; return this; }
TransformComponent* TransformComponent::SetRotation(float x, float y, float z) { m_Rotation = Vector3(x, y, z); return this; }

TransformComponent* TransformComponent::SetLastPosition(Vector3 lPosition) { m_PreviousPosition = lPosition; return this; }
TransformComponent* TransformComponent::SetLastPosition(float x, float y, float z) { m_PreviousPosition = Vector3(x, y, z); return this; }

TransformComponent* TransformComponent::SetParent(TransformComponent* transform) { m_Parent = transform; return this; }
TransformComponent* TransformComponent::SetWorld(XMFLOAT4X4 world) { m_World = world; return this; }

TransformComponent* TransformComponent::GetParent(void) const { return m_Parent; }
XMMATRIX TransformComponent::GetWorldMatrix(void) const { return XMLoadFloat4x4(&m_World); }

Vector3 TransformComponent::GetUp(void) const { return m_Up; }
Vector3 TransformComponent::GetRight(void) const { return m_Right; }
Vector3 TransformComponent::GetScale(void) const { return m_Scale; }
Vector3 TransformComponent::GetPosition(void) const { return m_Position; }
Vector3 TransformComponent::GetForward(void) const { return m_Forward; }
Vector3 TransformComponent::GetRotation(void) const { return m_Rotation; }
Vector3 TransformComponent::GetLastPosition(void) const { return m_PreviousPosition; }