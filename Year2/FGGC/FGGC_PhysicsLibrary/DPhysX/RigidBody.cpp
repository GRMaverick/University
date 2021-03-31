#include "RigidBody.h"

#define DPHYSX_DLL_EXPORT

DPHYSX_DLL RigidBody::RigidBody(void)
{
	mInverseMass = 0.0f;
	mSpeed = 0.0f;
	mRadius = 0.0f;
	mCoefRest = 0.0f;

	mExtents = Vector3(0.0f, 0.0f, 0.0f);
	mMoments = Vector3(0.0f, 0.0f, 0.0f);
	mEulerAngles = Vector3(0.0f, 0.0f, 0.0f);
	mNetForce = Vector3(0.0f, 0.0f, 0.0f);
	mVelocity = Vector3(0.0f, 0.0f, 0.0f);
	mAcceleration = Vector3(0.0f, 0.0f, 0.0f);
	mAngVelocity = Vector3(0.0f, 0.0f, 0.0f);
	mAngAcceleration = Vector3(0.0f, 0.0f, 0.0f);

	mInertia = Matrix3x3();
	mIeInverse = Matrix3x3();
	mInertiaInverse = Matrix3x3();

	mOrientation = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);

	mTransform = nullptr;
}
DPHYSX_DLL RigidBody::RigidBody(Transform* transform, float mass)
{
	mInverseMass = 1 / mass;
	mSpeed = 0.0f;
	mRadius = 0.0f;
	mCoefRest = 0.0f;

	mExtents = Vector3(0.0f, 0.0f, 0.0f);
	mMoments = Vector3(0.0f, 0.0f, 0.0f);
	mEulerAngles = Vector3(0.0f, 0.0f, 0.0f);
	mNetForce = Vector3(0.0f, 0.0f, 0.0f);
	mVelocity = Vector3(0.0f, 0.0f, 0.0f);
	mAcceleration = Vector3(0.0f, 0.0f, 0.0f);
	mAngVelocity = Vector3(0.0f, 0.0f, 0.0f);
	mAngAcceleration = Vector3(0.0f, 0.0f, 0.0f);

	mInertia = Matrix3x3();
	mIeInverse = Matrix3x3();
	mInertiaInverse = Matrix3x3();

	mOrientation = Quaternion();

	mTransform = transform;
}
DPHYSX_DLL RigidBody::~RigidBody(void)
{
	delete mTransform;
}

DPHYSX_DLL void RigidBody::Update(float deltaTime)
{
	if (!mIsScenery) 
	{
		this->UpdatePosition(deltaTime);
		this->ResetForce();
	}

	Vector3 rotation = GetTransform()->GetRotation();
	mOrientation = MakeQFromEulerAngles(rotation.x, rotation.y, rotation.z);
}
DPHYSX_DLL void RigidBody::UpdatePosition(float deltaTime)
{
	Vector3 k1, k2, k3, k4;

	mAcceleration = mNetForce / mInverseMass;

	k1 = mAcceleration * deltaTime;
	mAcceleration = (mNetForce + (k1 / 2)) / mInverseMass;

	k2 = mAcceleration * deltaTime;
	mAcceleration = (mNetForce + (k2 / 2)) / mInverseMass;

	k3 = mAcceleration * deltaTime;
	mAcceleration = mNetForce + k3;

	k4 = mAcceleration * deltaTime;
	mVelocity += (k1 + (k2 * 2) + (k3 * 2) + k4) / 6;

	Vector3 loPosition = mTransform->GetPosition();
	mTransform->SetLastPosition(loPosition);

	loPosition += mVelocity * deltaTime;

	mTransform->SetPosition(loPosition);
}
DPHYSX_DLL void RigidBody::ResetForce(void)
{
	mNetForce = Vector3(0.0f, 0.0f, 0.0f);
}

DPHYSX_DLL void RigidBody::SetMass(float mass) { mInverseMass = 1 / mass; }
DPHYSX_DLL void RigidBody::SetRadius(float radius) { mRadius = radius; }
DPHYSX_DLL void RigidBody::SetScenery(bool scenery) { mIsScenery = scenery; }
DPHYSX_DLL void RigidBody::SetRestituition(float rest) { mCoefRest = rest; }
DPHYSX_DLL void RigidBody::SetVelocity(Vector3 velocity) { mVelocity = velocity; }
DPHYSX_DLL void RigidBody::SetAcceleration(Vector3 acceleration) { mAcceleration = acceleration; }
DPHYSX_DLL void RigidBody::AddForce(Vector3 forceToAdd) { mNetForce += forceToAdd; }

DPHYSX_DLL void RigidBody::SetExtents(Vector3 extents) { mExtents = extents; }
DPHYSX_DLL void RigidBody::SetCollisionPoint(Vector3 point) { mCollisionPoint = point; }

DPHYSX_DLL float RigidBody::GetMass(void) const { return mInverseMass; }
DPHYSX_DLL float RigidBody::GetRadius(void) const { return mRadius; }
DPHYSX_DLL bool RigidBody::GetScenery(void) const { return mIsScenery; }
DPHYSX_DLL float RigidBody::GetRestituition(void) const { return mCoefRest; }

DPHYSX_DLL Vector3 RigidBody::GetExtents(void) const { return mExtents; }
DPHYSX_DLL Vector3 RigidBody::GetCollisionPoint(void) const { return mCollisionPoint; }
DPHYSX_DLL Vector3 RigidBody::GetAngularVelocity(void) const { return mAngVelocity; }
DPHYSX_DLL Vector3 RigidBody::GetVelocity(void) const { return mVelocity; }
DPHYSX_DLL Vector3 RigidBody::GetAcceleration(void) const { return mAcceleration; }
DPHYSX_DLL Vector3 RigidBody::GetNetForce(void) const { return mNetForce; }

DPHYSX_DLL Transform* RigidBody::GetTransform(void) const { return mTransform; }

DPHYSX_DLL Matrix3x3 RigidBody::GetInertia(void) const { return mInertia; }
DPHYSX_DLL Matrix3x3 RigidBody::GetInverseInertia(void) const { return mInertiaInverse; }

DPHYSX_DLL Quaternion RigidBody::GetOrientation(void) const { return mOrientation; }