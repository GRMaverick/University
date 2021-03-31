#pragma once

#include "Commons.h"
#include "Structure.h"
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(string type, Appearance* app, Transform* transform, ParticleModel* pModel) : GameObject(type, app, transform, pModel) { mFired = false; mSpeed = 2.0f; }
	~Projectile() { GameObject::~GameObject(); }

	void Update(float deltaTime);
	void Move(float deltaTime);
	void CalculateForwardVector();

	inline void SetForward(XMFLOAT3 forward) { mForward = forward; }
	inline XMFLOAT3 GetForward() const { return mForward; }

	inline void SetFired(bool fired) { mFired = fired; }
	inline bool GetFired() const { return mFired; }

private:
	float				mSpeed;
	bool				mFired;
	XMFLOAT3  mForward;
};