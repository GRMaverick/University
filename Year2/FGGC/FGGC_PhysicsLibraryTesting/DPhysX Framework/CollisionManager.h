#ifndef __PHYSX_COLLISION_MANAGER__
#define __PHYSX_COLLISION_MANAGER__

#ifndef DPHYSX_DLL_EXPORT
#define DPHYSX_DLL __declspec(dllexport)
#else
#define DPHYSX_DLL __declspec(dllimport)
#endif

#include "Commons.h"
#include "Particle.h"
#include "RigidBody.h"

using namespace std;


class CollisionManager
{
public:
	DPHYSX_DLL static CollisionManager& GetInstance(void);

	DPHYSX_DLL bool AABBCollisionCheck(Particle* objectA, Particle* objectB);
	DPHYSX_DLL bool SphereSphereCollisionCheck(Particle& objectA, Particle& objectB);
	DPHYSX_DLL bool SphereSphereCollisionCheck(RigidBody& objectA, RigidBody& objectB);

	DPHYSX_DLL bool RigidBodyCollision(RigidBody& objectA, RigidBody& objectB);

	
	DPHYSX_DLL void ResolveInterpenetration(Particle* objectA, Particle* objectB);
	DPHYSX_DLL void ResolveCollision(Particle* objectA, Particle* objectB);


private:
	DPHYSX_DLL bool VertexVertexCollisionCheck(RigidBody& objectA, RigidBody& objectB);
	DPHYSX_DLL bool VertexEdgeCollisionCheck(RigidBody& objectA, RigidBody& objectB);
	DPHYSX_DLL bool PointCollision(Vector3& pointA, Vector3& pointB);

	bool mVertexVertexCollision;
	bool mVertexEdgeCollision;

	static CollisionManager* mInstance;

	DPHYSX_DLL CollisionManager(void);
};
#endif