#pragma once

#include "Line.h"
#include "Plane.h"
#include "Vector3.h"

namespace Mathematics
{
	using namespace Structures;
	
	namespace Intersections
	{
		//
		// Finds scalar projection of vector u in the direction of v
		//
		float ScalarProjection(const Vector3& u, const Vector3& v);

		//
		// Finds vector projection of vector u in the direction of v
		//
		Vector3 VectorProjection(const Vector3& u, const Vector3& v);

		//
		// Finds the distance between a line and a point
		//
		float DistancePointToLine(const Line& line, const Vector3& point);

		//
		// Determines an intersection between a line and sphere
		//
		bool LineSphereIntersect(const Line& line, const Vector3& sCentre, const float& sRadius);

		//
		// Determines an intersection between a line and a plane
		//
		bool LinePlaneIntersection(const Plane& plane, const Line& line, Vector3& intersectPoint);
	}
}