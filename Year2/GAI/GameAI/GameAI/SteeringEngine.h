#ifndef __STEERING_ENGINE_H__
#define __STEERING_ENGINE_H__

#include "Commons.h"

#define JITTER_CONST 2.0f
#define WANDER_RADIUS 3.0f

struct Steering
{
	Vector2D Position;
	Vector2D Velocity;
	Vector2D	Heading;
	double		MaxSpeed;
};

class SteeringEngine
{
public:
	static SteeringEngine& Instance(void);
	~SteeringEngine(void);

	void Seek(Steering& _steering, Vector2D _target);
	void Flee(Steering& _steering, Vector2D _target);
	void Arrive(Steering& _steering, Vector2D _target);
	void Wander(float elapsedTime);

private:
	static SteeringEngine* mInstance;
	SteeringEngine(void);
};

#define RAND_FLOAT	((rand()) / (RAND_MAX + 1.0))
#define RAND_CLAMP (RAND_FLOAT - RAND_FLOAT)
#define STEERING SteeringEngine::Instance()

#endif