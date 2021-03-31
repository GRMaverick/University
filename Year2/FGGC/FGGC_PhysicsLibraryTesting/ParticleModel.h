#pragma once

#include "Transform.h"

class ParticleModel
{
public:
	ParticleModel(Transform * transform, bool useConstAccel, XMFLOAT3 initialVelocity, XMFLOAT3 initialAcceleration);
	~ParticleModel();

	void move(float xAmount, float yAmount, float zAmount);

	XMFLOAT3 GetVelocity() const { return _velocity; }
	void SetVelocity(float x, float y, float z) { _velocity = XMFLOAT3(x, y, z); }
	void SetVelocity(XMFLOAT3 velocity) { _velocity = velocity; }

	XMFLOAT3 GetAcceleration() const { return _acceleration; }
	void SetAcceleration(float x, float y, float z) { _acceleration = XMFLOAT3(x, y, z); }
	void SetAcceleration(XMFLOAT3 acceleration) { _acceleration = acceleration; }

	bool IsUsingConstAccel() const { return _useConstAccel; }
	void SetUsingConstAccel(bool useConstAccel) { _useConstAccel = useConstAccel; }

	void Update(float deltaTime);

private:
	Transform * _transform;

	XMFLOAT3 _velocity;
	XMFLOAT3 _acceleration;

	bool _useConstAccel;

	void MoveConstVel(float deltaTime);
	void MoveConstAccel(float deltaTime);
};

