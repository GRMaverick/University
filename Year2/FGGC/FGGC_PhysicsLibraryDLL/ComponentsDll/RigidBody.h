#pragma once

#ifdef COMPONENTSDLL_EXPORTS
	#define COMPONENTSDLL_API __declspec(dllexport)
#else
	#define COMPONENTSDLL_API __declspec(dllimport)
#endif

#include "Commons.h"
#include "Components.h"

class RigidBody : public ParticleModel
{
public:
	RigidBody() : ParticleModel(nullptr, 0.0f) { mRotation = Quaternion(); mAngularVelocity = XMFLOAT3(); }
	RigidBody(Transform* transform, float mass) : ParticleModel(transform, mass) { }
	~RigidBody() { ParticleModel::~ParticleModel(); }

	COMPONENTSDLL_API void CalculateDerivedData();
	COMPONENTSDLL_API void CalculateTransformMatrix(XMFLOAT4X3 matrix, XMFLOAT3 position, Quaternion rotation);


	COMPONENTSDLL_API void SetRotation(Quaternion rotation) { mRotation = rotation; }
	COMPONENTSDLL_API void SetAngularVelocity(XMFLOAT3 aVelocity) { mAngularVelocity = aVelocity; }

	COMPONENTSDLL_API XMFLOAT3 GetRotation() { return XMFLOAT3(mRotation.x, mRotation.y, mRotation.z); }
	COMPONENTSDLL_API XMFLOAT3 GetAngularVelocity() { return mAngularVelocity; }
private:
	Quaternion mRotation;
	XMFLOAT3 mAngularVelocity;
};