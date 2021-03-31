#include "stdafx.h"
#include <math.h>

#include "Intersections.h"

namespace Mathematics
{
	using namespace Structures;

	namespace Intersections
	{
		//
		// Finds scalar projection of vector u in the direction of v
		//
		float ScalarProjection(const Vector3& u, const Vector3& v)
		{
			if (v.IsNormalised())
			{
				return u.Dot(v);
			}
			else
			{
				return u.Dot(v) / v.Magnitude();
			}
		}

		//
		// Finds vector projection of vector u in the direction of v
		//
		Vector3 VectorProjection(const Vector3& u, const Vector3& v)
		{
			float puvMag = ScalarProjection(u, v);
			if (v.IsNormalised())
			{
				return v * puvMag;
			}
			else
			{
				return (v / v.Magnitude()) * puvMag;
			}
		}

		//
		// Finds the distance between a line and a point
		//
		float DistancePointToLine(const Line& line, const Vector3& point)
		{
			Vector3 vectorToProject = line.GetPoint() - point;
			Vector3 toProjectOn = line.GetDirection();

			Vector3 projection = VectorProjection(vectorToProject, toProjectOn);

			return (vectorToProject - projection).Magnitude();
		}

		//
		// Detemines an intersection between a line and sphere
		//
		bool LineSphereIntersect(const Line& line, const Vector3& sCentre, const float& sRadius)
		{
			return (DistancePointToLine(line, sCentre) < sRadius);
		}

//
// Determines an intersection between a line and a plane
//
bool LinePlaneIntersection(const Plane& plane, const Line& line, Vector3& intersectPoint) 
{
	Vector3 lineVector = line.GetDirection() - line.GetPoint();
	Vector3 lineToPlaneCentre = line.GetPoint() - plane.GetPoint();

	float dotlinePlaneNormal = plane.GetNormal().Dot(lineVector);
	float dotNormCentre = -plane.GetNormal().Dot(lineToPlaneCentre);

	if (fabs(dotlinePlaneNormal) < 1e-06)
	{           
		return false;	// segment is parallel to plane
	}

	float sI = dotNormCentre / dotlinePlaneNormal;
	if (sI < 0 || sI > 1)
	{
		return 0;
	}

	intersectPoint = line.GetPoint() + (lineVector * sI);

	if (plane.GetExtents().x != -1.0f 
		&& plane.GetExtents().y != -1.0f 
		&& plane.GetExtents().z != -1.0f)
	{
		float xMin = plane.GetPoint().x - plane.GetExtents().x;
		float xMax = plane.GetPoint().x + plane.GetExtents().x;
		float yMin = plane.GetPoint().y - plane.GetExtents().y;
		float yMax = plane.GetPoint().y + plane.GetExtents().y;

		if (xMin < intersectPoint.x && intersectPoint.x < xMax
			&& yMin < intersectPoint.y && intersectPoint.y < yMax)
		{
			return true;	// In area of collision
		}
		else
		{
			return false;	// Outside area of collision
		}
	}
	return true;
}
	}
}