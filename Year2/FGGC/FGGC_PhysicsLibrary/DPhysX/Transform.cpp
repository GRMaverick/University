#include "Transform.h"

#define DPHYSX_DLL_EXPORT

DPHYSX_DLL Transform::Transform(void)
{
	mParent = nullptr;
	mWorld = XMFLOAT4X4();

	mPreviousPosition = Vector3(0.0f, 0.0f, 0.0f);
	mPosition = Vector3(0.0f, 0.0f, 0.0f);
	mRotation = Vector3(0.0f, 0.0f, 0.0f);
	mScale = Vector3(0.0f, 0.0f, 0.0f);
}
DPHYSX_DLL Transform::~Transform(void)
{
	if (mParent != nullptr)
	{
		delete mParent;
		mParent = 0;
	}
}

DPHYSX_DLL void Transform::Update(float deltaTime)
{
	XMMATRIX translation = XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z);
	XMMATRIX rotation = XMMatrixRotationQuaternion(XMQuaternionRotationRollPitchYaw(mRotation.x, mRotation.y, mRotation.z));
	XMMATRIX scale = XMMatrixScaling(mScale.x, mScale.y, mScale.z);

	XMStoreFloat4x4(&mWorld, scale * rotation * translation);

	if (mParent != nullptr)
		XMStoreFloat4x4(&mWorld, this->GetWorldMatrix() * mParent->GetWorldMatrix());
}

DPHYSX_DLL void Transform::SetParent(Transform* transform) { mParent = transform; }
DPHYSX_DLL void Transform::SetWorld(XMFLOAT4X4 world) { mWorld = world; }
DPHYSX_DLL void Transform::SetPosition(Vector3 position) { mPosition = position; }
DPHYSX_DLL void Transform::SetPosition(float x, float y, float z) { mPosition = Vector3(x, y, z); }
DPHYSX_DLL void Transform::SetRotation(Vector3 rotation) { mRotation = rotation; }
DPHYSX_DLL void Transform::SetRotation(float x, float y, float z) { mRotation = Vector3(x, y, z); }
DPHYSX_DLL void Transform::SetScale(Vector3 scale) { mScale = scale; }
DPHYSX_DLL void Transform::SetScale(float x, float y, float z) { mScale = Vector3(x, y, z); }
DPHYSX_DLL void Transform::SetLastPosition(Vector3 lPosition) { mPreviousPosition = lPosition; }
DPHYSX_DLL void Transform::SetLastPosition(float x, float y, float z) { mPreviousPosition = Vector3(x, y, z); }

DPHYSX_DLL Transform* Transform::GetParent(void) const { return mParent; }
DPHYSX_DLL XMMATRIX Transform::GetWorldMatrix(void) const { return XMLoadFloat4x4(&mWorld); }
DPHYSX_DLL Vector3 Transform::GetPosition(void) const { return mPosition; }
DPHYSX_DLL Vector3 Transform::GetRotation(void) const { return mRotation; }
DPHYSX_DLL Vector3 Transform::GetScale(void) const { return mScale; }
DPHYSX_DLL Vector3 Transform::GetLastPosition(void) const { return mPreviousPosition; }