#include "Particle.h"

#define DPHYSX_DLL_EXPORT

float Particle::mGravity = -9.81f;

DPHYSX_DLL Particle::Particle(void)
{
	mCoefRest = 0.0f;
	mIsScenery = false;
	mInverseMass = 0.0f;
	
	mTransform = nullptr;
	mBBox = Vector3(0.0f, 0.0f, 0.0f);

	mNetForce = Vector3(0.0f, 0.0f, 0.0f);
	mVelocity = Vector3(0.0f, 0.0f, 0.0f);
	mAcceleration = Vector3(0.0f, 0.0f, 0.0f);
}
DPHYSX_DLL Particle::Particle(Transform* transform, float mass)
{
	mCoefRest = 0.0f;
	mIsScenery = false;
	mInverseMass = 1 / mass;

	mTransform = transform;
	mBBox = Vector3(0.0f, 0.0f, 0.0f);

	mNetForce = Vector3(0.0f, 0.0f, 0.0f);
	mVelocity = Vector3(0.0f, 0.0f, 0.0f);
	mAcceleration = Vector3(0.0f, 0.0f, 0.0f);
}
DPHYSX_DLL Particle::~Particle(void)
{

}

DPHYSX_DLL void Particle::Update(float deltaTime)
{
	if (!mIsScenery) {
		this->UpdatePosition(deltaTime);
		this->ResetForce();
	}
}
DPHYSX_DLL void Particle::UpdatePosition(float deltaTime)
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
DPHYSX_DLL void Particle::ResetForce(void)
{
	mNetForce = Vector3(0.0f, 0.0f, 0.0f);
}


DPHYSX_DLL void Particle::SetMass(float mass) { mInverseMass = 1 / mass; }
DPHYSX_DLL void Particle::SetBBox(Vector3 bbox) { mBBox = bbox; }
DPHYSX_DLL void Particle::SetRadius(float radius) { mRadius = radius; }
DPHYSX_DLL void Particle::SetScenery(bool scenery) { mIsScenery = scenery; }
DPHYSX_DLL void Particle::SetRestituition(float rest) { mCoefRest = rest; }
DPHYSX_DLL void Particle::SetVelocity(Vector3 velocity) { mVelocity = velocity; }
DPHYSX_DLL void Particle::SetAcceleration(Vector3 acceleration) { mAcceleration = acceleration; }
DPHYSX_DLL void Particle::AddForce(Vector3 forceToAdd){	mNetForce += forceToAdd; }

DPHYSX_DLL float Particle::GetMass(void) const { return mInverseMass; }
DPHYSX_DLL float Particle::GetRadius(void) const { return mRadius; }
DPHYSX_DLL bool Particle::GetScenery(void) const { return mIsScenery; }
DPHYSX_DLL float Particle::GetRestituition(void) const { return mCoefRest; }
DPHYSX_DLL Vector3 Particle::GetVelocity(void) const { return mVelocity; }
DPHYSX_DLL Vector3 Particle::GetAcceleration(void) const { return mAcceleration; }
DPHYSX_DLL Vector3 Particle::GetNetForce(void) const { return mNetForce; }
DPHYSX_DLL Vector3 Particle::GetBBox(void) const { return mBBox; }
DPHYSX_DLL Transform* Particle::GetTransform(void) const { return mTransform; }