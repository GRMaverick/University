#include "pch.h"
#include "FPSCameraComponent.h"

FPSCameraComponent::FPSCameraComponent(void)
{

}

FPSCameraComponent::FPSCameraComponent(const Vector3& position, const Vector3& at, const Vector3& up, const float& windowWidth, const float& windowHeight, const float& nearDepth, const float& farDepth)
{
	mWindowWidth = windowWidth;
	mWindowHeight = windowHeight;
	mNearDepth = nearDepth;
	mFarDepth = farDepth;

	mDefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	mDefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	mCamPosition = XMVectorSet(position.x, position.y, position.z, 0.0f);
	mCamTarget = XMVectorSet(at.x, at.y, at.z, 0.0f);
	mCamUp = XMVectorSet(up.x, up.y, up.z, 0.0f);

	mMoveLeftRight = 0.0f;
	mMoveBackForward = 0.0f;

	mCamYaw = 0.0f;
	mCamPitch = 0.0f;

	Update();
}
FPSCameraComponent::~FPSCameraComponent(void)
{
}

void FPSCameraComponent::Update(void)
{
	mCamProjection = XMMatrixPerspectiveFovLH(0.25f * XM_PI, mWindowWidth / mWindowHeight, mNearDepth, mFarDepth);
}
void FPSCameraComponent::UpdateViewMatrix(Vector3 position, Vector3 target, Vector3 up)
{	
	mMoveLeftRight = 0.0f;
	mMoveBackForward = 0.0f;

	XMVECTOR camPosition = XMVectorSet(position.x, position.y, position.z, 0.0f);
	XMVECTOR camTarget = XMVectorSet(target.x, target.y, target.z, 0.0f);
	XMVECTOR camUp = XMVectorSet(up.x, up.y, up.z, 0.0f);

	mCamView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
}

void FPSCameraComponent::Reshape(const float& windowWidth, const float& windowHeight, const float& nearDepth, const float& farDepth)
{
	mWindowWidth = windowWidth;
	mWindowHeight = windowHeight;
	mNearDepth = nearDepth;
	mFarDepth = farDepth;
}

void FPSCameraComponent::Rotate(const float& pitch, const float& yaw)
{
	mCamPitch += pitch;
	mCamYaw += yaw;
}