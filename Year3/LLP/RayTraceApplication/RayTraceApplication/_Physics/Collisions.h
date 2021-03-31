#pragma once

class Floor;
class Sphere;

class Collisions
{
public:
	static bool SphereFloorCollision(Sphere* sphere, Floor* floor);

	static void ResolveCollision(Sphere* sphere, Floor* floor);
};