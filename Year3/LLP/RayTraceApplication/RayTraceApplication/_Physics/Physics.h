#pragma once

class Sphere;

class Physics
{
public:
	static void ApplyGravity(Sphere* sphere, float deltaTime);
private:
	static void CalculatePosition(Sphere* sphere);
};