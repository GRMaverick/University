#pragma once

#include <windows.h>

#include "ICameraComponent.h"
#include "Vector3.h"

using namespace DirectX;
using namespace Mathematics::Structures;

class FPSCameraComponent : public ICameraComponent
{
public:
	FPSCameraComponent(void);
	FPSCameraComponent(const Vector3& position, const Vector3& at, const Vector3& up, const float& windowWidth,
		const float& windowHeight, const float& nearDepth, const float& farDepth);
	~FPSCameraComponent();

	void SetOwnerName(const std::string& name) { IComponent::SetOwnerName(name); }
	std::string GetOwnerName(void) { return IComponent::GetOwnerName(); }
		
	void Update(void);
	void UpdateViewMatrix(Vector3 position, Vector3 target, Vector3 up);

	void SetActive(bool isActive) { mIsActive = isActive; }

	void Strafe(const float& amount) override { mMoveLeftRight += amount; }
	void Advance(const float& amount) override { mMoveBackForward += amount; }
	void Rotate(const float& pitch, const float& yaw) override;

	float GetPitch(void) override { return mCamPitch; }
	float GetYaw(void) override { return mCamYaw; }
	float GetStrafe(void) { return mMoveLeftRight; }
	float GetAdvance(void) { return mMoveBackForward; }

	XMVECTOR GetUp(void) override { return mCamUp; }
	XMVECTOR GetPosition() override { return mCamPosition; }
	XMVECTOR GetLookAt(void) override { return mCamTarget; }

	XMMATRIX GetView(void) override { return mCamView; }
	XMMATRIX GetProjection(void) override { return mCamProjection; }

	void Reshape(const float& windowWidth, const float& windowHeight, const float& nearDepth, const float& farDepth) override;

	bool IsActive(void) { return mIsActive; }

private:			
	bool mIsActive;
	float mWindowWidth;
	float mWindowHeight;
	float mNearDepth;
	float mFarDepth;

	XMMATRIX mCamView;
	XMMATRIX mCamProjection;

	XMVECTOR mDefaultForward;
	XMVECTOR mDefaultRight;
	XMVECTOR mCamForward;
	XMVECTOR mCamRight;

	XMVECTOR mCamTarget;
	XMVECTOR mCamUp;
	XMVECTOR mCamPosition;

	XMMATRIX mCamRotationMatrix;

	float mMoveLeftRight;
	float mMoveBackForward;

	float mCamYaw;
	float mCamPitch;
};
