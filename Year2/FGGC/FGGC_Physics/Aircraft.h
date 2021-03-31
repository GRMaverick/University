#pragma once

#include "Structure.h"
#include "Commons.h"
#include "GameObject.h"
#include "Projectile.h"

class Aircraft : public GameObject
{
public:
	Aircraft(string type, Appearance* appearance, Transform* transform, ParticleModel* particleModel, GameObject* leader);
	~Aircraft() { GameObject::~GameObject(); }

	void Update(float deltaTime);
	void UpdateChildren(float deltaTime);

	void CalculateForwardVector();
	void CalculateLift();
	void CalculateDrag();
	void TruncateSpeed();

	void Draw(ID3D11DeviceContext* iContext);

	inline void SetSpeed(float speed) { mSpeed = speed; }
	inline float GetSpeed() const { return mSpeed; }

	inline void SetMaxSpeed(float speed) { mMaxSpeed = speed; }
	inline float GetMaxSpeed() const { return mMaxSpeed; }

	inline void AddRotationX(float x) { mRotationX += x; }
	inline void AddRotationY(float y) { mRotationY += y; }
	inline void AddRotationZ(float z) { mRotationZ += z; }

	inline float GetRotationX() const { return mRotationX; }
	inline float GetRotationY() const { return mRotationY; }
	inline float GetRotationZ() const { return mRotationZ; }
	
	inline void SetForwardVec(XMFLOAT3 forward) { mForward = forward; }
	inline XMFLOAT3 GetForwardVec() const { return mForward; }
	
	inline void SetTarget(XMFLOAT3 target) { mTarget = target; }
	inline XMFLOAT3 GetTarget() const { return mTarget; }

	inline void SetTargetVelocity(XMFLOAT3 target) { mTargetVelocity = target; }
	inline XMFLOAT3 GetTargetVelocity() const { return mTargetVelocity; }
	
	inline void SetWheelRotation(float rotation) { mWheelRotation = rotation; }
	inline float GetWheelRotation() const { return mWheelRotation; }

	inline void AddProjectile(Projectile* proj) { proj->GetTransform()->SetParent(this->GetTransform()); mProjectiles.push_back(proj); }	
	inline void RemoveProjectile() { mProjectiles.front()->GetTransform()->SetParent(nullptr); mProjectiles.pop_back(); }
	inline vector<Projectile*> GetProjectiles() const { return mProjectiles; }
		
private:
	GameObject* mRudder;
	vector<Projectile*> mProjectiles;

	Transform* mTransform;
	XMFLOAT3 mForward;

	XMFLOAT3 mOldRotation;
	XMFLOAT3 mTarget;
	XMFLOAT3 mTargetVelocity;

	float mRotationX;
	float mRotationY;
	float mRotationZ;
	float mRotationSpeed;
	float mWheelRotation;
	
	float mSpeed;
	float mMaxSpeed;
};