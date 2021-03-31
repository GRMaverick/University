#include "SteeringEngine.h"

SteeringEngine* SteeringEngine::mInstance = nullptr;

SteeringEngine::SteeringEngine(void)
{

}
SteeringEngine::~SteeringEngine(void)
{

}

SteeringEngine& SteeringEngine::Instance(void)
{
	if (mInstance == nullptr)
	{
		mInstance = new SteeringEngine();
	}

	return *mInstance;
}

void SteeringEngine::Seek(Steering& _steering, Vector2D _target)
{
	Vector2D desired = Vec2DNormalize(_target - _steering.Position) * _steering.MaxSpeed;
	_steering.Velocity = desired - _steering.Velocity;
}
void SteeringEngine::Flee(Steering& _steering, Vector2D _target)
{
	Vector2D desired = Vec2DNormalize(_steering.Position - _target) * _steering.MaxSpeed;
	_steering.Velocity = desired - _steering.Velocity;
}
void SteeringEngine::Arrive(Steering& _steering, Vector2D _target)
{
	float radius = 5.0f;
	float timeToTarget = 1.0f;

	Vector2D desired = _target - _steering.Position;

	if (desired.Length() < radius)
	{
		_steering.Velocity = Vector2D();
	}
	else
	{
		_steering.Velocity = desired;
		_steering.Velocity /= timeToTarget;
	}
}
void SteeringEngine::Wander(float elapsedTime)
{
	float jitterTime = JITTER_CONST * elapsedTime;
	Vector2D wanderTarget = Vec2DNormalize(Vector2D(RAND_CLAMP * jitterTime, RAND_CLAMP * jitterTime));
	wanderTarget *= WANDER_RADIUS;
}