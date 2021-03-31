#ifndef __DPHYSX_RIGIDBODY__
#define __DPHYSX_RIGIDBODY__

#ifndef DPHYSX_DLL_EXPORT
#define DPHYSX_DLL __declspec(dllexport)
#else
#define DPHYSX_DLL __declspec(dllimport)
#endif

#include <vector>

#include "Particle.h"

class RigidBody
{
public:
	Vector3 mEdges[12];
	Vector3 mVertices[8];

	DPHYSX_DLL RigidBody(void);
	DPHYSX_DLL RigidBody(Transform* transform, float mass);
	DPHYSX_DLL ~RigidBody(void);

	DPHYSX_DLL void Update(float deltaTime);

	DPHYSX_DLL void SetMass(float mass);
	DPHYSX_DLL void SetRadius(float radius);
	DPHYSX_DLL void SetRestituition(float rest);
	DPHYSX_DLL void SetScenery(bool isScenery);
	DPHYSX_DLL void SetVelocity(Vector3 velocity);
	DPHYSX_DLL void SetAcceleration(Vector3 acceleration);
	DPHYSX_DLL void AddForce(Vector3 forceToAdd);

	DPHYSX_DLL float GetMass(void) const;
	DPHYSX_DLL float GetRadius(void) const;
	DPHYSX_DLL bool GetScenery(void) const;
	DPHYSX_DLL float GetRestituition(void) const;

	DPHYSX_DLL Vector3 GetVelocity(void) const;
	DPHYSX_DLL Vector3 GetAcceleration(void) const;
	DPHYSX_DLL Vector3 GetNetForce(void) const;

	DPHYSX_DLL Transform* GetTransform(void) const;

	DPHYSX_DLL Vector3 GetExtents(void) const;
	DPHYSX_DLL Vector3 GetCollisionPoint(void) const;
	DPHYSX_DLL Vector3 GetAngularVelocity(void) const;

	DPHYSX_DLL void SetExtents(Vector3 extents);
	DPHYSX_DLL void SetCollisionPoint(Vector3 point);

	DPHYSX_DLL Matrix3x3 GetInertia(void) const;
	DPHYSX_DLL Matrix3x3 GetInverseInertia(void) const;

	DPHYSX_DLL Quaternion GetOrientation(void) const;

private:
	float mInverseMass;
	float mSpeed;
	float mRadius;
	float mCoefRest;

	bool mIsScenery;

	Transform* mTransform;

	Vector3 mExtents;

	Vector3 mNetForce;

	Vector3 mEulerAngles;

	Vector3 mVelocity;
	Vector3 mAcceleration;
	Vector3 mAngVelocity;
	Vector3 mAngAcceleration;

	Vector3 mCollisionPoint;

	Vector3 mMoments;

	Matrix3x3 mInertia;
	Matrix3x3 mIeInverse;
	Matrix3x3 mInertiaInverse;

	Quaternion mOrientation;

	DPHYSX_DLL void ResetForce(void);
	DPHYSX_DLL void UpdatePosition(float deltaTime);
};

#endif