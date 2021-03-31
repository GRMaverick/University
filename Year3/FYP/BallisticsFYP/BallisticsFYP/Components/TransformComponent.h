#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

#include "IComponent.h"
#include "Vector3.h"

using namespace std;
using namespace DirectX;
using namespace Mathematics::Structures;

class TransformComponent : public IComponent
{
public:
	TransformComponent(void);
	~TransformComponent(void);

	void SetOwnerName(const std::string& name) { IComponent::SetOwnerName(name); }
	std::string GetOwnerName(void) { return IComponent::GetOwnerName(); }

	void Update();

	TransformComponent* SetParent(TransformComponent* transform);

	TransformComponent* SetUp(Vector3 up);
	TransformComponent* SetUp(float x, float y, float z);
	TransformComponent* SetScale(Vector3 scale);
	TransformComponent* SetScale(float x, float y, float z);
	TransformComponent* SetPosition(Vector3 position);
	TransformComponent* SetPosition(float x, float y, float z);
	TransformComponent* SetForward(Vector3 forward);
	TransformComponent* SetForward(float x, float y, float z);
	TransformComponent* SetRotation(Vector3 rotation);
	TransformComponent* SetRotation(float x, float y, float z);
	TransformComponent* SetLastPosition(Vector3 lPosition);
	TransformComponent* SetLastPosition(float x, float y, float z);

	TransformComponent* SetWorld(XMFLOAT4X4 world);

	Vector3 GetUp(void) const;
	Vector3 GetRight(void) const;
	Vector3 GetScale(void) const;
	Vector3 GetPosition(void) const;
	Vector3 GetForward(void) const;
	Vector3 GetRotation(void) const;
	Vector3 GetLastPosition(void) const;

	XMMATRIX GetWorldMatrix(void) const;

	TransformComponent* GetParent(void) const;

private:
	Vector3 m_Up;
	Vector3 m_Right;
	Vector3 m_Scale;
	Vector3 m_Position;
	Vector3 m_Forward;
	Vector3 m_Rotation;
	Vector3 m_PreviousPosition;

	XMFLOAT4X4 m_World;

	TransformComponent* m_Parent;
};
