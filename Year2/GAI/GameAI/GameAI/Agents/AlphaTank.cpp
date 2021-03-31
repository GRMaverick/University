#include "AlphaTank.h"
#include "../TankManager.h"
#include "../Commons.h"
#include "../C2DMatrix.h"

AlphaTank::AlphaTank(SDL_Renderer* renderer, TankSetupDetails details)
	: BaseTank(renderer, details)
{
	mRenderer = renderer;

	mTankTurnDirection  = DIRECTION_UNKNOWN;
	mTankTurnKeyDown	= false;
	mTankMoveDirection	= DIRECTION_NONE;
	mTankMoveKeyDown	= false;
	mManTurnDirection   = DIRECTION_UNKNOWN;
	mManKeyDown			= false;
	mFireKeyDown		= false;
}

AlphaTank::~AlphaTank()
{
}

void AlphaTank::ChangeState(BASE_TANK_STATE newState)
{
	BaseTank::ChangeState(newState);
}

void AlphaTank::Update(float deltaTime, SDL_Event e)
{
	mSteering.MaxSpeed = mMaxSpeed;
	mSteering.Position = this->GetCentralPosition();
	mSteering.Velocity = mVelocity;
	mSteering.Heading = mHeading;

	switch(e.type)
	{
		//Deal with keyboard input.
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				//Tank speed keys.
				case SDLK_UP:
					break;
				case SDLK_DOWN:
					break;
				case SDLK_LEFT:
					break;
				case SDLK_RIGHT:
					break;
				case SDLK_a:
					break;
				case SDLK_d:
					break;
				case SDLK_1:
					break;
				case SDLK_2:
					break;
			}
			break;
		case SDL_KEYUP:
			switch(e.key.keysym.sym)
			{
				case SDLK_LEFT:
				case SDLK_RIGHT:
					break;
				case SDLK_UP:
				case SDLK_DOWN:
					break;
				case SDLK_a:
				case SDLK_d:
					break;

				case SDLK_1:
					mState = STATE_SEEK;
					break;
				case SDLK_2:
					mState = STATE_FLEE;
					break;
				case SDLK_3:
					mState = STATE_IDLE;
					break;
				case SDLK_4:
					mState = STATE_ARRIVE;
					break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (e.button.state)
			{
				case SDL_BUTTON_LEFT:
					mClick = Vector2D(e.motion.x, e.motion.y);
			}
			break;
		case SDL_MOUSEMOTION:
			mMotion.x = e.motion.x;
			mMotion.y = e.motion.y;
			break;
	}

	switch (mState)
	{
	case STATE_IDLE:
		mSteering.Velocity = Vector2D();
		break;
	case STATE_SEEK:
		STEERING.Seek(mSteering, mClick);
		break;
	case STATE_FLEE:
		STEERING.Flee(mSteering, mClick);
		break;
	case STATE_ARRIVE:
		STEERING.Arrive(mSteering, mClick);
		break;
	default:
		break;
	}

	mVelocity = mSteering.Velocity;

	RotateHeadingToFacePosition(mClick, deltaTime);

	BaseTank::Update(deltaTime, e); 
}

void AlphaTank::MoveInHeadingDirection(float deltaTime)
{
	Vector2D force = (mHeading*mCurrentSpeed)-mVelocity;

	Vector2D acceleration = force/GetMass();

	mVelocity += acceleration * deltaTime;
	
	mVelocity.Truncate(GetMaxSpeed()); 

	Vector2D newPosition = GetPosition();
		newPosition.x += mVelocity.x*deltaTime;
		newPosition.y += (mVelocity.y/**-1.0f*/)*deltaTime;
	SetPosition(newPosition);
}

void AlphaTank::RotateHeadingByRadian(double radian, int sign)
{
	if (radian > mMaxTurnRate) 
		radian = mMaxTurnRate;
	else if(radian < -mMaxTurnRate)
		radian = -mMaxTurnRate;

    mRotationAngle += RadsToDegs(radian)*sign;

	C2DMatrix RotationMatrix;
  
	RotationMatrix.Rotate(radian * sign);	
	RotationMatrix.TransformVector2Ds(mHeading);

	RotationMatrix.TransformVector2Ds(mVelocity);

	mSide = mHeading.Perp();
}

void AlphaTank::Render(void)
{
	BaseTank::Render();
	SDL_SetRenderDrawColor(mRenderer, 255.0f, 0.0f, 0.0f, 1.0f);

	SDL_Rect mousePosition;
	mousePosition.x = mClick.x;
	mousePosition.y = mClick.y;
	mousePosition.w = 10;
	mousePosition.h = 10;
	SDL_RenderDrawRect(mRenderer, &mousePosition);
}
