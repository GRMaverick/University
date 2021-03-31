#include "pch.h"
#include "Integrators.h"
#include "Vector3.h"

#include "PhysicsComponent.h"
#include "TransformComponent.h"

using namespace Mathematics::Structures;

void Integrators::RungeKutta4(PhysicsComponent* body, TransformComponent* transform, const float& deltaTime)
{
	float mass = body->GetMass();
	Vector3 velocity = body->GetVelocity();
	Vector3 netforce = body->GetNetforce();
	Vector3 lastPosition = transform->GetPosition();
	Vector3 acceleration = netforce / mass;

	Vector3 term1 = acceleration * deltaTime;
	acceleration = ((netforce + (term1 / 2)) / mass);

	Vector3 term2 = acceleration * deltaTime;
	acceleration = ((netforce + (term2 / 2)) / mass);

	Vector3 term3 = acceleration * deltaTime;
	acceleration = (netforce + term3);

	Vector3 term4 = acceleration * deltaTime;

	velocity += (term1 + (term2 * 2) + (term3 * 2) + term4) / 6;
	
	transform->SetLastPosition(lastPosition);
	lastPosition += (velocity * deltaTime);

	body->SetVelocity(velocity);
	body->SetAcceleration(acceleration);
	transform->SetPosition(lastPosition);

	body->SetNetforce({ 0.0f, 0.0f, 0.0f });
}