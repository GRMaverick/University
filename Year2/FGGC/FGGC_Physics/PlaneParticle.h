#pragma once

#include "Structure.h"
#include "RigidBody.h"
#include "ParticleComponent.h"

class PlaneParticle : public RigidBody
{
public:
	PlaneParticle(Transform* transform, float mass);
	~PlaneParticle() { ParticleModel::~ParticleModel(); }

	void Update(float deltaTime);
	void TruncateSpeed();

	inline void AddSpeed(float speed) { mSpeed += speed; this->TruncateSpeed(); }

	inline void SetSpeed(float speed) { mSpeed = speed; }
	inline void SetMaxSpeed(float speed) { mMaxSpeed = speed; }
	inline void SetPlaneDirection(XMFLOAT3 planeDirection) { mPlaneDirection = planeDirection; }
	inline void SetPlaneVelocity(XMFLOAT3 planeVelocity) { mPlaneVelocity = planeVelocity; }

	inline float GetSpeed() const { return mSpeed; }
	inline float GetMaxSpeed() const { return mMaxSpeed; }
	inline XMFLOAT3 GetPlaneDirection() const { return mPlaneDirection; }
	inline XMFLOAT3 GetPlaneVelocity() const { return mPlaneVelocity; }
	
private:
	float				mWheelRadius;
	float				mWheelSpeed;
	int				mGearRatio;
	float				mSpeed;
	float				mMaxSpeed;
	float				mThrust;

	XMFLOAT3	mPlaneVelocity;
	XMFLOAT3	mPlaneDirection;

	void CalculateVelocity();
	void CalculateWheelSpeed();
	void CalculateThrust(float deltaTime);
};