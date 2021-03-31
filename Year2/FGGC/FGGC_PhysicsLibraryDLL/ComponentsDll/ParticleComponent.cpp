#include "stdafx.h"
#include "ParticleComponent.h"
#include <stdexcept>

ParticleModel::ParticleModel(Transform* transform, float inverseMass){
	mIsResting = false;
	mGravity = 9.81;
	mTransform = transform;
	mInverseMass = 1 / inverseMass;
	mDamping = 0.5f;
	mWeight = XMFLOAT3(0.0f, mInverseMass * -mGravity, 0.0f);
	mVelocity = mAcceleration = mNetForce = mLift = mThrust = mDrag = XMFLOAT3(0.0f, 0.0f, 0.0f);
}
ParticleModel::~ParticleModel(){
}

void ParticleModel::Update(float deltaTime){
	this->UpdateNetForce();
	this->UpdateAcceleration();
	this->UpdatePosition(deltaTime);

	powf(mDamping, deltaTime);

	this->ResetNetForce();
}

void ParticleModel::UpdateNetForce(){
	mNetForce.x = mWeight.x + mLift.x + mDrag.x + mThrust.x;
	mNetForce.y = mWeight.y + mLift.y + mDrag.y + mThrust.y;
	mNetForce.z = mWeight.z + mLift.z + mDrag.z + mThrust.z;
}

void ParticleModel::UpdateAcceleration(){
	mAcceleration.x = mNetForce.x / mInverseMass;
	mAcceleration.y = mNetForce.y / mInverseMass;
	mAcceleration.z = mNetForce.z / mInverseMass;
}
void ParticleModel::UpdatePosition(float deltaTime){
	XMFLOAT3 position = mTransform->GetPosition();

	position.x += mVelocity.x * deltaTime + 0.5 * mAcceleration.x * deltaTime * deltaTime;
	position.y += mVelocity.y * deltaTime + 0.5 * mAcceleration.y * deltaTime * deltaTime;
	position.z += mVelocity.z * deltaTime + 0.5 * mAcceleration.z * deltaTime * deltaTime;

	mTransform->SetPosition(position);

	mVelocity.x += mAcceleration.x * deltaTime;
	mVelocity.y += mAcceleration.y * deltaTime;
	mVelocity.z += mAcceleration.z * deltaTime;
}

void ParticleModel::UpdateResting(float deltaTime)
{
	bool restTest = mVelocity.x < 1.0f && mVelocity.y < 1.0f && mVelocity.z < 1.0f;

	if (restTest)
		mIsResting = true;
	else
		mIsResting = false;

	if (mIsResting)
		mWeight = XMFLOAT3(0.0f, 0.0f, 0.0f);
	else
		mWeight = XMFLOAT3(0.0f, mInverseMass * -mGravity, 0.0f);
}

void ParticleModel::ResetNetForce(){
	mNetForce = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

bool ParticleModel::CollisionCheck(XMFLOAT3 position, float radius){
	XMFLOAT3 object1Pos = mTransform->GetPosition();

	XMFLOAT3 difference;
	difference.x = object1Pos.x - position.x;
	difference.y = object1Pos.y - position.y;
	difference.z = object1Pos.z - position.z;

	float differenceMag = sqrt((difference.x * difference.x) + (difference.y * difference.y) + (difference.z * difference.z));

	float radiusDistance = mRadius + radius;

	if (differenceMag <= radiusDistance)
		return true;
	else
		return false;
}
bool ParticleModel::CollisionCheck(ParticleModel* object2)
{
	XMFLOAT3 obj1Pos = mTransform->GetPosition();
	XMFLOAT3 obj2Pos = object2->GetTransform()->GetPosition();

	XMFLOAT3 obj1Box = mBBox;
	XMFLOAT3 obj2Box = object2->GetBBox();

	float aX = obj1Pos.x - obj1Box.x;				float aWidth = obj1Pos.x + obj1Box.x;
	float aY = obj1Pos.y - obj1Box.y;				float aHeight = obj1Pos.y + obj1Box.y;
	float aZ = obj1Pos.z - obj1Box.z;				float aDepth = obj1Pos.z + obj1Box.z;

	float bX = obj2Pos.x - obj2Box.x;			float bWidth = obj2Box.x + obj2Box.x;
	float bY = obj2Pos.y - obj2Box.y;			float bHeight = obj2Box.y + obj2Box.y;
	float bZ = obj2Pos.z - obj2Box.z;			float bDepth = obj2Box.z + obj2Box.z;

	if (aX > bX + bWidth)
		return false;
	else if (aX + aWidth < bX)
		return false;
	else if (aY > bY + bHeight)
		return false;
	else if (bY + bHeight < aY)
		return false;
	else if (aZ > bZ + bDepth)
		return false;
	else if (bZ + bDepth < aZ)
		return false;

	return true;
}
void ParticleModel::ResolveInterpenetration(ParticleModel* object2)
{
	XMFLOAT3 thisLast = mTransform->GetLastPosition();
	XMFLOAT3 object2Last = object2->GetTransform()->GetLastPosition();

	mTransform->SetPosition(mTransform->GetLastPosition());
	object2->GetTransform()->SetPosition(object2->GetTransform()->GetLastPosition());
}
void ParticleModel::ResolveCollision(ParticleModel* object2)
{
	float cofRest = min(mCoefR, object2->GetRestituition());

	float mA = mInverseMass;
	float mB = object2->GetMass();
	XMFLOAT3 uA = mVelocity;
	XMFLOAT3 uB = object2->GetVelocity();
	XMFLOAT3 vA = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 vB = XMFLOAT3(0.0f, 0.0f, 0.0f);

	vA.x = (mA * uA.x) + (mB * uB.x) + mB * cofRest * (uB.x - uA.x) / (mA + mB);
	vA.y = (mA * uA.y) + (mB * uB.y) + mB * cofRest * (uB.y - uA.y) / (mA + mB);
	vA.z = (mA * uA.z) + (mB * uB.z) + mB * cofRest * (uB.z - uA.z) / (mA + mB);

	vB.x = (mA * uA.x) + (mB * uB.x) + mA * cofRest * (uA.x - uB.x) / (mA + mB);
	vB.y = (mA * uA.y) + (mB * uB.y) + mA * cofRest * (uA.y - uB.y) / (mA + mB);
	vB.z = (mA * uA.z) + (mB * uB.z) + mA * cofRest * (uA.z - uB.z) / (mA + mB);

	mVelocity = vA;
	if (!object2->GetScenery())
		object2->SetVelocity(vB);
}

