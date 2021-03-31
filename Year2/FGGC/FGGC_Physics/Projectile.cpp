#include "Projectile.h"

void Projectile::Update(float deltaTime)
{
	CalculateForwardVector();
	Move(deltaTime);
	GameObject::Update(deltaTime);
}
void Projectile::Move(float deltaTime)
{
	if(mFired)
		this->GetParticleModel()->SetVelocity(XMFLOAT3(-mForward.x * mSpeed, -mForward.y * mSpeed, -mForward.z * mSpeed));
}
void Projectile::CalculateForwardVector()
{
	mForward.x = sin(GetTransform()->GetRotation().y);
	mForward.y = -sin(GetTransform()->GetRotation().x);
	mForward.z = cos(GetTransform()->GetRotation().y);

	float planeDirectionMag = sqrt((mForward.x * mForward.x) + (mForward.y * mForward.y) + (mForward.z * mForward.z));
	mForward = XMFLOAT3(mForward.x / planeDirectionMag, mForward.y / planeDirectionMag, mForward.z / planeDirectionMag);
}