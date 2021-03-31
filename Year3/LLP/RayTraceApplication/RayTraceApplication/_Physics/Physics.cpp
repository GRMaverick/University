#include "Sphere.h"
#include "Vector3.h"
#include "Physics.h"

void Physics::ApplyGravity(Sphere* sphere, float deltaTime)
{
	Vector3 k1 = Vector3(0);
	Vector3 k2 = Vector3(0);
	Vector3 k3 = Vector3(0);
	Vector3 k4 = Vector3(0);

	Vector3 Velocity = Vector3(0);
	Vector3 NetForce = Vector3(0);
	Vector3 Acceleration = Vector3(0);
	Vector3 GravityF = Vector3(0.0f, -9.81f, 0.0f);

	NetForce += GravityF;
	Acceleration = NetForce / sphere->Mass;

	k1 = Acceleration * deltaTime;
	Acceleration = (NetForce + (k1 / 2)) / sphere->Mass;

	k2 = Acceleration * deltaTime;
	Acceleration = (NetForce + (k2 / 2)) / sphere->Mass;

	k3 = Acceleration * deltaTime;
	Acceleration = NetForce + k3;

	k4 = Acceleration * deltaTime;
	sphere->Velocity += (k1 + (k2 * 2) + (k3 * 2) + k4) / 6;
	
	sphere->Center += sphere->Velocity * deltaTime;
}
void Physics::CalculatePosition(Sphere* sphere)
{

}