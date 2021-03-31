#pragma once

#include <windows.h>
#include <vector>

#include "Commons.h"
#include "TransformComponent.h"

using namespace std;

class ParticleModel
{
public:
	ParticleModel(Transform* transform, bool constAccOn, XMFLOAT3 velocity, XMFLOAT3 acceleration);
	ParticleModel(Transform * transform, XMFLOAT3 velocity, XMFLOAT3 acceleration, XMFLOAT3 angVel, XMFLOAT3 angAcc);
	ParticleModel(Transform* transform, bool constAccOn, XMFLOAT3 velocity, XMFLOAT3 acceleration, float mass, XMFLOAT3 netForce);
	~ParticleModel();

	void Update(float deltaTime);
	void UpdateState(float deltaTime);
	void UpdateNetForce();
	void UpdateAcceleration();

	void Move(float deltaTime);
	void Move(float xAmount, float yAmount, float zAmount);

	void MoveConstantVelocity(float deltaTime);
	void MoveConstantAcceleration(float deltaTime);

	void SpinConstantVelocity(float deltaTime);
	void SpinConstantAcceleration(float deltaTime);

	bool CollisionCheck(XMFLOAT3 position, float radius);

	void SetMass(float mass);
	void SetRadius(float radius);
	void SetLift(XMFLOAT3 lift);
	void SetDrag(XMFLOAT3 drag);
	void SetThrust(XMFLOAT3 thrust);
	void SetWeight(XMFLOAT3 weight);
	void SetConsAccOn(bool consAcc);
	void SetVelocity(XMFLOAT3 velocity);
	void SetNetForce(XMFLOAT3 nForce);
	void SetAngularVelocity(XMFLOAT3 radians);
	void SetAcceleration(XMFLOAT3 acceleration);

	float GetMass() const;
	float GetRadius() const;
	Transform* GetTransform() const;
	XMFLOAT3 GetLift() const;
	XMFLOAT3 GetDrag() const;
	XMFLOAT3 GetThrust() const;
	XMFLOAT3 GetWeight() const;
	XMFLOAT3 GetVelocity() const;
	XMFLOAT3 GetNetForce() const;
	XMFLOAT3 GetAcceleration() const;	
	XMFLOAT3 GetAngularVelocity() const;

private:
	bool					 _consAccOn;

	float					_mass;
	float					_radius;

	XMFLOAT3	_netForce;
	XMFLOAT3	_weight;
	XMFLOAT3	_thrust;
	XMFLOAT3	_lift;
	XMFLOAT3	_drag;

	Transform*		_transform;

	XMFLOAT3	_velocity;
	XMFLOAT3	_acceleration;
	XMFLOAT3	_angularVelocity;
	XMFLOAT3	_angularAcceleration;
};

