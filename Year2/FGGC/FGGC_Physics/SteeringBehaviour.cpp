#include "SteeringBehaviour.h"

SteeringBehaviour::SteeringBehaviour(GameObject* agent, GameObject* leader)
{
	mTargetIndex = 0;

	mAgent = (Aircraft*)agent;
	mLeader = (Aircraft*)leader;

	mSteeringForce = XMFLOAT3();
	mTarget = XMFLOAT3();
	mWanderTarget = XMFLOAT3();
}
SteeringBehaviour::~SteeringBehaviour()
{

}

XMFLOAT3 SteeringBehaviour::Wander()
{
	return XMFLOAT3();
}

void SteeringBehaviour::Seek(XMFLOAT3 target)
{
	XMFLOAT3 agentRotation = mAgent->GetTransform()->GetRotation();
	XMFLOAT3 agentForward = mAgent->GetForwardVec();
	XMFLOAT3 agentPosition = mAgent->GetTransform()->GetPosition();
	XMFLOAT3 upDirection = XMFLOAT3(agentPosition.x, agentPosition.y + 10.0f, agentPosition.z);
	XMFLOAT3 forwardDirection = agentPosition - (agentPosition + agentForward);
	XMFLOAT3 targetDirection = target - agentPosition;
	XMFLOAT3 crossProduct = Cross(forwardDirection, targetDirection);

	mAgent->SetForwardVec(Normalise(targetDirection));
	/*float dotProduct = (crossProduct.x + upDirection.x) + (crossProduct.y + upDirection.y) + (crossProduct.z + upDirection.z);

	CarParticleModel* carBodyTemp = (CarParticleModel*)GetPlaneBody()->GetParticleModel();
	float engineSpeed = carBodyTemp->GetEngineSpeed();

	if (dotProduct < 5.0f && dotProduct > -5.0f)
	{
		carBodyTemp->AddEngineSpeed(0.0008f);
		SetPlaneWheelRotation(0.0f);
	}
	else if (dotProduct > 5.0f)
	{
		AddPlaneWheelRotation(-0.005f);

		if (engineSpeed < 0.1)
		{
			carBodyTemp->AddEngineSpeed(0.0002f);
		}
		else if (engineSpeed > 0.1)
		{
			carBodyTemp->AddEngineSpeed(-0.0002f);
		}
	}
	else if (dotProduct < 5.0f)
	{
		AddPlaneWheelRotation(0.005f);

		if (engineSpeed < 0.1)
		{
			carBodyTemp->AddEngineSpeed(0.0002f);
		}
		else if (engineSpeed > 0.1)
		{
			carBodyTemp->AddEngineSpeed(-0.0002f);
		}
	}*/
}
void SteeringBehaviour::Pathfollowing()
{
	mPath = mAgent->GetPath();
	mTarget = mPath.at(mTargetIndex);

	XMFLOAT3 agentPosition = mAgent->GetTransform()->GetPosition();

	XMFLOAT3 targetDistance = mTarget - agentPosition;

	float targetMagnitude = Magnitude(targetDistance);

	if (-targetMagnitude <=30.0f)
		mTargetIndex++;
	if (mTargetIndex >= mPath.size())
		mTargetIndex = 0;

	mAgent->SetForwardVec(Normalise(targetDistance));
}

XMFLOAT3 SteeringBehaviour::Flee(XMFLOAT3 target)
{
	return XMFLOAT3(0.0f, 0.0f, 0.0f);
}
XMFLOAT3 SteeringBehaviour::Arrive(XMFLOAT3 target, DECELERATION deceleration)
{
	XMFLOAT3 toTarget = target - mAgent->GetTransform()->GetPosition();
	float distance = Magnitude(toTarget);

	if (distance > 0)
	{
		float decelerationTweaker = 0.3;
		float speed = distance / ((float)deceleration * decelerationTweaker);

		speed = min(speed, mAgent->GetMaxSpeed());

		XMFLOAT3 desiredVelocity = toTarget * (speed / distance);

		return (desiredVelocity - mAgent->GetParticleModel()->GetVelocity());
	}

	return XMFLOAT3(0.0f, 0.0f, 0.0f);
}
XMFLOAT3 SteeringBehaviour::OffsetPursuit(XMFLOAT3 offset)
{	
	// Distance to Offset
	XMFLOAT3 toOffset = offset - mAgent->GetTransform()->GetPosition();

	// Look ahead of time, 
	 float lookAheadTime = Magnitude(toOffset) / (mAgent->GetMaxSpeed() + mLeader->GetMaxSpeed());

	// now Arrive at the predicted future position offset
	 return Arrive(offset + mLeader->GetParticleModel()->GetVelocity() * lookAheadTime, DECELERATION::DECELERATION_NORMAL);
}