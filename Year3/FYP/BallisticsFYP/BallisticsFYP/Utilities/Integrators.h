#pragma once

class PhysicsComponent;
class TransformComponent;
 
class Integrators
{
public:
	static void RungeKutta4(PhysicsComponent* body, TransformComponent* transform, const float& deltaTime);
};