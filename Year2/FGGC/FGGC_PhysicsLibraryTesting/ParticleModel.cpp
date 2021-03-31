#include "ParticleModel.h"


ParticleModel::ParticleModel(Transform * transform, bool useConstAccel, XMFLOAT3 initialVelocity, XMFLOAT3 initialAcceleration) : _transform(transform), _velocity(initialVelocity), _acceleration(initialAcceleration), _useConstAccel(useConstAccel)
{

}


ParticleModel::~ParticleModel()
{
}

void ParticleModel::move(float xAmount, float yAmount, float zAmount)
{
	XMFLOAT3 position = _transform->GetPosition();

	position.x += xAmount;
	position.y += yAmount;
	position.z += zAmount;

	_transform->SetPosition(position);
}

void ParticleModel::MoveConstVel(float deltaTime)
{
	XMFLOAT3 position = _transform->GetPosition();

	position.x += _velocity.x * deltaTime;
	position.y += _velocity.y * deltaTime;
	position.z += _velocity.z * deltaTime;

	_transform->SetPosition(position);
}

void ParticleModel::MoveConstAccel(float deltaTime)
{
	XMFLOAT3 position = _transform->GetPosition();

	// S = UT + 0.5AT^2
	position.x += _velocity.x * deltaTime + 0.5f * _acceleration.x * deltaTime * deltaTime;
	position.y += _velocity.y * deltaTime + 0.5f * _acceleration.y * deltaTime * deltaTime;
	position.z += _velocity.z * deltaTime + 0.5f * _acceleration.z * deltaTime * deltaTime;

	// V = U + AT
	_velocity.x += _acceleration.x * deltaTime;
	_velocity.y += _acceleration.y * deltaTime;
	_velocity.z += _acceleration.z * deltaTime;

	_transform->SetPosition(position);
}

void ParticleModel::Update(float deltaTime)
{
	if (_useConstAccel)
	{
		MoveConstAccel(deltaTime);
	}
	else
	{
		MoveConstVel(deltaTime);
	}
}