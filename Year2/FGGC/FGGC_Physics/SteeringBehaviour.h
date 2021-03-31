#pragma once

#include "Structure.h"
#include "Commons.h"
#include "GameObject.h"
#include "Aircraft.h"

class Aircraft;

class SteeringBehaviour
{
public:
	SteeringBehaviour(GameObject* agent, GameObject* leader);
	~SteeringBehaviour();

	XMFLOAT3 Wander();

	void Seek(XMFLOAT3 target);
	void Pathfollowing();

	XMFLOAT3 Flee(XMFLOAT3 target);
	XMFLOAT3 Arrive(XMFLOAT3 target, DECELERATION deceleration);
	XMFLOAT3 OffsetPursuit(XMFLOAT3 offset);

private:
	int mTargetIndex;

	Aircraft* mAgent;
	Aircraft* mLeader;

	XMFLOAT3 mSteeringForce;
	XMFLOAT3 mTarget;
	XMFLOAT3 mWanderTarget;

	vector<XMFLOAT3> mPath;
};