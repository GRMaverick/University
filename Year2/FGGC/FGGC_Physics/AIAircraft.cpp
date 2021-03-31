#include "AIAircraft.h"
#include "PlaneParticle.h"

AIAircraft::AIAircraft(string type, Appearance* app, Transform* transform, ParticleModel* particleModel, GameObject* leader)
	: Aircraft(type, app, transform, particleModel, leader)
{
	mTargetPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTargetIndex = 0;

	PlaneParticle* particle = (PlaneParticle*)GetParticleModel();
	particle->SetMaxSpeed(10.0f);
}

void AIAircraft::Update(float deltaTime)
{
	//GoToTarget();
	//Pathfollowing();

	Aircraft::Update(deltaTime);
}

void AIAircraft::GoToTarget()
{
	PlaneParticle* planeParticle = (PlaneParticle*)GetParticleModel();
	float engineSpeed = planeParticle->GetSpeed();

	XMFLOAT3 planePosition = planeParticle->GetTransform()->GetPosition();
	XMFLOAT3 planeDirection = planeParticle->GetPlaneDirection();
	XMFLOAT3 upDirection = XMFLOAT3(planePosition.x, planePosition.y + 10.0f, planePosition.z);
	upDirection = upDirection + planePosition;

	XMFLOAT3 forwardDirection = planePosition - (planePosition + planeDirection);
	XMFLOAT3 targetDirection = mTargetPosition = planePosition;
	XMFLOAT3 crossProduct = Cross(forwardDirection, targetDirection);
	
	float dotProduct = (crossProduct.x + upDirection.x) + (crossProduct.y + upDirection.y) + (crossProduct.z + upDirection.z);

	if (dotProduct < 5.0f && dotProduct > -5.0f)
	{
		planeParticle->AddSpeed(0.5f);
		SetWheelRotation(0.0f);
	}
	else if (dotProduct > 5.0f)
	{
		SetWheelRotation(GetWheelRotation() + 0.5f);
	
		if (engineSpeed < 0.1)
		{
			planeParticle->AddSpeed(0.5f);
		}
		else if (engineSpeed > 0.1)
		{
			planeParticle->AddSpeed(-0.5f);
		}
	}
	else if (dotProduct < 5.0f)
	{
		SetWheelRotation(GetWheelRotation() - 0.5f);

		if (engineSpeed < 0.1)
		{
			planeParticle->AddSpeed(0.5f);
		}
		else if (engineSpeed > 0.1)
		{
			planeParticle->AddSpeed(-0.5f);
		}
	}
}
void AIAircraft::Pathfollowing()
{
	mTargetPosition = mPath.at(mTargetIndex);
	XMFLOAT3 planePosition = GetTransform()->GetPosition();

	XMFLOAT3 targetDistance = mTargetPosition - planePosition;

	float magnitude = Magnitude(targetDistance);

	if (magnitude <= 30.0f)
		mTargetIndex++ ;

	if (mTargetIndex >= mPath.size())
		mTargetIndex = 0;
}