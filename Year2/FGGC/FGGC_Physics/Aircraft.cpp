#include "Aircraft.h"
#include "PlaneParticle.h"

Aircraft::Aircraft(string type, Appearance* appearance, Transform* transform, ParticleModel* particleModel, GameObject* leader) : GameObject(type, appearance, transform, particleModel) 
{
	mTransform = transform;

	mSpeed = 0.0f;
	mMaxSpeed = 2.0f;

	mRotationX = 0.0f;
	mRotationY = 0.0f;
	mRotationZ = 0.0f;
	mRotationSpeed = 5.7f;
	mWheelRotation = 0.0f;
}

void Aircraft::Update(float deltaTime) 
{
	this->CalculateForwardVector();
	this->CalculateLift();
	this->UpdateChildren(deltaTime);
	this->TruncateSpeed();

	XMFLOAT3 planeRotation = GetTransform()->GetRotation();
	float rudderLimit = 0.5f;
	float rudderRotation = mRudder->GetTransform()->GetRotation().y + planeRotation.y;
	float test = (planeRotation.y - rudderRotation) * 40.0f;	

	string type = this->GetType();

	for each(Projectile* missile in mProjectiles)
	{
		AddChild((GameObject*)missile);
	}

	if (type == "Player")
	{
		this->GetParticleModel()->SetThrust(XMFLOAT3(mForward.x * mSpeed, mForward.y * mSpeed, mForward.z * mSpeed));
	}
	else
	{
		XMFLOAT3 planePos = GetTransform()->GetPosition();
		XMFLOAT3 velocityTemp = GetParticleModel()->GetVelocity();
		
		this->GetParticleModel()->SetThrust(XMFLOAT3(mForward.x * mSpeed, mForward.y * mSpeed, mForward.z * mSpeed));

		float planeWheelLimit = 5.0f;

		if (mWheelRotation <= -planeWheelLimit)
		{
			mWheelRotation = -planeWheelLimit;
		}
		else if (mWheelRotation >= planeWheelLimit)
		{
			mWheelRotation = planeWheelLimit;
		}
	}

	this->GetTransform()->SetRotation(XMConvertToRadians(mRotationX * mRotationSpeed), XMConvertToRadians((mRotationY + (test)) * mRotationSpeed), XMConvertToRadians(mRotationZ * mRotationSpeed));
	
	GetParticleModel()->Update(deltaTime);
	GameObject::Update(deltaTime);
}
void Aircraft::UpdateChildren(float deltaTime)
{
	for each (GameObject* child in GetChildren())
	{
		XMFLOAT3 velocity = GetParticleModel()->GetVelocity();
		float VelocityMagnitude = Magnitude(velocity);
		float wheelRotation = 0.1f;

		if (child->GetType() == "Rudder")
		{
			mRudder = child;
			child->GetTransform()->SetRotation(mSpeed * 50, mWheelRotation, 0.0f);
		}
	}
}

void Aircraft::CalculateForwardVector()
{
	mForward.x = sin(GetTransform()->GetRotation().y);
	mForward.y = -sin(GetTransform()->GetRotation().x);
	mForward.z = cos(GetTransform()->GetRotation().y);

	float planeDirectionMag = sqrt((mForward.x * mForward.x) + (mForward.y * mForward.y) + (mForward.z * mForward.z));
	mForward = XMFLOAT3(mForward.x / planeDirectionMag, mForward.y / planeDirectionMag, mForward.z / planeDirectionMag);
}
void Aircraft::CalculateLift()
{
	if (mSpeed >= 5.0f)
	{
		float liftCoef = 1.0f;
		float density = 0.5f;
		float wingArea = GetTransform()->GetRotation().x * 2.0f;

		XMFLOAT3 lift = GetParticleModel()->GetLift();
		XMFLOAT3 velocity = GetParticleModel()->GetVelocity();

		lift.y = liftCoef * ((density * (velocity.z / 5.0f * velocity.z / 5.0f)) / 2) * wingArea;

		this->GetParticleModel()->SetLift(lift);
	}
}
void Aircraft::CalculateDrag()
{
	XMFLOAT3 drag = GetParticleModel()->GetDrag();
	XMFLOAT3 thrust = GetParticleModel()->GetVelocity();
	
	drag.x = thrust.x *= -0.5f;
	drag.y = thrust.y *= -0.5f;
	drag.z = thrust.z *= -0.5f;

	this->GetParticleModel()->SetDrag(drag);
}
void Aircraft::TruncateSpeed()
{
	if (mSpeed > mMaxSpeed)
		mSpeed = mMaxSpeed;
	if (mSpeed < 0.0f)
		mSpeed = 0.0f;
}

void Aircraft::Draw(ID3D11DeviceContext* iContext)
{
	GameObject::Draw(iContext);
}