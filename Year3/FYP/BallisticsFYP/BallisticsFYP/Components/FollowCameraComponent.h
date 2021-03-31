#pragma once

#include "Vector3.h"
#include "ICameraComponent.h"

using namespace DirectX;
using namespace Mathematics::Structures;

class FollowCameraComponent : public ICameraComponent
{
public:
	FollowCameraComponent(void);
	FollowCameraComponent(const Vector3& position, const Vector3& target, const Vector3& up, const float& wWidth, const float& wHeight, const float& nDepth, const float& fDepth);
	~FollowCameraComponent(void);

	void		SetOwnerName(const std::string& name) { IComponent::SetOwnerName(name); }
	std::string GetOwnerName(void) { return IComponent::GetOwnerName(); }

	void		Update(void);
	void		UpdateViewMatrix(const Vector3& position, const Vector3& target, const Vector3& up);

	void		Reshape(const float& windowWidth, const float& windowHeight, const float& nearDepth, const float& farDepth) override;

	void		SetActive(bool isActive) { m_IsActive = isActive; }
	bool		IsActive(void) override { return m_IsActive; }

	void		Strafe(const float& amount) override { }
	void		Advance(const float& amount) override { }
	void		Rotate(const float& pitch, const float& yaw) { } 

	float		GetPitch(void) override { return float(); }
	float		GetYaw(void) override { return float(); }
	float		GetStrafe(void) { return float(); }
	float		GetAdvance(void) { return float(); }

	XMVECTOR	GetUp(void) override { return m_UpVector; }
	XMVECTOR	GetLookAt(void) override { return m_TargetVector; }
	XMVECTOR	GetPosition(void) override { return m_PositionVector; }

	XMMATRIX	GetView(void) override { return m_ViewMatrix; }
	XMMATRIX	GetProjection(void) override { return m_ProjectionMatrix; }

private:
	bool		m_IsActive;
	float		m_FarDepth;
	float		m_NearDepth;
	float		m_WindowWidth;
	float		m_WindowHeight;

	XMVECTOR	m_UpVector;
	XMVECTOR	m_TargetVector;
	XMVECTOR	m_PositionVector;

	XMMATRIX	m_ViewMatrix;
	XMMATRIX	m_ProjectionMatrix;
};