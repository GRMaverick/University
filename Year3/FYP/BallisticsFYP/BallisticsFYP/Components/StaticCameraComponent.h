#pragma once

#include "Vector3.h"
#include <DirectXMath.h>

#include "ICameraComponent.h"

using namespace DirectX;
using namespace Mathematics::Structures;

class StaticCameraComponent : public ICameraComponent
{
public:
	StaticCameraComponent(void);
	StaticCameraComponent(const Vector3& position, const Vector3& at, const Vector3& up, const float& windowWidth, const float& windowHeight, const float& nearDepth, const float& farDepth);
	~StaticCameraComponent(void);

	void SetOwnerName(const std::string& name) { IComponent::SetOwnerName(name); }
	std::string GetOwnerName(void) { return IComponent::GetOwnerName(); }
	
	void Update(void);
	void Reshape(const float& windowWidth, const float& windowHeight, const float& nearDepth, const float& farDepth);

	void Strafe(const float& amount) { } ;
	void Advance(const float& amount) { } ;
	void Rotate(const float& pitch, const float& yaw) { };

	void SetUp(const Vector3& up);
	void SetTarget(const Vector3& target);
	void SetPosition(const Vector3& position);

	void SetFarDepth(const float& farDepth);
	void SetNearDepth(const float& nearDepth);
	void SetWindowHeight(const float& windowHeight);
	void SetWindowWidth(const float& windowWidth);

	XMVECTOR GetUp(void) override;
	XMVECTOR GetLookAt(void) override;
	XMVECTOR GetPosition(void) override;

	float GetPitch(void) override { return 0.0f;  }
	float GetYaw(void) override { return 0.0f; }

	XMMATRIX GetView(void) override;
	XMMATRIX GetProjection(void) override;
	XMFLOAT4X4 GetViewProjection(void);

	bool IsActive(void) override;
	void SetActive(bool isActive) override { m_IsActive = isActive; }

private:
	bool m_IsActive;

	Vector3 m_Up;
	Vector3 m_Target;
	Vector3 m_Position;

	float m_FarDepth;
	float m_NearDepth;
	float m_WindowWidth;
	float m_WindowHeight;

	XMFLOAT4X4 m_View;
	XMFLOAT4X4 m_Projection;
};
