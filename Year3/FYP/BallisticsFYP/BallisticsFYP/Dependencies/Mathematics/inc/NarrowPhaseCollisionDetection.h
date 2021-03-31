#pragma once

#include <vector>

#include "Vector3.h"


namespace Mathematics
{
	using namespace Structures;

	namespace Intersections
	{
		class NarrowPhaseCollisionDetection
		{
		public:
			static bool GJKAlgorithm(const std::vector<Vector3>& aVertices, const std::vector<Vector3>& bVertices);

		private:
			static Vector3 v;
			static Vector3 b, c, d;
			static unsigned int n; //simplex size

			static bool		Update(const Vector3& a);
			static bool		CheckOneFaceAB(const Vector3& a, const Vector3& b, const Vector3& c);
			static bool		CheckOneFaceAC(const Vector3& a, const Vector3& b, const Vector3& c);
			static bool		CheckTwoFaces(Vector3& abc, Vector3& acd, Vector3& ac, Vector3& ab, Vector3& ad, const Vector3& ao);

			static Vector3	AveragePoint(const std::vector<Vector3>& vertices);
			static Vector3	SupportPoint(const std::vector<Vector3>& aVertices, const std::vector<Vector3>& bVertices, const Vector3& supportingDirection);
			static Vector3	TripleProduct(const Vector3& ab, const Vector3& c);
			static int			IndexOfFurthestPoint(const std::vector<Vector3>& vertices, const Vector3& supportingDirection);
		};
	}
}