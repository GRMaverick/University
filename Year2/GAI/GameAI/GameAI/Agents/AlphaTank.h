#ifndef __ALPHA_TANK_H__
#define __ALPHA_TANK_H__

#include "../BaseTank.h"
#include <SDL.h>
#include "../Commons.h"

#include "../SteeringEngine.h"

#include "../NeuralNetwork.h"

enum AI_STATE
{
	STATE_IDLE,
	STATE_SEEK,
	STATE_FLEE,
	STATE_ARRIVE,
	STATE_MAX,
};

class AlphaTank : public BaseTank
{
public:
	AlphaTank(SDL_Renderer* renderer, TankSetupDetails details);
	~AlphaTank();

	void ChangeState(BASE_TANK_STATE newState);

	void Update(float deltaTime, SDL_Event e);

	void RotateHeadingByRadian(double radian, int sign);

	void Render(void);

protected:
	void	MoveInHeadingDirection(float deltaTime);

private:
	bool			mFireKeyDown;
	bool			mManKeyDown;
	bool			mTankTurnKeyDown;
	bool			mTankMoveKeyDown;

	TURN_DIRECTION  mManTurnDirection;
	TURN_DIRECTION  mTankTurnDirection;
	MOVE_DIRECTION  mTankMoveDirection;

	AI_STATE mState;
	Steering mSteering;

	Vector2D mClick;
	Vector2D mMotion;

	SDL_Renderer* mRenderer;

	NeuralNetwork mBrain;
};


#endif 