#ifndef __DPHYSX_PARTICLEMODEL__
#define __DPHYSX_PARTICLEMODEL__

#ifndef DPHYSX_DLL_EXPORT
#define DPHYSX_DLL __declspec(dllexport)
#else
#define DPHYSX_DLL __declspec(dllimport)
#endif

#include <iostream>
#include "Transform.h"

using namespace std;

class Particle
{
public:
	DPHYSX_DLL Particle(void);
	DPHYSX_DLL Particle(Transform* transform, float mass);
	DPHYSX_DLL ~Particle(void);

	DPHYSX_DLL void Update(float deltaTime);
	
	DPHYSX_DLL void SetMass(float mass);
	DPHYSX_DLL void SetRadius(float radius);
	DPHYSX_DLL void SetRestituition(float rest);
	DPHYSX_DLL void SetScenery(bool isScenery);
	DPHYSX_DLL void SetBBox(Vector3 bbox);
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
	DPHYSX_DLL Vector3 GetBBox(void) const;
	DPHYSX_DLL Transform* GetTransform(void) const;
protected:
	float mRadius;
private:
	bool mIsScenery;

	float mCoefRest;
	float mInverseMass;

	static float mGravity;

	Transform* mTransform;
	
	Vector3 mBBox;

	Vector3 mNetForce;
	Vector3 mVelocity;
	Vector3 mAcceleration;

	DPHYSX_DLL void ResetForce(void);
	DPHYSX_DLL void UpdatePosition(float deltaTime);
};

#endif
