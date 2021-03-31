
#include "Floor.h"
#include "Sphere.h"
#include "Collisions.h"

#include <algorithm>

bool Collisions::SphereFloorCollision(Sphere* sphere, Floor* floor)
{
	if (sphere->Center.y - sphere->Radius < floor->Center.y)
	{
		sphere->Center.y = floor->Center.y + sphere->Radius;
		return true;
	}
	return false;
}

void Collisions::ResolveCollision(Sphere* sphere, Floor* floor)
{
	float cofRest = std::min(sphere->CoefRest, 1.0f);

	float mA = sphere->Mass;
	float mB = floor->Mass;
	Vector3 uA = sphere->Velocity;
	Vector3 uB = Vector3(0.0f);
	Vector3 vA = Vector3(0.0f);
	Vector3 vB = Vector3(0.0f);
	Vector3 pA = sphere->Center;
	Vector3 pB = floor->Center;

	vA.x = (mA * uA.x + mB * uB.x + mB * cofRest * (uB.x - uA.x)) / (mA + mB);
	vA.y = (mA * uA.y + mB * uB.y + mB * cofRest * (uB.y - uA.y)) / (mA + mB) * -1.0f;
	vA.z = (mA * uA.z + mB * uB.z + mB * cofRest * (uB.z - uA.z)) / (mA + mB);

	vB.x = (mA * uA.x + mB * uB.x + mA * cofRest * (uA.x - uB.x)) / (mA + mB);
	vB.y = (mA * uA.y + mB * uB.y + mA * cofRest * (uA.y - uB.y)) / (mA + mB) * -1.0f;
	vB.z = (mA * uA.z + mB * uB.z + mA * cofRest * (uA.z - uB.z)) / (mA + mB);

	sphere->Velocity = vB;
}