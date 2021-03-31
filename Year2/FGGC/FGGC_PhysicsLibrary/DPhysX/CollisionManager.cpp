#include "CollisionManager.h"

#define DPHYSX_DLL_EXPORT
#define OR || 

CollisionManager* CollisionManager::mInstance = nullptr;

DPHYSX_DLL CollisionManager::CollisionManager(void)
{

}
DPHYSX_DLL CollisionManager& CollisionManager::GetInstance(void)
{
	if (mInstance == nullptr)
	{
		mInstance = new CollisionManager();
	}

	return *mInstance;
}

DPHYSX_DLL bool CollisionManager::AABBCollisionCheck(Particle* objectA, Particle* objectB)
{	
	Vector3 obj1Pos = objectA->GetTransform()->GetPosition();
	Vector3 obj2Pos = objectB->GetTransform()->GetPosition();

	Vector3 obj1Box = objectA->GetBBox();
	Vector3 obj2Box = objectB->GetBBox();

	float aX = obj1Pos.x - obj1Box.x;	float aWidth = obj1Box.x * 2;
	float aY = obj1Pos.y - obj1Box.y;	float aHeight = obj1Box.y * 2;
	float aZ = obj1Pos.z - obj1Box.z;	float aDepth = obj1Box.z * 2;

	float bX = obj2Pos.x - obj2Box.x;	float bWidth = obj2Box.x * 2;
	float bY = obj2Pos.y - obj2Box.y;	float bHeight = obj2Box.y * 2;
	float bZ = obj2Pos.z - obj2Box.z;	float bDepth = obj2Box.z * 2;

	if (aX > bX + bWidth)
		return false;
	else if (aX + aWidth < bX)
		return false;
	else if (aY > bY + bHeight)
		return false;
	else if (aY + aHeight < bY)
		return false;
	else if (aZ > bZ + bDepth)
		return false;
	else if (aZ + aDepth < bZ)
		return false;

	return true;
}
DPHYSX_DLL bool CollisionManager::SphereSphereCollisionCheck(Particle& objectA, Particle& objectB)
{
	Vector3 object1Pos = objectA.GetTransform()->GetPosition();
	Vector3 object2Pos = objectB.GetTransform()->GetPosition();

	Vector3 difference;
	difference = object1Pos - object2Pos;

	float differenceMag = difference.Magnitude();

	float radiusDistance = objectA.GetRadius() + objectB.GetRadius();

	if (differenceMag <= radiusDistance)
		return true;
	else
		return false;
}
DPHYSX_DLL bool CollisionManager::SphereSphereCollisionCheck(RigidBody& objectA, RigidBody& objectB)
{
	Vector3 object1Pos = objectA.GetTransform()->GetPosition();
	Vector3 object2Pos = objectB.GetTransform()->GetPosition();

	Vector3 difference;
	difference = object1Pos - object2Pos;

	float differenceMag = difference.Magnitude();

	float radiusDistance = objectA.GetRadius() + objectB.GetRadius();

	if (differenceMag <= radiusDistance)
		return true;
	else
		return false;
}

DPHYSX_DLL bool CollisionManager::RigidBodyCollision(RigidBody& objectA, RigidBody& objectB)
{
	if (SphereSphereCollisionCheck(objectA, objectB))
	{
		if (VertexVertexCollisionCheck(objectA, objectB))
		{
			throw exception("Vertex : Vertex Collision Detected");
			return true;
		}
		else if (VertexEdgeCollisionCheck(objectA, objectB))
		{
			throw exception("Vertex : Edge Collision Detected");
			return true;
		}
		else
		{
			throw exception("None :  Collision Detected");
			return false;
		}
	}
	else
	{
		throw exception("None :  Collision Detected");
		return false;
	}
}
DPHYSX_DLL bool CollisionManager::VertexVertexCollisionCheck(RigidBody& objectA, RigidBody& objectB)
{
	float widthA = objectA.GetExtents().x;
	float depthA = objectA.GetExtents().z;
	float heightA = objectA.GetExtents().y;

	float widthB = objectB.GetExtents().x;
	float depthB = objectB.GetExtents().z;
	float heightB = objectB.GetExtents().y;

	objectA.mVertices[0].x = widthA / 2;				objectB.mVertices[0].x = widthB / 2;
	objectA.mVertices[0].y = heightA / 2;				objectB.mVertices[0].y = heightB / 2;
	objectA.mVertices[0].z = depthA / 2;				objectB.mVertices[0].z = depthB / 2;
																				  
	objectA.mVertices[1].x = widthA / 2;				objectB.mVertices[1].x = widthB / 2;
	objectA.mVertices[1].y = heightA / 2;				objectB.mVertices[1].y = heightB / 2;
	objectA.mVertices[1].z = -depthA / 2;				objectB.mVertices[1].z = -depthB / 2;
																				  
	objectA.mVertices[2].x = -widthA / 2;				objectB.mVertices[2].x = -widthB / 2;
	objectA.mVertices[2].y = heightA / 2;				objectB.mVertices[2].y = heightB / 2;
	objectA.mVertices[2].z = -depthA / 2;				objectB.mVertices[2].z = -depthB / 2;
																				  
	objectA.mVertices[3].x = -widthA / 2;				objectB.mVertices[3].x = -widthB / 2;
	objectA.mVertices[3].y = heightA / 2;				objectB.mVertices[3].y = heightB / 2;
	objectA.mVertices[3].z = depthA / 2;				objectB.mVertices[3].z = depthB / 2;
																				  
	objectA.mVertices[4].x = widthA / 2;				objectB.mVertices[4].x = widthB / 2;
	objectA.mVertices[4].y = -heightA / 2;			objectB.mVertices[4].y = -heightB / 2;
	objectA.mVertices[4].z = depthA / 2;				objectB.mVertices[4].z = depthB / 2;
																				  
	objectA.mVertices[5].x = widthA / 2;				objectB.mVertices[5].x = widthB / 2;
	objectA.mVertices[5].y = -heightA / 2;			objectB.mVertices[5].y = -heightB / 2;
	objectA.mVertices[5].z = -depthA / 2;				objectB.mVertices[5].z = -depthB / 2;
																				  
	objectA.mVertices[6].x = -widthA / 2;				objectB.mVertices[6].x = -widthB / 2;
	objectA.mVertices[6].y = -heightA / 2;			objectB.mVertices[6].y = -heightB / 2;
	objectA.mVertices[6].z = -depthA / 2;				objectB.mVertices[6].z = -depthB / 2;
																				  
	objectA.mVertices[7].x = -widthA / 2;				objectB.mVertices[7].x = -widthB / 2;
	objectA.mVertices[7].y = -heightA / 2;			objectB.mVertices[7].y = -heightB / 2;
	objectA.mVertices[7].z = depthA / 2;				objectB.mVertices[7].z = depthB / 2;

	for (unsigned int i = 0; i < 12; i++)
	{
		//objectA.mVertices[i] = objectA.GetOrientation().QuaternionVectorRotate(objectA.mVertices[i]);
		objectA.mVertices[i] = QVRotate(objectA.GetOrientation(), objectA.mVertices[i]);
		objectA.mVertices[i] += objectA.GetTransform()->GetPosition();

		objectB.mVertices[i] = QVRotate(objectB.GetOrientation(), objectB.mVertices[i]);
		objectB.mVertices[i] += objectB.GetTransform()->GetPosition();
	}

	for (unsigned int i = 0; i < 12 && !mVertexVertexCollision; i++)
	{
		for (unsigned int j = 0; j < 12 && !mVertexVertexCollision; i++)
		{
			Vector3 collisionPoint = objectA.mVertices[i];
			
			objectA.SetCollisionPoint(collisionPoint - objectA.GetTransform()->GetPosition());
			objectB.SetCollisionPoint(collisionPoint - objectB.GetTransform()->GetPosition());

			Vector3 collisionNormal = objectA.GetTransform()->GetPosition() - objectB.GetTransform()->GetPosition();
			collisionNormal.Normalise();

			Vector3 vector1 = objectA.GetVelocity() + (objectA.GetAngularVelocity() ^ objectA.GetCollisionPoint());
			Vector3 vector2 = objectB.GetVelocity() + (objectB.GetAngularVelocity() ^ objectB.GetCollisionPoint());

			//vector1 = objectA.GetOrientation().QuaternionVectorRotate(vector1);

			vector1 = QVRotate(objectA.GetOrientation(), vector1);
			vector2 = QVRotate(objectA.GetOrientation(), vector2);
			//vector2 = objectB.GetOrientation().QuaternionVectorRotate(vector2);

			Vector3 relativeVelocity = vector1 - vector2;
			float vrn = relativeVelocity * collisionNormal;

			return (PointCollision(objectA.mVertices[i], objectB.mVertices[j]) && vrn < 0.0) ? true : false;
		}
	}

	return false;
}
DPHYSX_DLL bool CollisionManager::VertexEdgeCollisionCheck(RigidBody& objectA, RigidBody& objectb)
{
	return false;
}
DPHYSX_DLL bool CollisionManager::PointCollision(Vector3& pointA, Vector3& pointB)
{
	if ((fabs(pointA.x - pointB.x) <= COLLISION_TOLERANCE) &&	(fabs(pointA.y - pointB.y) <= COLLISION_TOLERANCE) && (fabs(pointA.z - pointB.z) <= COLLISION_TOLERANCE))
	{
		return true;
	}

	return false;
}

DPHYSX_DLL void CollisionManager::ResolveInterpenetration(Particle* objectA, Particle* objectB)
{
	Vector3 object1Last = objectA->GetTransform()->GetLastPosition();
	Vector3 object2Last = objectB->GetTransform()->GetLastPosition();

	objectA->GetTransform()->SetPosition(objectA->GetTransform()->GetLastPosition());
	objectB->GetTransform()->SetPosition(objectB->GetTransform()->GetLastPosition());
}
DPHYSX_DLL void CollisionManager::ResolveCollision(Particle* objectA, Particle* objectB)
{
	float cofRest = min(objectA->GetRestituition(), objectB->GetRestituition());

	float mA = objectA->GetMass();
	float mB = objectB->GetMass();
	Vector3 uA = objectA->GetVelocity();
	Vector3 uB = objectB->GetVelocity();
	Vector3 vA = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 vB = Vector3(0.0f, 0.0f, 0.0f); 
	Vector3 pA = objectA->GetTransform()->GetPosition();
	Vector3 pB = objectB->GetTransform()->GetPosition();

	if (pA.x > pB.x OR pB.x > pA.x)
	{
		vA.x = ((mA * uA.x + mB * uB.x + mB * cofRest * (uB.x - uA.x)) / (mA + mB)) * -1.0f;
		vA.y = (mA * uA.y + mB * uB.y + mB * cofRest * (uB.y - uA.y)) / (mA + mB);
		vA.z = ((mA * uA.z + mB * uB.z + mB * cofRest * (uB.z - uA.z)) / (mA + mB)) * -1.0f;

		vB.x = ((mA * uA.x + mB * uB.x + mA * cofRest * (uA.x - uB.x)) / (mA + mB)) * -1.0f;
		vB.y = (mA * uA.y + mB * uB.y + mA * cofRest * (uA.y - uB.y)) / (mA + mB);
		vB.z = ((mA * uA.z + mB * uB.z + mA * cofRest * (uA.z - uB.z)) / (mA + mB)) * -1.0f;
	}
	else if (pA.y > pB.y OR pB.y > pA.y)
	{
		vA.x = (mA * uA.x + mB * uB.x + mB * cofRest * (uB.x - uA.x)) / (mA + mB);
		vA.y = ((mA * uA.y + mB * uB.y + mB * cofRest * (uB.y - uA.y)) / (mA + mB)) * -1.0f;
		vA.z = (mA * uA.z + mB * uB.z + mB * cofRest * (uB.z - uA.z)) / (mA + mB);

		vB.x = (mA * uA.x + mB * uB.x + mA * cofRest * (uA.x - uB.x)) / (mA + mB);
		vB.y = ((mA * uA.y + mB * uB.y + mA * cofRest * (uA.y - uB.y)) / (mA + mB)) * -1.0f;
		vB.z = (mA * uA.z + mB * uB.z + mA * cofRest * (uA.z - uB.z)) / (mA + mB);
	}

	if (!objectA->GetScenery())
		objectA->SetVelocity(vA);
	if (!objectB->GetScenery())
		objectB->SetVelocity(vB);
}