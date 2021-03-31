#include "CollisionManager.h"

#define DPHYSX_DLL_EXPORT
#define OR || 

CollisionManager* CollisionManager::mInstance = nullptr;

DPHYSX_DLL CollisionManager::CollisionManager(void)
{
	mVertexVertexCollision = false;
	mVertexEdgeCollision = false;
	mInterpenetration = false;
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
DPHYSX_DLL bool CollisionManager::AABBCollisionCheck(RigidBody& objectA, RigidBody& objectB)
{
	Vector3 obj1Pos = objectA.GetTransform()->GetPosition();
	Vector3 obj2Pos = objectB.GetTransform()->GetPosition();
											   
	Vector3 obj1Box = objectA.GetExtents();
	Vector3 obj2Box = objectB.GetExtents();

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
			ResolveInterpenetration(objectA, objectB);
			ResolveCollision(objectA, objectB);
			return true;
		}
		else if (VertexEdgeCollisionCheck(objectA, objectB))
		{
			ResolveInterpenetration(objectA, objectB);
			ResolveCollision(objectA, objectB);
			return true;
		}
		else
		{
			mVertexVertexCollision = false;
			mVertexEdgeCollision = false;
			mInterpenetration = false;
			return false;
		}
	}
	else
	{
		mVertexVertexCollision = false;
		mVertexEdgeCollision = false;
		mInterpenetration = false;
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

	for (unsigned int i = 0; i < 8; i++)
	{
		objectA.mVertices[i] = QVRotate(objectA.GetOrientation(), objectA.mVertices[i]);
		objectA.mVertices[i] += objectA.GetTransform()->GetPosition();

		objectB.mVertices[i] = QVRotate(objectB.GetOrientation(), objectB.mVertices[i]);
		objectB.mVertices[i] += objectB.GetTransform()->GetPosition();
	}

	for (unsigned int i = 0; i < 8 && !mVertexVertexCollision; i++)
	{
		for (unsigned int j = 0; j < 8 && !mVertexVertexCollision; j++)
		{
			Vector3 collisionPoint = objectA.mVertices[i];

			objectA.SetCollisionPoint(collisionPoint - objectA.GetTransform()->GetPosition());
			objectB.SetCollisionPoint(collisionPoint - objectB.GetTransform()->GetPosition());

			mCollisionNormal = objectA.GetTransform()->GetPosition() - objectB.GetTransform()->GetPosition();
			mCollisionNormal.Normalise();

			Vector3 vector1 = objectA.GetVelocity() + (objectA.GetAngularVelocity() ^ objectA.GetCollisionPoint());
			Vector3 vector2 = objectB.GetVelocity() + (objectB.GetAngularVelocity() ^ objectB.GetCollisionPoint());

			vector1 = QVRotate(objectA.GetOrientation(), vector1);
			vector2 = QVRotate(objectA.GetOrientation(), vector2);

			mRelativeVelocity = vector1 - vector2;
			float vrn = mRelativeVelocity * mCollisionNormal;

			if (PointCollision(objectA.mVertices[i], objectB.mVertices[j]) && vrn < 0.0)
			{
				mVertexVertexCollision = true;
			}
		}
	}

	return mVertexVertexCollision;
}
DPHYSX_DLL bool CollisionManager::VertexEdgeCollisionCheck(RigidBody& objectA, RigidBody& objectB)
{
	objectA.mEdges[0] = objectA.mVertices[0] - objectA.mVertices[1];
	objectA.mEdges[1] = objectA.mVertices[1] - objectA.mVertices[2];
	objectA.mEdges[2] = objectA.mVertices[2] - objectA.mVertices[3];
	objectA.mEdges[3] = objectA.mVertices[3] - objectA.mVertices[4];

	objectA.mEdges[4] = objectA.mVertices[4] - objectA.mVertices[0];
	objectA.mEdges[5] = objectA.mVertices[5] - objectA.mVertices[1];
	objectA.mEdges[6] = objectA.mVertices[6] - objectA.mVertices[2];
	objectA.mEdges[7] = objectA.mVertices[7] - objectA.mVertices[3];

	objectA.mEdges[8] = objectA.mVertices[4] - objectA.mVertices[5];
	objectA.mEdges[9] = objectA.mVertices[5] - objectA.mVertices[6];
	objectA.mEdges[10] = objectA.mVertices[6] - objectA.mVertices[7];
	objectA.mEdges[11] = objectA.mVertices[7] - objectA.mVertices[4];

	// =================================== //

	objectB.mEdges[0] = objectB.mVertices[0] - objectB.mVertices[1];
	objectB.mEdges[1] = objectB.mVertices[1] - objectB.mVertices[2];
	objectB.mEdges[2] = objectB.mVertices[2] - objectB.mVertices[3];
	objectB.mEdges[3] = objectB.mVertices[3] - objectB.mVertices[4];

	objectB.mEdges[4] = objectB.mVertices[4] - objectB.mVertices[0];
	objectB.mEdges[5] = objectB.mVertices[5] - objectB.mVertices[1];
	objectB.mEdges[6] = objectB.mVertices[6] - objectB.mVertices[2];
	objectB.mEdges[7] = objectB.mVertices[7] - objectB.mVertices[3];

	objectB.mEdges[8] = objectB.mVertices[4] - objectA.mVertices[5];
	objectB.mEdges[9] = objectB.mVertices[5] - objectB.mVertices[6];
	objectB.mEdges[10] = objectB.mVertices[6] - objectB.mVertices[7];
	objectB.mEdges[11] = objectB.mVertices[7] - objectB.mVertices[4];

	for (unsigned int i = 0; i < 12 && !mVertexEdgeCollision; i++)
	{
		for (unsigned int j = 0; j < 12 && !mVertexEdgeCollision; j++)
		{
			Vector3 u = objectB.mEdges[j];
			u.Normalise();

			Vector3 p = objectA.mVertices[i] - objectB.mVertices[j];

			Vector3 proj = (p * u) * u;
			Vector3 d = p ^ u;
			float distance = d.Magnitude();

			Vector3 collisionPoint = objectA.mVertices[i];
			objectA.SetCollisionPoint(collisionPoint - objectA.GetTransform()->GetPosition());
			objectB.SetCollisionPoint(collisionPoint - objectB.GetTransform()->GetPosition());

			mCollisionNormal = ((u ^ p) ^ u);
			mCollisionNormal.Normalise();

			Vector3 v1 = objectA.GetVelocity() + (objectA.GetAngularVelocity() ^ objectA.GetCollisionPoint());
			Vector3 v2 = objectB.GetVelocity() + (objectB.GetAngularVelocity() ^ objectB.GetCollisionPoint());

			v1 = QVRotate(objectA.GetOrientation(), v1);
			v2 = QVRotate(objectB.GetOrientation(), v2);

			mRelativeVelocity = (v1 - v2);
			float vrn = mRelativeVelocity * mCollisionNormal;

			if ((proj.Magnitude() > 0.0f) && (proj.Magnitude() <= objectB.mEdges[j].Magnitude()) && (distance <= COLLISION_TOLERANCE) && (vrn < 0.0))                              
				mVertexEdgeCollision = true;
		}
	}

	return mVertexEdgeCollision;
}
DPHYSX_DLL bool CollisionManager::PointCollision(Vector3& pointA, Vector3& pointB)
{
	if ((fabs(pointA.x - pointB.x) <= COLLISION_TOLERANCE) && (fabs(pointA.y - pointB.y) <= COLLISION_TOLERANCE) && (fabs(pointA.z - pointB.z) <= COLLISION_TOLERANCE))
	{
		return true;
	}

	return false;
}

DPHYSX_DLL int CollisionManager::ResolveInterpenetration(RigidBody& objectA, RigidBody& objectB)
{		
	Vector3 object1Last = objectA.GetTransform()->GetLastPosition();
	Vector3 object2Last = objectB.GetTransform()->GetLastPosition();
	objectA.GetTransform()->SetPosition(objectA.GetTransform()->GetLastPosition());
	objectB.GetTransform()->SetPosition(objectB.GetTransform()->GetLastPosition());	
	return 0;

	//if (!mVertexVertexCollision && mVertexEdgeCollision)
	//{
	//	for (unsigned int i = 0; i < 12 && !mInterpenetration; i++)
	//	{
	//		for (unsigned int j = 0; j < 12 && !mInterpenetration; j++)
	//		{
	//			Vector3 p = objectA.mVertices[i] - objectB.mVertices[j];
	//			float d = p * objectB.mEdges[j];

	//			if (d < 0)
	//			{
	//				mInterpenetration = true;
	//			}
	//		}
	//	}
	//}

	//if (mInterpenetration)
	//{
	//	return -1;
	//}
	//else if (mVertexEdgeCollision || mVertexVertexCollision)
	//{
	//	return 1;
	//}
	//else
	//{
	//	return 0;
	//}
}
DPHYSX_DLL void CollisionManager::ResolveCollision(RigidBody& objectA, RigidBody& objectB)
{
	float cofRest = min(objectA.GetRestituition(), objectB.GetRestituition());
	#pragma region MyRegion
		//float mA = objectA.GetMass();
		//float mB = objectB.GetMass();
		//Vector3 uA = objectA.GetVelocity();
		//Vector3 uB = objectB.GetVelocity();
		//Vector3 vA = Vector3(0.0f, 0.0f, 0.0f);
		//Vector3 vB = Vector3(0.0f, 0.0f, 0.0f);
		//Vector3 pA = objectA.GetTransform()->GetPosition();
		//Vector3 pB = objectB.GetTransform()->GetPosition();

		//if (pA.x > pB.x OR pB.x > pA.x)
		//{
		//	vA.x = ((mA * uA.x + mB * uB.x + mB * cofRest * (uB.x - uA.x)) / (mA + mB)) * -1.0f;
		//	vA.y = (mA * uA.y + mB * uB.y + mB * cofRest * (uB.y - uA.y)) / (mA + mB);
		//	vA.z = ((mA * uA.z + mB * uB.z + mB * cofRest * (uB.z - uA.z)) / (mA + mB)) * -1.0f;

		//	vB.x = ((mA * uA.x + mB * uB.x + mA * cofRest * (uA.x - uB.x)) / (mA + mB)) * -1.0f;
		//	vB.y = (mA * uA.y + mB * uB.y + mA * cofRest * (uA.y - uB.y)) / (mA + mB);
		//	vB.z = ((mA * uA.z + mB * uB.z + mA * cofRest * (uA.z - uB.z)) / (mA + mB)) * -1.0f;
		//}
		//else if (pA.y > pB.y OR pB.y > pA.y)
		//{
		//	vA.x = (mA * uA.x + mB * uB.x + mB * cofRest * (uB.x - uA.x)) / (mA + mB);
		//	vA.y = ((mA * uA.y + mB * uB.y + mB * cofRest * (uB.y - uA.y)) / (mA + mB)) * -1.0f;
		//	vA.z = (mA * uA.z + mB * uB.z + mB * cofRest * (uB.z - uA.z)) / (mA + mB);

		//	vB.x = (mA * uA.x + mB * uB.x + mA * cofRest * (uA.x - uB.x)) / (mA + mB);
		//	vB.y = ((mA * uA.y + mB * uB.y + mA * cofRest * (uA.y - uB.y)) / (mA + mB)) * -1.0f;
		//	vB.z = (mA * uA.z + mB * uB.z + mA * cofRest * (uA.z - uB.z)) / (mA + mB);
		//}

		//if (!objectA.GetScenery())
		//	objectA.SetVelocity(vA);
		//if (!objectB.GetScenery())
		//	objectB.SetVelocity(vB);  
	#pragma endregion

	Vector3 pt1 = objectA.GetCollisionPoint() - objectA.GetTransform()->GetPosition();
	Vector3 pt2 = objectB.GetCollisionPoint() - objectB.GetTransform()->GetPosition();
	float j;
	j = (-(1 + cofRest) * (mRelativeVelocity*mCollisionNormal)) /
		((1 / objectA.GetMass() + 1 / objectB.GetMass()) +
		(mCollisionNormal * (((pt1 ^ mCollisionNormal)*objectA.GetInverseInertia()) ^ pt1)) +
			(mCollisionNormal * (((pt2 ^ mCollisionNormal)*objectB.GetInverseInertia()) ^ pt2))
			);

	//objectA.GetVelocity() += (j * mCollisionNormal) / objectA.GetMass();     
	//objectA.GetAngularVelocity() += (objectA.GetCollisionPoint() ^ (j * mCollisionNormal)) / objectA.GetInertia();
	//objectB.GetVelocity() -= (j * mCollisionNormal) / objectB.GetMass();     
	//objectB.GetAngularVelocity() -= (objectB.GetCollisionPoint() ^ (j * mCollisionNormal)) / objectB.GetInertia();

	if (!objectA.GetScenery())
	{
		objectA.GetVelocity() += (j * mCollisionNormal) / objectA.GetMass();
		//objectA.GetAngularVelocityGlobal() += (pt2 ^ (j * mCollisionNormal))*objectA.GetInverseInertia();
		//objectA.GetAngularVelocity() = QVRotate(~objectA.GetOrientation(), objectA.GetAngularVelocityGlobal());
	}

	if (!objectB.GetScenery())
	{
		objectB.GetVelocity() -= (j * mCollisionNormal) / objectB.GetMass();
		//objectB.GetAngularVelocityGlobal() -= (pt2 ^ (j * mCollisionNormal))*objectB.GetInverseInertia();
		//objectB.GetAngularVelocity() = QVRotate(~objectB.GetOrientation(), objectB.GetAngularVelocityGlobal());
	}
}