#pragma once

#include <vector>

#include "Plane.h"
#include "Vector3.h"
#include "IComponent.h"

using namespace Mathematics::Structures;

class CollisionComponent : public IComponent
{
public:
	CollisionComponent(void)
	{

	}
	virtual ~CollisionComponent(void)
	{

	}

	void SetOwnerName(const std::string& name) { IComponent::SetOwnerName(name); }
	std::string GetOwnerName(void) { return IComponent::GetOwnerName(); }

	void SetCollided(const bool& hasCollided) { m_HasCollided = hasCollided; }
	bool HasCollided(void) { return m_HasCollided; }

	// // Used for Narrow Phase Collision Detection
	CollisionComponent* AddVertex(const Vector3& vertex) { m_Vertices.push_back(vertex); return this; }	
	// // Used for Broad Phase Collision Detection
	CollisionComponent* SetBoundingRadius(const float& radius) { m_BoundingRadius = radius; return this; }
	// // Used for Narrow Phase Collision Detection
	CollisionComponent* SetVertices(const std::vector<Vector3>& vertices) { m_Vertices = vertices; return this; }
	// // Used for Narrow Phase Collision Detection
	CollisionComponent* AddCollidingPlane(const Mathematics::Structures::Plane& plane) { m_CollidingPlane = plane; return this; }
	
	// // Used for Broad Phase Collision Detection
	float GetBoundingRadius(void) const { return m_BoundingRadius; }
	// // Used for Narrow Phase Collision Detection
	std::vector<Vector3> GetVertices(void) const { return m_Vertices; }
	// // Used for Narrow Phase Collision Detection
	Mathematics::Structures::Plane GetCollidingPlane(void) const { return m_CollidingPlane; }

private:
	std::vector<Vector3>					m_Vertices;
	bool									m_HasCollided;
	float									m_BoundingRadius;
	Mathematics::Structures::Plane			m_CollidingPlane;
};