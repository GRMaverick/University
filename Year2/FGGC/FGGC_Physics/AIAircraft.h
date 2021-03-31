#pragma once

#include "Commons.h"
#include "Structure.h"
#include "Aircraft.h"

class AIAircraft : public Aircraft
{
public:
	AIAircraft(string type, Appearance* app, Transform* transform, ParticleModel* particleModel, GameObject* leader);
	~AIAircraft() { Aircraft::~Aircraft(); }

	void Update(float deltaTime);
	void Pathfollowing();
	void GoToTarget();

	void SetPath(vector<XMFLOAT3> path) { mPath = path; }
	vector<XMFLOAT3> GetPath() const { return mPath; }

private:
	vector<XMFLOAT3> mPath;

	bool mFinished;

	XMFLOAT3 mTargetPosition;
	int mTargetIndex;
};
