#include "ParticleModel.h"

ParticleModel::ParticleModel(Transform* transform, bool consAccOn, XMFLOAT3 velocity, XMFLOAT3 acceleration){
	_transform						= transform;
	_consAccOn					= consAccOn;
	_velocity							= velocity;
	_acceleration					= acceleration;
	_angularVelocity				= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_angularAcceleration		= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_lift									= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_drag								= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_thrust								= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_weight							= XMFLOAT3(0.0f, 0.0f, 0.0f);
}
ParticleModel::ParticleModel(Transform * transform, XMFLOAT3 velocity, XMFLOAT3 acceleration, XMFLOAT3 angVel, XMFLOAT3 angAcc){
	_consAccOn					= false;
	_transform						= transform;
	_velocity							= velocity;
	_acceleration					= acceleration;
	_angularVelocity				= angVel;
	_angularAcceleration		= angAcc;
	_mass								= 0.0f;
	_radius								= 0.0f;
	_netForce						= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_lift									= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_drag								= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_thrust								= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_weight							= XMFLOAT3(0.0f, 0.0f, 0.0f);
}
ParticleModel::ParticleModel(Transform* transform, bool consAccOn, XMFLOAT3 velocity, XMFLOAT3 acceleration, float mass, XMFLOAT3 netForce){
	_transform						= transform;
	_consAccOn					= consAccOn;
	_velocity							= velocity;
	_acceleration					= acceleration;
	_angularVelocity				= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_angularAcceleration		= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_mass								= mass;
	_netForce						= netForce;
	_lift									= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_drag								= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_thrust								= XMFLOAT3(0.0f, 0.0f, 0.0f);
	_weight							= XMFLOAT3(0.0f, 0.0f, 0.0f);
}
ParticleModel::~ParticleModel()
{
	//delete _transform;
}

void ParticleModel::Update(float deltaTime)
{
	this->UpdateState(deltaTime);
}
void ParticleModel::UpdateState(float deltaTime)
{
	this->UpdateNetForce();
	this->UpdateAcceleration();
	this->Move(deltaTime);
}
void ParticleModel::UpdateNetForce()
{
	_netForce.x = _lift.x + _drag.x + _thrust.x + _weight.x;
	_netForce.y = _lift.y + _drag.y + _thrust.y + _weight.y;
	_netForce.z = _lift.z + _drag.z + _thrust.z + _weight.z;
}
void ParticleModel::UpdateAcceleration()
{
	_acceleration.x = _netForce.x / _mass;
	_acceleration.y = _netForce.y / _mass;
	_acceleration.z = _netForce.z / _mass;
}

void ParticleModel::Move(float deltaTime)
{
	XMFLOAT3 position = _transform->GetPosition();

	position.x += _velocity.x * deltaTime + 0.5 * _acceleration.x * deltaTime * deltaTime;
	position.y += _velocity.y * deltaTime + 0.5 * _acceleration.y * deltaTime * deltaTime;
	position.z += _velocity.z * deltaTime + 0.5 * _acceleration.z * deltaTime * deltaTime;

	_transform->SetPosition(position);

	_velocity.x += _acceleration.x * deltaTime;
	_velocity.y += _acceleration.y * deltaTime;
	_velocity.z += _acceleration.z * deltaTime;
}
void ParticleModel::Move(float xAmount, float yAmount, float zAmount)
{
	XMFLOAT3 position = _transform->GetPosition();

	position.x += xAmount;
	position.y += yAmount;
	position.z += zAmount;

	_transform->SetPosition(position);
}
//void ParticleModel::MoveConstantVelocity(float deltaTime)
//{
//	XMFLOAT3 position = _transform->GetPosition();
//
//	position.x += _velocity.x * deltaTime;
//	position.y += _velocity.y * deltaTime;
//	position.z += _velocity.z * deltaTime;
//
//	_transform->SetPosition(position);
//}
//void ParticleModel::MoveConstantAcceleration(float deltaTime)
//{
//	XMFLOAT3 position = _transform->GetPosition();
//	
//	// Update world position of object by adding displacement to previously calculated position
//	position.x += ((_velocity.x * deltaTime) + (0.5 * _acceleration.x * deltaTime * deltaTime));
//	position.y += ((_velocity.y * deltaTime) + (0.5 * _acceleration.y * deltaTime * deltaTime));
//	position.x += ((_velocity.z * deltaTime) + (0.5 * _acceleration.z * deltaTime * deltaTime));
//
//	_transform->SetPosition(position);
//
//	// Update velocity of object by adding change relative to previously calculated velocity
//	_velocity.x += _acceleration.x * deltaTime;
//	_velocity.y += _acceleration.y * deltaTime;
//	_velocity.z += _acceleration.z * deltaTime;
//}
	
void ParticleModel::SpinConstantVelocity(float deltaTime)
{
	XMFLOAT3 rotation = _transform->GetRotation();

	rotation.x += _angularVelocity.x * deltaTime;
	rotation.y += _angularVelocity.y * deltaTime;
	rotation.z += _angularVelocity.z * deltaTime;

	_transform->SetRotation(rotation);
}
void ParticleModel::SpinConstantAcceleration(float deltaTime)
{
	XMFLOAT3 rotation = _transform->GetRotation();

	// Update world position of object by adding angular desplacement to previously calculated position
	rotation.x += (_angularVelocity.x * deltaTime) + (0.5f * _angularAcceleration.x * deltaTime * deltaTime);
	rotation.y += (_angularVelocity.y * deltaTime) + (0.5f * _angularAcceleration.y * deltaTime * deltaTime);
	rotation.z += (_angularVelocity.z * deltaTime) + (0.5f * _angularAcceleration.z * deltaTime * deltaTime);

	_transform->SetRotation(rotation);

	// Update angular velocity of object by adding change relative to previously calculated angular velocity
	_angularVelocity.x += _angularAcceleration.x * deltaTime;
	_angularVelocity.y += _angularAcceleration.y * deltaTime;
	_angularVelocity.z += _angularAcceleration.z * deltaTime;

}

bool ParticleModel::CollisionCheck(XMFLOAT3 position, float radius){
	XMFLOAT3 vector = XMFLOAT3(position.x - _transform->GetPosition().x, position.y - _transform->GetPosition().y, position.z - _transform->GetPosition().z);
	float distance = sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));

	if (distance > (_radius + radius))
		return false;

	return true;
}

// ----
// PROPERTIES - MUTATORS
// ----
void ParticleModel::SetMass(float mass)
{
	_mass = mass;
}
void ParticleModel::SetRadius(float radius){
	_radius = radius;
}
void ParticleModel::SetLift(XMFLOAT3 lift)
{
	_lift = lift;
}
void ParticleModel::SetDrag(XMFLOAT3 drag)
{
	_drag = drag;
}
void ParticleModel::SetThrust(XMFLOAT3 thrust)
{
	_thrust = thrust;
}
void ParticleModel::SetWeight(XMFLOAT3 weight)
{
	_weight = weight;
}
void ParticleModel::SetVelocity(XMFLOAT3 velocity)
{
	_velocity = velocity;
}
void ParticleModel::SetConsAccOn(bool consAccOn)
{
	_consAccOn = consAccOn;
}
void ParticleModel::SetNetForce(XMFLOAT3 nForce) 
{
	_netForce = nForce;
}
void ParticleModel::SetAcceleration(XMFLOAT3 acceleration)
{
	_acceleration = acceleration;
}
void ParticleModel::SetAngularVelocity(XMFLOAT3 angularVelocity)
{
	_angularVelocity = angularVelocity;
}
// ----
// PROPERTIES - ACCESSORS
// ----
float ParticleModel::GetMass() const
{
	return _mass;
}
float ParticleModel::GetRadius() const {
	return _radius;
}
Transform* ParticleModel::GetTransform() const{
	return _transform;
}
XMFLOAT3 ParticleModel::GetLift() const
{
	return _lift;
}
XMFLOAT3 ParticleModel::GetDrag() const
{
	return _drag;
}
XMFLOAT3 ParticleModel::GetThrust() const
{
	return _thrust;
}
XMFLOAT3 ParticleModel::GetWeight() const
{
	return _weight;
}
XMFLOAT3 ParticleModel::GetVelocity() const
{
	return _velocity;
}
XMFLOAT3 ParticleModel::GetNetForce() const
{
	return _netForce;
}
XMFLOAT3 ParticleModel::GetAcceleration() const
{
	return _acceleration;
}
XMFLOAT3 ParticleModel::GetAngularVelocity() const
{
	return _angularVelocity;
}
