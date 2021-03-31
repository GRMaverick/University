#include "PlaneParticle.h"

PlaneParticle::PlaneParticle(Transform* transform, float mass) : RigidBody(transform, mass)
{
	mGearRatio = 10.0f;
	mWheelSpeed = 1.0f;
	mSpeed = 0.0f;
	mWheelRadius = 10.0f;
	mMaxSpeed = 0.0f;

	mPlaneVelocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mPlaneDirection = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void PlaneParticle::Update(float deltaTime)
{
	this->CalculateWheelSpeed();
	this->CalculateThrust(deltaTime);
	this->CalculateVelocity();
	
	ParticleModel::Update(deltaTime);
}

void PlaneParticle::TruncateSpeed()
{
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;
}
void PlaneParticle::CalculateVelocity()
{
	mPlaneVelocity = mPlaneDirection * mThrust;
}
void PlaneParticle::CalculateWheelSpeed()
{
	this->TruncateSpeed();

	mWheelSpeed = mSpeed / mGearRatio;
}
void PlaneParticle::CalculateThrust(float deltaTime)
{
	mThrust = ((mWheelSpeed * 60) * 2 * XM_PI * mWheelRadius) / deltaTime;
}